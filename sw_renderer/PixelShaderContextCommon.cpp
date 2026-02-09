#include "PixelShaderContextCommon.h"

#include "CombinedBlendState.h"
#include "UniformManager.h"

#include "cr-pixel-shader.h"

#include "rtarget-data.h"

using namespace Ceng;

PixelShaderContextCommon::PixelShaderContextCommon(CR_PixelShader* shader)
{
	blendState = nullptr;

	this->shader = shader;

	link = nullptr;
	quadSizeBytes = 0;

	activeRenderTargets = 0;

	textureUnits = nullptr;

	InitWriterData();
}

void PixelShaderContextCommon::InitWriterData()
{
	for (Ceng::UINT32 k = 0; k < maxTargets; k++)
	{
		targetHandles[k] = nullptr;
		targetWriters[k].writer = nullptr;
		targetWriters[k].isNull = true;
	}
}

PixelShaderContextCommon::~PixelShaderContextCommon()
{
	for (Ceng::UINT32 k = 0; k < maxTargets; k++)
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

	textureUnits = source.textureUnits;
	
	uniformBuffer = source.uniformBuffer;

	blendState = source.blendState;

	InitWriterData();

	ConfigureRenderTargets(source.activeRenderTargets, source.targetHandles);
}

CRESULT PixelShaderContextCommon::ConfigureRenderTargets(Ceng::UINT32 amount, const std::shared_ptr<CR_NewTargetData> targets[])
{
	Ceng::UINT32 k;

	activeRenderTargets = amount;

	for (k = 2; k < amount; k++)
	{
		targetHandles[k] = targets[k];

		if (targetWriters[k].writer != nullptr && targetWriters[k].isNull == false)
		{
			targetWriters[k].writer->Release();
			targetWriters[k].writer = nullptr;
			targetWriters[k].isNull = true;
		}

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

	for (k = amount; k < maxTargets; ++k)
	{
		if (targetWriters[k].writer != nullptr && targetWriters[k].isNull == false)
		{
			targetWriters[k].writer->Release();
		}

		targetHandles[k] = nullptr;
		targetWriters[k].writer = shader->nullWriter;
		targetWriters[k].isNull = true;
	}

	return CE_OK;
}

const CRESULT PixelShaderContextCommon::ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
	UniformManager& uniformManager)
{
	uniformBuffer.Configure(&uniformManager, shader->cacheLine);

	return CE_OK;
}