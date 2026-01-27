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
}

const CRESULT PixelShaderContextCommon::ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
	UniformManager& uniformManager)
{
	uniformBuffer.Configure(&uniformManager, shader->cacheLine);

	return CE_OK;
}