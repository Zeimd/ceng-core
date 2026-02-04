#pragma once

#ifndef CENG_SWR_PIXEL_SHADER_INSTANCE_COMMON_H
#define CENG_SWR_PIXEL_SHADER_INSTANCE_COMMON_H

#include <vector>

#include <ceng/datatypes/shader-uniform-desc.h>

#include <ceng/datatypes/aligned-buffer.h>

#include "texture-unit.h"

#include "UniformManager.h"
#include "UniformBufferInstance.h"

#include "CombinedBlendState.h"

#include <ceng/swshader/PshaderTargetWriter.h>

namespace Ceng
{
	class CR_PixelShader;

	class ShaderLinkInstance;	

	struct WriterData
	{
		Pshader::PshaderTargetWriter* writer;
		bool isNull;
	};

	class PixelShaderContextCommon
	{
	public:

		CR_PixelShader* shader;

		CombinedBlendState* blendState;

		UniformBufferInstance uniformBuffer;

		ShaderLinkInstance* link;

		UINT32 quadSizeBytes;

		std::vector<TextureUnit>* textureUnits;

		UINT32 activeRenderTargets;

		static const Ceng::UINT32 maxTargets = 2 + CRENDER_MAX_COLOR_TARGETS;

		std::shared_ptr<CR_NewTargetData> targetHandles[maxTargets];

		WriterData targetWriters[maxTargets];

	public:

		PixelShaderContextCommon() = delete;

		~PixelShaderContextCommon();

		PixelShaderContextCommon(CR_PixelShader* shader);

		PixelShaderContextCommon(const PixelShaderContextCommon& source);

		const CRESULT ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
			UniformManager& uniformManager);

		CRESULT ConfigureRenderTargets(const std::shared_ptr<CR_NewTargetData> targets[]);
	};
}

#endif