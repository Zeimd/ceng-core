#include "VertexShaderInstanceCommon.h"

#include "cr-vertex-shader.h"

#include "cr-vertex-format.h"

#include "vertex-stream.h"

using namespace Ceng;

VertexShaderInstanceCommon::VertexShaderInstanceCommon(CR_VertexShader* shader)
{
	this->shader = shader;

	fragmentFormat = nullptr;

	fragmentSizeBytes = 0;

	streamCount = 0;

	vertexFormat = nullptr;

	vertexStreams = nullptr;
}

VertexShaderInstanceCommon::VertexShaderInstanceCommon(const VertexShaderInstanceCommon& source)
{
	shader = source.shader;

	vertexFormat = source.vertexFormat;

	streamCount = source.streamCount;

	vertexStreams = source.vertexStreams;

	fragmentFormat = source.fragmentFormat;

	fragmentSizeBytes = source.fragmentSizeBytes;
	
	uniformBuffer = source.uniformBuffer;

	uniformPtr = AlignedBuffer<UINT8*>(
		Ceng::UINT32(shader->uniformList.size()), shader->cacheLine);

	for (Ceng::UINT32 k = 0; k < shader->uniformList.size(); k++)
	{
		uniformPtr[k] = &uniformBuffer[shader->uniformList[k].bufferOffset];
	}
}

const CRESULT VertexShaderInstanceCommon::ConfigureInput(const std::vector<CR_vsInputSemantic>& inputSemantics)
{
	sourceIndex = AlignedBuffer<Ceng::UINT32>(inputSemantics.size(), shader->cacheLine);

	inputSteps = AlignedBuffer<Ceng::POINTER>(inputSemantics.size(), shader->cacheLine);

	inputBaseAddress = AlignedBuffer<Ceng::POINTER>(inputSemantics.size(), shader->cacheLine);

	Ceng::UINT32 k, j;

	for (k = 0; k < inputSemantics.size(); k++)
	{
		sourceIndex[k] = -1;

		for (j = 0; j < vertexFormat->variables.size(); j++)
		{
			if (inputSemantics[k].semantic == vertexFormat->variables[j].semantic)
			{
				sourceIndex[k] = j;

				inputBaseAddress[k] = POINTER(vertexFormat->variables[j].inputOffset) +
					POINTER(vertexStreams[vertexFormat->variables[j].inputStream].inputPtr);

				inputSteps[k] = vertexStreams[vertexFormat->variables[j].inputStream].elementSize;

				break;
			}
		}

		if (sourceIndex[k] == -1)
		{
			return CE_ERR_FAIL;
		}
	}

	return CE_OK;
}

const CRESULT VertexShaderInstanceCommon::ConfigureUniforms(const std::vector<CR_ShaderConstantData>& uniformList,
	const Ceng::UINT32 bufferSize)
{
	uniformBuffer = AlignedBuffer<UINT8>(shader->uniformBufferSize, shader->cacheLine);

	uniformPtr = AlignedBuffer<UINT8*>(
		Ceng::UINT32(shader->uniformList.size()), shader->cacheLine);

	Ceng::UINT32 k;

	for (k = 0; k < shader->uniformList.size(); k++)
	{
		uniformPtr[k] = &uniformBuffer[shader->uniformList[k].bufferOffset];
	}

	return CE_OK;
}