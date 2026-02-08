#pragma once

#ifndef CENG_TEXTURE_UNIT_SAMPLER_H
#define CENG_TEXTURE_UNIT_SAMPLER_H

#include "../interfaces/base-interface.h"

#include "pshader-types.h"

namespace Ceng::Pshader
{
	class PShaderTextureUnitSampler : public BASE_INTERFACE
	{
	protected:

		~PShaderTextureUnitSampler() override
		{

		}

	public:

		//*********************************************
		// Samplers that output 4x Float4 in SOA

		virtual void Sample1d_Float(const Pshader::Float& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample1dArray_Float(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample2d_Float(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample2dArray_Float(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample3d_Float(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void SampleCube_Float(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) = 0;

		//*********************************************
		// Samplers that output 4x Unbyte4 in SOA
		// Purpose is to allow fast-track when texture read is written directly into render target of
		// this format.

		virtual void Sample1d_Unbyte(const Pshader::Float& coords, Ceng::UINT8* destAddress) = 0;

		virtual void Sample1dArray_Unbyte(const Pshader::Float2& coords, Ceng::UINT8* destAddress) = 0;

		virtual void Sample2d_Unbyte(const Pshader::Float2& coords, Ceng::UINT8* destAddress) = 0;

		virtual void Sample2dArray_Unbyte(const Pshader::Float3& coords, Ceng::UINT8* destAddress) = 0;

		virtual void Sample3d_Unbyte(const Pshader::Float3& coords, Ceng::UINT8* destAddress) = 0;

		virtual void SampleCube_Unbyte(const Pshader::Float3& coords, Ceng::UINT8* destAddress) = 0;

		//*********************************************
		// Samplers that output 4x Nbyte4 in SOA

		virtual void Sample1d_Nbyte(const Pshader::Float& coords, Ceng::INT8* destAddress) = 0;

		virtual void Sample1dArray_Nbyte(const Pshader::Float2& coords, Ceng::INT8* destAddress) = 0;

		virtual void Sample2d_Nbyte(const Pshader::Float2& coords, Ceng::INT8* destAddress) = 0;

		virtual void Sample2dArray_Nbyte(const Pshader::Float3& coords, Ceng::INT8* destAddress) = 0;

		virtual void Sample3d_Nbyte(const Pshader::Float3& coords, Ceng::INT8* destAddress) = 0;

		virtual void SampleCube_Nbyte(const Pshader::Float3& coords, Ceng::INT8* destAddress) = 0;

		//*********************************************
		// Samplers that output 4x Uint4 in SOA

		virtual void Sample1d_Uint(const Pshader::Float& coords, Ceng::UINT32* destAddress) = 0;

		virtual void Sample1dArray_Uint(const Pshader::Float2& coords, Ceng::UINT32* destAddress) = 0;

		virtual void Sample2d_Uint(const Pshader::Float2& coords, Ceng::UINT32* destAddress) = 0;

		virtual void Sample2dArray_Uint(const Pshader::Float3& coords, Ceng::UINT32* destAddress) = 0;

		virtual void Sample3d_Uint(const Pshader::Float3& coords, Ceng::UINT32* destAddress) = 0;

		virtual void SampleCube_Uint(const Pshader::Float3& coords, Ceng::UINT32* destAddress) = 0;

		//*********************************************
		// Samplers that output 4x Int4 in SOA

		virtual void Sample1d_Int(const Pshader::Float& coords, Ceng::INT32* destAddress) = 0;

		virtual void Sample1dArray_Int(const Pshader::Float2& coords, Ceng::INT32* destAddress) = 0;

		virtual void Sample2d_Int(const Pshader::Float2& coords, Ceng::INT32* destAddress) = 0;

		virtual void Sample2dArray_Int(const Pshader::Float3& coords, Ceng::INT32* destAddress) = 0;

		virtual void Sample3d_Int(const Pshader::Float3& coords, Ceng::INT32* destAddress) = 0;

		virtual void SampleCube_Int(const Pshader::Float3& coords, Ceng::INT32* destAddress) = 0;
		
	};
}

#endif