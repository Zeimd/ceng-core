#pragma once

#ifndef CENG_TEXTURE_SAMPLER_2D_H
#define CENG_TEXTURE_SAMPLER_2D_H

#include <ceng/swshader/PShaderTextureUnitSampler.h>

namespace Ceng
{
	class CR_ShaderViewTex2D;
	class CR_SamplerState;
}

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

		//*********************************************
		// Samplers that output 4x Float4 in SOA

		void Sample1d_Float(const Pshader::Float& coords, Ceng::FLOAT32* destAddress) override;

		void Sample1dArray_Float(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) override;

		void Sample2d_Float(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) override;

		void Sample2dArray_Float(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) override;

		void Sample3d_Float(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) override;

		void SampleCube_Float(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) override;

		//*********************************************
		// Samplers that output 4x Unbyte4 in SOA
		// Purpose is to allow fast-track when texture read is written directly into render target of
		// this format.

		void Sample1d_Unbyte(const Pshader::Float& coords, Ceng::UINT8* destAddress) override;

		void Sample1dArray_Unbyte(const Pshader::Float2& coords, Ceng::UINT8* destAddress) override;

		void Sample2d_Unbyte(const Pshader::Float2& coords, Ceng::UINT8* destAddress) override;

		void Sample2dArray_Unbyte(const Pshader::Float3& coords, Ceng::UINT8* destAddress) override;

		void Sample3d_Unbyte(const Pshader::Float3& coords, Ceng::UINT8* destAddress) override;

		void SampleCube_Unbyte(const Pshader::Float3& coords, Ceng::UINT8* destAddress) override;

		//*********************************************
		// Samplers that output 4x Nbyte4 in SOA

		void Sample1d_Nbyte(const Pshader::Float& coords, Ceng::INT8* destAddress) override;

		void Sample1dArray_Nbyte(const Pshader::Float2& coords, Ceng::INT8* destAddress) override;

		void Sample2d_Nbyte(const Pshader::Float2& coords, Ceng::INT8* destAddress) override;

		void Sample2dArray_Nbyte(const Pshader::Float3& coords, Ceng::INT8* destAddress) override;

		void Sample3d_Nbyte(const Pshader::Float3& coords, Ceng::INT8* destAddress) override;

		void SampleCube_Nbyte(const Pshader::Float3& coords, Ceng::INT8* destAddress) override;

		//*********************************************
		// Samplers that output 4x Uint4 in SOA

		void Sample1d_Uint(const Pshader::Float& coords, Ceng::UINT32* destAddress) override;

		void Sample1dArray_Uint(const Pshader::Float2& coords, Ceng::UINT32* destAddress) override;

		void Sample2d_Uint(const Pshader::Float2& coords, Ceng::UINT32* destAddress) override;

		void Sample2dArray_Uint(const Pshader::Float3& coords, Ceng::UINT32* destAddress) override;

		void Sample3d_Uint(const Pshader::Float3& coords, Ceng::UINT32* destAddress) override;

		void SampleCube_Uint(const Pshader::Float3& coords, Ceng::UINT32* destAddress) override;

		//*********************************************
		// Samplers that output 4x Int4 in SOA

		void Sample1d_Int(const Pshader::Float& coords, Ceng::INT32* destAddress) override;

		void Sample1dArray_Int(const Pshader::Float2& coords, Ceng::INT32* destAddress) override;

		void Sample2d_Int(const Pshader::Float2& coords, Ceng::INT32* destAddress) override;

		void Sample2dArray_Int(const Pshader::Float3& coords, Ceng::INT32* destAddress) override;

		void Sample3d_Int(const Pshader::Float3& coords, Ceng::INT32* destAddress) override;

		void SampleCube_Int(const Pshader::Float3& coords, Ceng::INT32* destAddress) override;

	protected:

		typedef void (TextureSampler2d::* FilterFunction_unbyte)(const Ceng::INT32*, const Ceng::INT32*, Ceng::UINT32,
			const Ceng::FLOAT32, Ceng::UINT8*);

		static FilterFunction_unbyte minFilterTable_unbyte[16];

		static FilterFunction_unbyte magFilterTable_unbyte[8];

		void Nearest_Port_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Nearest_SSE2_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Linear_Port_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Linear_SSE2_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Nearest_MipNearest_Port_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Nearest_MipNearest_SSE2_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Linear_MipNearest_Port_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Linear_MipNearest_SSE2_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Nearest_MipLinear_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);

		void Linear_MipLinear_unbyte(const Ceng::INT32* uFX, const Ceng::INT32* vFX, Ceng::UINT32 mipLevel,
			const Ceng::FLOAT32 mipFactor, Ceng::UINT8* out_color);
	};
}

#endif