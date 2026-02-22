#pragma once

#ifndef CENG_SWRENDER_VSHADER_TYPES_H
#define CENG_SWRENDER_VSHADER_TYPES_H

#include <ceng/datatypes/basic-types.h>

#include "vshader-input.h"

namespace Ceng::Vshader
{
	class Float;
	class Float2;
	class Float3;
	class Float4;

	//********************************************************************************

	class Float
	{
	public:
		Ceng::FLOAT32 x;

	public:

		inline Float(Ceng::FLOAT32 x)
			: x(x)
		{

		}

		inline Float(const Float& source)
			: x(source.x)
		{

		}

		inline Float(const Vshader::InFloat& source)
			: x(source)
		{
			
		}

		// Operators: self

		inline Float& operator = (const Float& other)
		{
			x = other.x;
			return *this;
		}

		inline Float& operator += (const Float& other)
		{
			x += other.x;
			return *this;
		}

		inline Float& operator -= (const Float& other)
		{
			x -= other.x;
			return *this;
		}

		inline Float& operator *= (const Float& other)
		{
			x *= other.x;
			return *this;
		}

		inline Float& operator /= (const Float& other)
		{
			x /= other.x;
			return *this;
		}

		inline Ceng::BOOL operator == (const Float& other) const
		{
			return x == other.x;
		}

		inline Ceng::BOOL operator != (const Float& other) const
		{
			return x != other.x;
		}

		inline Ceng::BOOL operator < (const Float& other) const
		{
			return x < other.x;
		}

		inline Ceng::BOOL operator <= (const Float& other) const
		{
			return x <= other.x;
		}

		inline Ceng::BOOL operator > (const Float& other) const
		{
			return x > other.x;
		}

		inline Ceng::BOOL operator >= (const Float& other) const
		{
			return x >= other.x;
		}

		// Operators: Ceng::FLOAT32

		inline Float& operator = (Ceng::FLOAT32 other)
		{
			x = other;
			return *this;
		}

		inline Float& operator += (Ceng::FLOAT32 other)
		{
			x += other;
			return *this;
		}

		inline Float& operator -= (Ceng::FLOAT32 other)
		{
			x -= other;
			return *this;
		}

		inline Float& operator *= (Ceng::FLOAT32 other)
		{
			x *= other;
			return *this;
		}

		inline Float& operator /= (Ceng::FLOAT32 other)
		{
			x /= other;
			return *this;
		}

		inline Ceng::BOOL operator == (Ceng::FLOAT32 other) const
		{
			return x == other;
		}

		inline Ceng::BOOL operator != (Ceng::FLOAT32 other) const
		{
			return x != other;
		}

		inline Ceng::BOOL operator < (Ceng::FLOAT32 other) const
		{
			return x < other;
		}

		inline Ceng::BOOL operator <= (Ceng::FLOAT32 other) const
		{
			return x <= other;
		}

		inline Ceng::BOOL operator > (Ceng::FLOAT32 other) const
		{
			return x > other;
		}

		inline Ceng::BOOL operator >= (Ceng::FLOAT32 other) const
		{
			return x >= other;
		}

		// Operators: InFloat

		inline Float& operator = (const Vshader::InFloat& other)
		{
			x = (Ceng::FLOAT32)other;
			return *this;
		}

		inline Float& operator += (const Vshader::InFloat& other)
		{
			x += (Ceng::FLOAT32)other;
			return *this;
		}

		inline Float& operator -= (const Vshader::InFloat& other)
		{
			x -= (Ceng::FLOAT32)other;
			return *this;
		}

		inline Float& operator *= (const Vshader::InFloat& other)
		{
			x *= (Ceng::FLOAT32)other;
			return *this;
		}

		inline Float& operator /= (const Vshader::InFloat& other)
		{
			x /= (Ceng::FLOAT32)other;
			return *this;
		}

		inline Ceng::BOOL operator == (const Vshader::InFloat& other) const
		{
			return x == (Ceng::FLOAT32)other;
		}

		inline Ceng::BOOL operator != (const Vshader::InFloat& other) const
		{
			return x != (Ceng::FLOAT32)other;
		}

		inline Ceng::BOOL operator < (const Vshader::InFloat& other) const
		{
			return x < (Ceng::FLOAT32)other;
		}

		inline Ceng::BOOL operator <= (const Vshader::InFloat& other) const
		{
			return x <= (Ceng::FLOAT32)other;
		}

		inline Ceng::BOOL operator > (const Vshader::InFloat& other) const
		{
			return x > (Ceng::FLOAT32)other;
		}

		inline Ceng::BOOL operator >= (const Vshader::InFloat& other) const
		{
			return x >= (Ceng::FLOAT32)other;
		}
	};

	// Binary operators, Float-Float

	inline Float operator + (const Float& a, const Float& b)
	{
		Float temp{ a };
		return temp += b;
	}

	inline Float operator - (const Float& a, const Float& b)
	{
		Float temp{ a };
		return temp -= b;
	}

	inline Float operator * (const Float& a, const Float& b)
	{
		Float temp{ a };
		return temp *= b;
	}

	inline Float operator / (const Float& a, const Float& b)
	{
		Float temp{ a };
		return temp /= b;
	}

	// Binary operators, FLOAT32-Float

	inline Ceng::FLOAT32 operator + (Ceng::FLOAT32 a, const Float& b)
	{
		return a + b.x;
	}

	inline Ceng::FLOAT32 operator - (Ceng::FLOAT32 a, const Float& b)
	{
		return a - b.x;
	}

	inline Ceng::FLOAT32 operator * (Ceng::FLOAT32 a, const Float& b)
	{
		return a * b.x;
	}

	inline Ceng::FLOAT32 operator / (Ceng::FLOAT32 a, const Float& b)
	{
		return a / b.x;
	}

	inline Ceng::BOOL operator == (Ceng::FLOAT32 a, const Float& b)
	{
		return a == b.x;
	}

	inline Ceng::BOOL operator != (Ceng::FLOAT32 a, const Float& b)
	{
		return a != b.x;
	}

	inline Ceng::BOOL operator > (Ceng::FLOAT32 a, const Float& b)
	{
		return a > b.x;
	}

	inline Ceng::BOOL operator >= (Ceng::FLOAT32 a, const Float& b)
	{
		return a >= b.x;
	}

	inline Ceng::BOOL operator < (Ceng::FLOAT32 a, const Float& b)
	{
		return a < b.x;
	}

	inline Ceng::BOOL operator <= (Ceng::FLOAT32 a, const Float& b)
	{
		return a <= b.x;
	}

	// Binary operators, InFloat-Float

	inline Float operator + (const Vshader::InFloat& a, const Float& b)
	{
		return (Ceng::FLOAT32)a + b.x;
	}

	inline Float operator - (const Vshader::InFloat& a, const Float& b)
	{
		return (Ceng::FLOAT32)a - b.x;
	}

	inline Float operator * (const Vshader::InFloat& a, const Float& b)
	{
		return (Ceng::FLOAT32)a * b.x;
	}

	inline Float operator / (const Vshader::InFloat& a, const Float& b)
	{
		return (Ceng::FLOAT32)a / b.x;
	}

	inline Ceng::BOOL operator == (const Vshader::InFloat& a, const Float& b)
	{
		return b == a;
	}

	inline Ceng::BOOL operator != (const Vshader::InFloat& a, const Float& b)
	{
		return b != a;
	}

	inline Ceng::BOOL operator < (const Vshader::InFloat& a, const Float& b)
	{
		return b < a;
	}

	inline Ceng::BOOL operator <= (const Vshader::InFloat& a, const Float& b)
	{
		return b <= a;
	}

	inline Ceng::BOOL operator > (const Vshader::InFloat& a, const Float& b)
	{
		return b > a;
	}

	inline Ceng::BOOL operator >= (const Vshader::InFloat& a, const Float& b)
	{
		return b >= a;
	}

	// Binary operators, InFloat-FLOAT32

	inline Float operator + (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a + b;
	}

	inline Float operator - (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a - b;
	}

	inline Float operator * (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a * b;
	}

	inline Float operator / (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a / b;
	}

	inline Ceng::BOOL operator == (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a == b;
	}

	inline Ceng::BOOL operator != (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a != b;
	}

	inline Ceng::BOOL operator < (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a < b;
	}

	inline Ceng::BOOL operator <= (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a <= b;
	}

	inline Ceng::BOOL operator > (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a > b;
	}

	inline Ceng::BOOL operator >= (const Vshader::InFloat& a, Ceng::FLOAT32 b)
	{
		return (Ceng::FLOAT32)a >= b;
	}

}

#endif