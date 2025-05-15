#pragma once

#ifndef CENG_SWR_PIXEL_SHADER_INSTANCE_COMMON_H
#define CENG_SWR_PIXEL_SHADER_INSTANCE_COMMON_H

#include <vector>

#include <ceng/datatypes/aligned-buffer.h>

#include "texture-unit.h"

#include "shader-const-data.h"

namespace Ceng
{
	class CR_PixelShader;

	class ShaderLinkInstance;

	class PixelShaderInstanceCommon
	{
	public:

		CR_PixelShader* shader;

		AlignedBuffer<Ceng::UINT8*> uniformPtr;

		AlignedBuffer<Ceng::UINT8> uniformBuffer;

		ShaderLinkInstance* link;

		UINT32 quadSizeBytes;

		std::vector<TextureUnit> textureUnits;

		UINT32 activeRenderTargets;

		std::shared_ptr<CR_NewTargetData> targetHandles[2 + CRENDER_MAX_COLOR_TARGETS];

	public:

		PixelShaderInstanceCommon() = delete;

		PixelShaderInstanceCommon(CR_PixelShader* shader);

		PixelShaderInstanceCommon(const PixelShaderInstanceCommon& source);

		const CRESULT ConfigureUniforms(const std::vector<CR_ShaderConstantData>& uniformList,
			const Ceng::UINT32 bufferSize);
	};
}

#endif