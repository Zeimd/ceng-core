#pragma once

#include "pshader-types.h"
#include "pshader-uniform.h"

namespace Ceng::Pshader
{
	class DelayedSampler2D
	{
	public:

		Pshader::PShaderTextureUnitSampler* unit;
		Pshader::Float2* uv;

		void* dataAddress;

	public:

		DelayedSampler2D() : unit(nullptr), uv(nullptr), dataAddress(nullptr)
		{
		}

		DelayedSampler2D(PShaderTextureUnitSampler* unit, Pshader::Float2* uv)
			: unit(unit), uv(uv), dataAddress(nullptr)
		{

		}

		void SampleToFloat4(void* destBuffer) const;
		void SampleToUnbyte4(void* destBuffer) const;
		void SampleToNbyte4(void* destBuffer) const;
		void SampleToInt4(void* destBuffer) const;
		void SampleToUint4(void* destBuffer) const;
	};

	//**********************************************************
	// SampleTexture2D methods

	inline void DelayedSampler2D::SampleToFloat4(void* destBuffer) const
	{
		unit->Sample2d_Float(*uv, (Ceng::FLOAT32*)destBuffer);
	}

	inline void DelayedSampler2D::SampleToUnbyte4(void* destBuffer) const
	{
		unit->Sample2d_Unbyte(*uv, (Ceng::UINT8*)destBuffer);
	}

	inline void DelayedSampler2D::SampleToNbyte4(void* destBuffer) const
	{
		unit->Sample2d_Nbyte(*uv, (Ceng::INT8*)destBuffer);
	}

	inline void DelayedSampler2D::SampleToInt4(void* destBuffer) const
	{
		unit->Sample2d_Int(*uv, (Ceng::INT32*)destBuffer);
	}

	inline void DelayedSampler2D::SampleToUint4(void* destBuffer) const
	{
		unit->Sample2d_Uint(*uv, (Ceng::UINT32*)destBuffer);
	}

	inline DelayedSampler2D sample2d(Pshader::UniformSampler2d& sampler, Pshader::Float2& uv)
	{
		return DelayedSampler2D(sampler.sampler, &uv);
	}
}