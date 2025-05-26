#include "PixelShaderInstanceCommon.h"

#include "cr-pixel-shader.h"

using namespace Ceng;

PixelShaderInstanceCommon::PixelShaderInstanceCommon(CR_PixelShader* shader)
{
	this->shader = shader;

	link = nullptr;
	quadSizeBytes = 0;

	activeRenderTargets = 0;

	textureUnits = std::vector<TextureUnit>(CRENDER_MAX_SHADER_TEXTURES);

	Ceng::UINT32 k;

	for (k = 0; k < 2 + CRENDER_MAX_COLOR_TARGETS; k++)
	{
		targetHandles[k] = nullptr;
	}
}

PixelShaderInstanceCommon::PixelShaderInstanceCommon(const PixelShaderInstanceCommon& source)
{
	shader = source.shader;
	
	link = source.link;

	quadSizeBytes = source.quadSizeBytes;

	activeRenderTargets = source.activeRenderTargets;

	textureUnits = source.textureUnits;

	Ceng::UINT32 k;

	for (k = 0; k < 2 + CRENDER_MAX_COLOR_TARGETS; k++)
	{
		targetHandles[k] = source.targetHandles[k];
	}

	uniformBuffer = source.uniformBuffer;

	uniformPtr = AlignedBuffer<UINT8*>(
		Ceng::UINT32(shader->uniformList.size()), shader->cacheLine);

	for (k = 0; k < shader->uniformList.size(); k++)
	{
		uniformPtr[k] = &uniformBuffer[shader->uniformList[k].bufferOffset];
	}
}

const CRESULT PixelShaderInstanceCommon::ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
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