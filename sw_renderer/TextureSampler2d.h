#pragma once

#ifndef CENG_TEXTURE_SAMPLER_2D_H
#define CENG_TEXTURE_SAMPLER_2D_H

#include <ceng/swshader/PShaderTextureUnitSampler.h>

#include "cr-sampler-state.h"
#include "cr-shader-view-tex2d.h"


namespace Ceng::Pshader
{
	class TextureSampler2d : public PShaderTextureUnitSampler
	{
	public:

	protected:

		Ceng::CR_ShaderViewTex2D* view;
		Ceng::CR_SamplerState* sampler;

		~TextureSampler2d() override;

	public:

		TextureSampler2d(CR_ShaderViewTex2D* view, CR_SamplerState* sampler);

		void Release() override;		

		void Sample1d(const Pshader::Float& coords, Ceng::FLOAT32* destAddress) override;

		void Sample1dArray(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) override;

		void Sample2d(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) override;

		void Sample2dArray(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) override;

		void Sample3d(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) override;

		void SampleCube(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) override;

	protected:

		typedef void (TextureSampler2d::* FilterFunction)(const Ceng::INT32*, const Ceng::INT32*, Ceng::UINT32,
			const Ceng::FLOAT32, Ceng::FLOAT32*);

		static FilterFunction minFilterTable[16];

		static FilterFunction magFilterTable[8];

		void Nearest_Port(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Nearest_SSE2(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Linear_Port(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Linear_SSE2(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Nearest_MipNearest_Port(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Nearest_MipNearest_SSE2(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Linear_MipNearest_Port(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Linear_MipNearest_SSE2(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Nearest_MipLinear(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);

		void Linear_MipLinear(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::FLOAT32* out_color);
	};
}

#endif