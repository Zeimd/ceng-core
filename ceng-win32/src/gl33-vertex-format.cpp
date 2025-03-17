/*****************************************************************************
*
* gl33-vertex-format.cpp
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#include "../inc/gl33-vertex-format.h"
#include "../inc/gl32-vertex-buffer.h"
#include "../inc/gl32-shader-program.h"

using namespace Ceng;

GL33_VertexFormat::GL33_VertexFormat() : locked(false), enabledArrays(false)
{
}

GL33_VertexFormat::GL33_VertexFormat(std::vector<GL_VertexData> &&vertexData, std::vector<StreamData> &&streamList)
	: vertexData(vertexData), streamList(streamList), locked(false), enabledArrays(false)
{
	SetEmptyLinks();
}

GL33_VertexFormat::~GL33_VertexFormat()
{
}

void GL33_VertexFormat::Release()
{
	delete this;
}

const CRESULT GL33_VertexFormat::GetInstance(const std::vector<VertexDeclData> &vertexDecl, GL33_VertexFormat **out_format)
{
	std::vector<GL_VertexData> vertexData;

	std::vector<StreamData> streamList(max_vertex_streams,StreamData());

	for (Ceng::UINT32 k = 0; k < vertexDecl.size(); ++k)
	{
		if (vertexDecl[k].streamSource == VTX_DECL_END.streamSource)
		{
			break;
		}

		GL_VertexData tempData;

		if (vertexDecl[k].streamSource > max_vertex_streams)
		{
			return CE_ERR_INVALID_PARAM;
		}

		CRESULT cresult = tempData.TranslateFormat(vertexDecl[k].format);
		if (cresult != CE_OK)
		{
			return cresult;
		}

		tempData.name = vertexDecl[k].name;
		tempData.stream = vertexDecl[k].streamSource;
		tempData.offset = streamList[tempData.stream].stride;
	
		vertexData.push_back(tempData);

		streamList[tempData.stream].stride += tempData.size;
		streamList[tempData.stream].attributes.push_back(vertexData.size()-1);
	}

	*out_format = new GL33_VertexFormat(std::move(vertexData),std::move(streamList));

	return CE_OK;
}

const Ceng::CRESULT GL_VertexData::TranslateFormat(const Ceng::VTX_DATATYPE::value format)
{
	normalized = false;

	switch (format)
	{
	case VTX_DATATYPE::FLOAT:
		type = GL_FLOAT;
		elements = 1;
		size = 4;
		break;
	case VTX_DATATYPE::FLOAT2:
		type = GL_FLOAT;
		elements = 2;
		size = 8;
		break;
	case VTX_DATATYPE::FLOAT3:
		type = GL_FLOAT;
		elements = 3;
		size = 12;
		break;
	case VTX_DATATYPE::FLOAT4:
		type = GL_FLOAT;
		elements = 4;
		size = 16;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

void GL33_VertexFormat::LinkShaderProgram(GL32_ShaderProgram *program)
{
	if (program == nullptr)
	{
		SetEmptyLinks();
		return;
	}

	Ceng::UINT32 linkIndex;
	
	for (linkIndex = 0; linkIndex < shaderLink.size(); ++linkIndex)
	{
		if (shaderLink[linkIndex].program->programID == program->programID)
		{
			break;
		}
	}

	if (linkIndex < shaderLink.size())
	{
		for (Ceng::UINT32 k = 0; k < vertexData.size(); ++k)
		{
			vertexData[k].gl_attribHandle = shaderLink[linkIndex].linkValues[k];

			vertexData[k].shaderLink = false;

			if (vertexData[k].gl_attribHandle != -1)
			{
				vertexData[k].shaderLink = true;
			}
		}
	}
	else
	{
		// Not linked to the program before

		shaderLink.push_back(LinkVector(vertexData.size(),program));

		LinkVector &linkVector = shaderLink[shaderLink.size() - 1];

		for (Ceng::UINT32 k = 0; k < vertexData.size(); ++k)
		{
			GLint gl_handle = glGetAttribLocation(program->programID, vertexData[k].name.ToCString());

			//GLenum result = glGetError();

			linkVector.linkValues[k] = gl_handle;

			vertexData[k].gl_attribHandle = gl_handle;

			vertexData[k].shaderLink = false;

			if (vertexData[k].gl_attribHandle != -1)
			{
				vertexData[k].shaderLink = true;
			}
		}
	}
}

void GL33_VertexFormat::LinkVertexStream(const Ceng::UINT32 index, GL32_VertexStreamState *stream)
{
	if (index >= streamList.size())
	{
		return;
	}

	std::vector<size_t> &attribList = streamList[index].attributes;

	for (Ceng::UINT32 k = 0; k < attribList.size(); ++k)
	{
		GL_VertexData &variable = vertexData[attribList[k]];

		if (variable.shaderLink == false)
		{
			variable.streamLink = false;
			variable.arrayEnabled = false;

			continue;
		}

		Ceng::BOOL disable = false;
		
		if (stream == nullptr)
		{
			disable = true;
		}
		else if (stream->vertexBuffer == nullptr)
		{
			disable = true;
		}
		else if (stream->vertexBuffer->bufferID == -1)
		{
			disable = true;
		}

		if (disable == true)
		{
			if (variable.arrayEnabled == true)
			{
				glDisableVertexAttribArray(variable.gl_attribHandle);
			}

			variable.arrayEnabled = false;
			variable.streamLink = false;

			continue;
		}

		glEnableVertexAttribArray(variable.gl_attribHandle);
		variable.arrayEnabled = true;

		Ceng::POINTER offset = Ceng::POINTER(variable.offset) + stream->offset;

		glVertexAttribPointer(variable.gl_attribHandle, variable.elements, variable.type, variable.normalized, streamList[index].stride,
			(void*)(offset));

		variable.streamLink = true;	
	}

	enabledArrays = true;
}

void GL33_VertexFormat::DisableStreamLinks()
{
	if (enabledArrays == false) return;

	for (Ceng::UINT32 k = 0; k < vertexData.size(); ++k)
	{
		GL_VertexData &variable = vertexData[k];

		if (variable.arrayEnabled == true)
		{
			glDisableVertexAttribArray(variable.gl_attribHandle);
		}

		variable.arrayEnabled = false;
		variable.shaderLink = false;
	}

	enabledArrays = false;
}

void GL33_VertexFormat::Clear()
{
	vertexData.clear();
}

const size_t GL33_VertexFormat::StreamCount()
{
	return streamList.size();
}

const Ceng::UINT32 GL33_VertexFormat::StreamStride(const size_t stream)
{
	if (stream > streamList.size()) return -1;

	return streamList[stream].stride;
}

void GL33_VertexFormat::SetEmptyLinks()
{
	for (Ceng::UINT32 k = 0; k < vertexData.size(); ++k)
	{
		vertexData[k].gl_attribHandle = -1;
		vertexData[k].shaderLink = false;
	}
}

