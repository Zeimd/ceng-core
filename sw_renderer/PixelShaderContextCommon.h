#pragma once

#ifndef CENG_SWR_PIXEL_SHADER_INSTANCE_COMMON_H
#define CENG_SWR_PIXEL_SHADER_INSTANCE_COMMON_H

#include <vector>

#include <ceng/datatypes/shader-uniform-desc.h>

#include <ceng/datatypes/aligned-buffer.h>

#include "texture-unit.h"

#include "UniformManager.h"

namespace Ceng
{
	class CR_PixelShader;

	class ShaderLinkInstance;

	using UniformBufferContainer = AlignedBuffer<Ceng::UINT8>;

	class PixelShaderContextCommon
	{
	public:

		CR_PixelShader* shader;

		AlignedBuffer<Ceng::UINT8*> uniformPtr;

		std::vector<UniformBufferContainer> uniformBuffer;

		ShaderLinkInstance* link;

		UINT32 quadSizeBytes;

		std::vector<TextureUnit> textureUnits;

		UINT32 activeRenderTargets;

		std::shared_ptr<CR_NewTargetData> targetHandles[2 + CRENDER_MAX_COLOR_TARGETS];

	public:

		PixelShaderContextCommon() = delete;

		PixelShaderContextCommon(CR_PixelShader* shader);

		PixelShaderContextCommon(const PixelShaderContextCommon& source);

		const CRESULT ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
			const UniformManager& uniformManager);
	};
}

#endif