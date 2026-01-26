#pragma once

#ifndef CENG_PSHADER_UNIFORM_H
#define CENG_PSHADER_UNIFORM_H

namespace Ceng::Pshader
{
	class UniformBase
	{
	public:
		void* dataPtr;
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

	typedef void (*CallbackSampler2d)();

	class UniformSampler2d : public UniformBase
	{
	public:

		CallbackSampler2d sampler;
	};
}

#endif