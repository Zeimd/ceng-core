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
		targetWriters[k].writer = nullptr;
		targetWriters[k].isNull = true;
	}
}

PixelShaderContextCommon::~PixelShaderContextCommon()
{
	for (Ceng::UINT32 k = 0; k < 2 + CRENDER_MAX_COLOR_TARGETS; k++)
	{
		if (targetWriters[k].isNull == false)
		{
			targetWriters[k].writer->Release();
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
	
	uniformBuffer = source.uniformBuffer;

	blendState = source.blendState;

	ConfigureRenderTargets(source.targetHandles);
}

CRESULT PixelShaderContextCommon::ConfigureRenderTargets(const std::shared_ptr<CR_NewTargetData> targets[])
{
	Ceng::UINT32 k;

	for (k = 0; k < 2 + CRENDER_MAX_COLOR_TARGETS; k++)
	{
		targetHandles[k] = targets[k];

		if (targetHandles[k] != nullptr)
		{
			Pshader::PshaderTargetWriter* writer = targets[k]->GetWriter(blendState);

			if (writer != nullptr)
			{
				targetWriters[k].writer = writer;
				targetWriters[k].isNull = false;
			}
			else
			{
				writer = shader->nullWriter;
				targetWriters[k].isNull = true;
			}
		}
		else
		{
			targetWriters[k].writer = shader->nullWriter;
			targetWriters[k].isNull = true;
		}
	}

	return CE_OK;
}

const CRESULT PixelShaderContextCommon::ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
	UniformManager& uniformManager)
{
	uniformBuffer.Configure(&uniformManager, shader->cacheLine);

	return CE_OK;
}