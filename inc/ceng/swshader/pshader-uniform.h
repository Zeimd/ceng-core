#pragma once

#ifndef CENG_PSHADER_UNIFORM_H
#define CENG_PSHADER_UNIFORM_H

#include "PShaderTextureUnitSampler.h"

namespace Ceng::Pshader
{
	class UniformBase
	{
	public:
		void* dataPtr;

	public:

		UniformBase()
			: dataPtr(nullptr)
		{

		}
	};

	struct PixelShaderUniform
	{
		Pshader::UniformBase* variable;
	};

	class UniformFloat : public UniformBase
	{

	};

	class UniformFloat2 : public UniformBase
	{

	};

	class UniformFloat3 : public UniformBase
	{

	};

	class UniformFloat4 : public UniformBase
	{

	};

	class UniformInt : public UniformBase
	{

	};

	class UniformInt2 : public UniformBase
	{

	};

	class UniformInt3 : public UniformBase
	{

	};

	class UniformInt4 : public UniformBase
	{

	};

	class UniformUInt : public UniformBase
	{

	};

	class UniformUInt2 : public UniformBase
	{

	};

	class UniformUInt3 : public UniformBase
	{

	};

	class UniformUInt4 : public UniformBase
	{

	};

	class UniformBool : public UniformBase
	{

	};

	class UniformBool2 : public UniformBase
	{

	};

	class UniformBool3 : public UniformBase
	{

	};

	class UniformBool4 : public UniformBase
	{

	};

	class UniformSampler2d : public UniformBase
	{
	public:

		PShaderTextureUnitSampler* sampler;

	public:
		
	};
}

#endif