#include "PixelShaderContextCommon.h"

#include "cr-pixel-shader.h"

using namespace Ceng;

PixelShaderContextCommon::PixelShaderContextCommon(CR_PixelShader* shader)
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

PixelShaderContextCommon::PixelShaderContextCommon(const PixelShaderContextCommon& source)
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
		uniformPtr[k] = &uniformBuffer[shader->uniformAllocation[k].bufferId][shader->uniformAllocation[k].offset];
	}
}

const CRESULT PixelShaderContextCommon::ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
	const std::vector<UniformAllocation>& allocations,
	const std::vector<UniformBlock>& blocks)
{
	for (int k = 0; k < blocks.size(); ++k)
	{
		uniformBuffer.emplace_back(blocks[k].size, shader->cacheLine);
	}

	uniformPtr = AlignedBuffer<UINT8*>(Ceng::UINT32(shader->uniformList.size()), shader->cacheLine);

	for (int k = 0; k < uniformList.size(); ++k)
	{
		uniformPtr[k] = &uniformBuffer[allocations[k].bufferId][allocations[k].offset];
	}

	return CE_OK;
}