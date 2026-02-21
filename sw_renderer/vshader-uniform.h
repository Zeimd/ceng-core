#pragma once

#ifndef CENG_SWRENDER_VSHADER_UNIFORM_H
#define CENG_SWRENDER_VSHADER_UNIFORM_H

#include <ceng/math/ce-matrix.h>

namespace Ceng::Vshader
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

	struct VertexShaderUniform
	{
		Vshader::UniformBase* variable;
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

	class UniformMat4x4 : public UniformBase
	{
	public:

	};

	inline VectorF4 operator * (const UniformMat4x4& matrix, const VectorF4& vector)
	{
		Ceng::Matrix4* localMatrix = (Ceng::Matrix4*)matrix.dataPtr;

		return *localMatrix * vector;
	}

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
}

#endif