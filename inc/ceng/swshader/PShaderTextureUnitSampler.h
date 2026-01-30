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

		virtual void Sample1d(const Pshader::Float& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample1dArray(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample2d(const Pshader::Float2& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample2dArray(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void Sample3d(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) = 0;

		virtual void SampleCube(const Pshader::Float3& coords, Ceng::FLOAT32* destAddress) = 0;

	};
}

#endif