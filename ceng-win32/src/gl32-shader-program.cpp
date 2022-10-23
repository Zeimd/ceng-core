/*****************************************************************************
*
* gl32-shader-program.cpp
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#include "../inc/gl32-shader-program.h"

#include "../inc/gl32-vertex-shader.h"
#include "../inc/gl32-pixel-shader.h"

#include "../inc/gl32-uniform-empty.h"
#include "../inc/gl32-uniform-float.h"
#include "../inc/gl32-uniform-float2.h"
#include "../inc/gl32-uniform-float3.h"
#include "../inc/gl32-uniform-float4.h"
#include "../inc/gl32-uniform-mat4.h"
#include "../inc/gl32-uniform-sampler2d.h"

using namespace Ceng;

GL32_ShaderProgram::GL32_ShaderProgram()
{
}

GL32_ShaderProgram::GL32_ShaderProgram(const GLuint programID, std::vector<UniformData> &&uniforms, Ceng::StringUtf8 &&log, const Ceng::BOOL linked)
	: programID(programID),uniforms(uniforms),log(log),linked(linked)
{
}

GL32_ShaderProgram::~GL32_ShaderProgram()
{
	glDeleteProgram(programID);
}

void GL32_ShaderProgram::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_ShaderProgram::GetInstance(Ceng::VertexShader *vertexShader, Ceng::PixelShader *pixelShader,GL32_ShaderProgram **program)
{
	if (vertexShader == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (!vertexShader->Compiled())
	{
		return CE_ERR_INVALID_PARAM;
	}

	if (pixelShader == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (!pixelShader->Compiled())
	{
		return CE_ERR_INVALID_PARAM;
	}

	GLuint programID = glCreateProgram();

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	GL32_VertexShader *gl_vshader = static_cast<GL32_VertexShader*>(vertexShader);
	GL32_PixelShader *gl_pshader = static_cast<GL32_PixelShader*>(pixelShader);

	glAttachShader(programID,gl_vshader->shaderID);

	result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glDeleteProgram(programID);
		return CE_ERR_FAIL;
	}

	glAttachShader(programID, gl_pshader->shaderID);

	result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glDeleteProgram(programID);
		return CE_ERR_FAIL;
	}

	glLinkProgram(programID);

	result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glDeleteProgram(programID);
		return CE_ERR_FAIL;
	}

	Ceng::BOOL linked = true;
	Ceng::StringUtf8 programLog;

	GLint gl_linked;
	glGetProgramiv(programID, GL_LINK_STATUS, &gl_linked);

	if (gl_linked != GL_TRUE)
	{
		linked = false;

		GLint logSize;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logSize);

		std::vector<char> tempLog(logSize);

		glGetProgramInfoLog(programID, logSize, nullptr, &tempLog[0]);

		programLog = &tempLog[0];
	}

	std::vector<UniformData> uniforms;

	GatherUniforms(programID, uniforms);

	*program = new GL32_ShaderProgram(programID,std::move(uniforms),std::move(programLog),linked);

	return CE_OK;
}

const Ceng::CRESULT GL32_ShaderProgram::GatherUniforms(const GLuint programID, std::vector<UniformData> &uniforms)
{
	GLint amount;
	GLint maxLength;

	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &amount);

	glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);

	std::vector<char> tempName(maxLength,0);

	UniformData tempData;

	for (Ceng::INT32 k = 0; k < amount; ++k)
	{
		glGetActiveUniform(programID, k, maxLength, nullptr, &tempData.size, &tempData.type, &tempName[0]);

		tempData.index = glGetUniformLocation(programID, &tempName[0]);

		tempData.name = &tempName[0];
		uniforms.push_back(tempData);
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_ShaderProgram::GetConstant(const char *variableName, Ceng::ShaderConstant **handle)
{
	Ceng::UINT32 k;

	for (k = 0; k < uniforms.size(); ++k)
	{
		if (uniforms[k].name == variableName)
		{
			break;
		}
	}

	if (k == uniforms.size())
	{
		*handle = new GL32_UniformEmpty();

		return CE_ERR_UNDEFINED_UNIFORM;
	}

	GLuint gl_index = uniforms[k].index;

	switch (uniforms[k].type)
	{
	case GL_FLOAT:
		*handle = new GL32_UniformFloat(gl_index, this);
		break;
	case GL_FLOAT_VEC2:
		*handle = new GL32_UniformFloat2(gl_index, this);
		break;
	case GL_FLOAT_VEC3:
		*handle = new GL32_UniformFloat3(gl_index, this);
		break;
	case GL_FLOAT_VEC4:
		*handle = new GL32_UniformFloat4(gl_index,this);
		break;
	case GL_INT:
		break;
	case GL_INT_VEC2:
		break;
	case GL_INT_VEC3:
		break;
	case GL_INT_VEC4:
		break;
	case GL_BOOL:
		break;
	case GL_BOOL_VEC2:
		break;
	case GL_BOOL_VEC3:
		break;
	case GL_BOOL_VEC4:
		break;
	case GL_FLOAT_MAT2:
		break;
	case GL_FLOAT_MAT3:
		break;
	case GL_FLOAT_MAT4:
		*handle = new GL32_UniformMat4(gl_index, this);
		break;
	case GL_SAMPLER_1D:
	case GL_SAMPLER_1D_ARRAY:
	case GL_SAMPLER_2D:
	case GL_SAMPLER_2D_ARRAY:
	case GL_SAMPLER_3D:
	case GL_SAMPLER_CUBE:
	case GL_SAMPLER_CUBE_MAP_ARRAY:
		*handle = new GL32_UniformSampler2D(gl_index, this);
		break;
	default:
		return CE_ERR_FAIL;
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_ShaderProgram::AddUniformUpdate(GL32_ShaderConstant *uniform)
{
	uniformUpdates.push_back(uniform);

	return CE_OK;
}

const Ceng::CRESULT GL32_ShaderProgram::GL_UpdateUniforms()
{
	for (Ceng::UINT32 k = 0; k < uniformUpdates.size(); ++k)
	{
		uniformUpdates[k]->GL_Update();
	}

	uniformUpdates.clear();

	return CE_OK;
}

const Ceng::CRESULT GL32_ShaderProgram::GetLog(Ceng::StringUtf8 **out_log)
{
	*out_log = new StringUtf8(log);
	return CE_OK;
}

const Ceng::BOOL GL32_ShaderProgram::Linked()
{
	return linked;
}

const Ceng::BOOL GL32_ShaderProgram::IsActive()
{
	return active;
}
