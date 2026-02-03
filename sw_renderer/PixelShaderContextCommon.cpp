#include "PixelShaderContextCommon.h"

#include "cr-pixel-shader.h"

using namespace Ceng;

PixelShaderContextCommon::PixelShaderContextCommon(CR_PixelShader* shader)
{
	blendState = nullptr;

	this->shader = shader;

	link = nullptr;
	quadSizeBytes = 0;

	activeRenderTargets = 0;

	textureUnits = nullptr;

	Ceng::UINT32 k;

	for (k = 0; k < 2 + CRENDER_MAX_COLOR_TARGETS; k++)
	{
		targetHandles[k] = nullptr;
		targetWriters[k] = nullptr;
	}
}

PixelShaderContextCommon::~PixelShaderContextCommon()
{
	for (Ceng::UINT32 k = 0; k < 2 + CRENDER_MAX_COLOR_TARGETS; k++)
	{
		if (targetWriters[k] != nullptr)
		{
			if (targetWriters[k] != shader->nullWriter)
			{
				targetWriters[k]->Release();
			}			
		}		
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

		if (targetHandles[k] != nullptr)
		{
			Pshader::PshaderTargetWriter* writer = source.targetHandles[k]->GetWriter(blendState);

			if (writer == nullptr)
			{
				writer = shader->nullWriter;
			}

			targetWriters[k] = writer;
		}
		else
		{
			targetWriters[k] = shader->nullWriter;
		}
	}

	
	uniformBuffer = source.uniformBuffer;
}

const CRESULT PixelShaderContextCommon::ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
	UniformManager& uniformManager)
{
	uniformBuffer.Configure(&uniformManager, shader->cacheLine);

	return CE_OK;
}