#pragma once

#ifndef CENG_SWRENDER_VSHADER_TYPES_H
#define CENG_SWRENDER_VSHADER_TYPES_H

#include <ceng/datatypes/basic-types.h>

#include "vshader-input.h"

namespace Ceng::Vshader
{
	class Bool;
	class Bool2;
	class Bool3;
	class Bool4;

	class Float;
	class Float2;
	class Float3;
	class Float4;

	//********************************************************************************

	class Bool
	{
	public:
		Ceng::BOOL x;

	public:

		inline Bool(const Bool& other)
			: x(other.x)
		{

		}

		inline Bool(bool x)
			: x(x)
		{

		}

		inline Bool(Ceng::BOOL x)
			: x(x)
		{

		}
	};

	inline Bool operator == (const Bool& a, const Bool& b)
	{
		return a.x == b.x;
	}

	inline Bool operator != (const Bool& a, const Bool& b)
	{
		return a.x != b.x;
	}

	//********************************************************************************

	class Bool2
	{
	public:
		Ceng::BOOL x;
		Ceng::BOOL y;

	public:

		inline Bool2(const Bool2& other)
			: x(other.x), y(other.y)
		{

		}

		inline Bool2(bool x, bool y)
			: x(x), y(y)
		{

		}

		inline Bool2(Ceng::BOOL x, Ceng::BOOL y)
			: x(x), y(y)
		{

		}

		inline Bool2 operator == (const Bool2& other)
		{
			return { x == other.x, y == other.y };
		}

		inline Bool2 operator != (const Bool2& other)
		{
			return { x != other.x, y != other.y };
		}
	};

	//********************************************************************************

	class Bool3
	{
	public:
		Ceng::BOOL x;
		Ceng::BOOL y;
		Ceng::BOOL z;

	public:

		inline Bool3(const Bool3& other)
			: x(other.x), y(other.y), z(other.z)
		{

		}

		inline Bool3(bool x, bool y, bool z)
			: x(x), y(y), z(z)
		{

		}

		inline Bool3(Ceng::BOOL x, Ceng::BOOL y, Ceng::BOOL z)
			: x(x), y(y),z(z)
		{

		}

		inline Bool3 operator == (const Bool3& other)
		{
			return { x == other.x, y == other.y, z == other.z };
		}

		inline Bool3 operator != (const Bool3& other)
		{
			return { x != other.x, y != other.y, z != other.z };
		}
	};

	//********************************************************************************

	class Bool4
	{
	public:
		Ceng::BOOL x;
		Ceng::BOOL y;
		Ceng::BOOL z;
		Ceng::BOOL w;

	public:

		inline Bool4(const Bool4& other)
			: x(other.x), y(other.y), z(other.z), w(other.w)
		{

		}

		inline Bool4(bool x, bool y, bool z, bool w)
			: x(x), y(y), z(z), w(w)
		{

		}

		inline Bool4(Ceng::BOOL x, Ceng::BOOL y, Ceng::BOOL z, Ceng::BOOL w)
			: x(x), y(y), z(z), w(w)
		{

		}

		inline Bool4 operator == (const Bool4& other)
		{
			return { x == other.x, y == other.y, z == other.z, w == other.w };
		}

		inline Bool4 operator != (const Bool4& other)
		{
			return { x != other.x, y != other.y, z != other.z, w != other.w };
		}
	};


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

	inline Float operator + (Ceng::FLOAT32 a, const Float& b)
	{
		return a + b.x;
	}

	inline Float operator - (Ceng::FLOAT32 a, const Float& b)
	{
		return a - b.x;
	}

	inline Float operator * (Ceng::FLOAT32 a, const Float& b)
	{
		return a * b.x;
	}

	inline Float operator / (Ceng::FLOAT32 a, const Float& b)
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

	//********************************************************************************

	class alignas(8) Float2
	{
	public:
		Ceng::FLOAT32 x;
		Ceng::FLOAT32 y;

	public:

		inline Float2(Ceng::FLOAT32 x, Ceng::FLOAT32 y)
			: x(x),y(y)
		{

		}

		inline Float2(const Float2& source)
			: x(source.x), y(source.y)
		{

		}

		inline Float2(const VectorF2& source)
			: x(source.x), y(source.y)
		{

		}

		inline Float2(const Vshader::InFloat2& source)			
		{
			Ceng::VectorF2 temp = source;

			x = temp.x;
			y = temp.y;

		}

		// Operators: self

		inline Float2& operator = (const Float2& other)
		{
			x = other.x;
			y = other.y;

			return *this;
		}

		inline Float2& operator += (const Float2& other)
		{
			x += other.x;
			y += other.y;

			return *this;
		}

		inline Float2& operator -= (const Float2& other)
		{
			x -= other.x;
			y -= other.y;

			return *this;
		}

		inline Float2& operator *= (const Float2& other)
		{
			x *= other.x;
			y *= other.y;

			return *this;
		}

		inline Float2& operator /= (const Float2& other)
		{
			x /= other.x;
			y /= other.y;

			return *this;
		}

		inline Ceng::BOOL operator == (const Float2& other) const
		{
			return (x == other.x) && (y == other.y);
		}

		inline Ceng::BOOL operator != (const Float2& other) const
		{
			return (x != other.x) || (y != other.y);
		}

		// Operators: Ceng::FLOAT32

		inline Float2& operator *= (Ceng::FLOAT32 other)
		{
			x *= other;
			y *= other;

			return *this;
		}

		inline Float2& operator /= (Ceng::FLOAT32 other)
		{
			x /= other;
			y /= other;

			return *this;
		}

		inline Ceng::BOOL operator == (const Ceng::VectorF2& other) const
		{
			return (x == other.x) && (y == other.y);
		}

		inline Ceng::BOOL operator != (const Ceng::VectorF2& other) const
		{
			return (x == other.x) && (y == other.y);
		}

		// Operators: InFloat

		inline Float2& operator *= (const Vshader::InFloat& other)
		{
			x *= (Ceng::FLOAT32)other;
			y *= (Ceng::FLOAT32)other;

			return *this;
		}

		inline Float2& operator /= (const Vshader::InFloat& other)
		{
			x /= (Ceng::FLOAT32)other;
			y /= (Ceng::FLOAT32)other;

			return *this;
		}

		inline Ceng::BOOL operator == (const Vshader::InFloat2& other) const
		{
			Ceng::VectorF2 temp = other;

			return (x == temp.x) && (y == temp.y);
		}

		inline Ceng::BOOL operator != (const Vshader::InFloat2& other) const
		{
			Ceng::VectorF2 temp = other;

			return (x == temp.x) && (y == temp.y);
		}
	};

	// Binary operators, Float2-Float2

	inline Float2 operator + (const Float2& a, const Float2& b)
	{
		Float2 temp{ a };
		return temp += b;
	}

	inline Float2 operator - (const Float2& a, const Float2& b)
	{
		Float2 temp{ a };
		return temp -= b;
	}

	inline Float2 operator * (const Float2& a, const Float2& b)
	{
		Float2 temp{ a };
		return temp *= b;
	}

	inline Float2 operator / (const Float2& a, const Float2& b)
	{
		Float2 temp{ a };
		return temp /= b;
	}

	// Binary operators, InFloat2-FLOAT32

	inline Float2 operator * (const Vshader::InFloat2& a, Ceng::FLOAT32 b)
	{
		return (Ceng::VectorF2)a * b;
	}

	inline Float2 operator / (const Vshader::InFloat2& a, Ceng::FLOAT32 b)
	{
		return (Ceng::VectorF2)a / b;
	}

	// Binary operators, Float2-Float

	inline Float2 operator * (const Float2& a, const Float& b)
	{
		return a * b;
	}

	inline Float2 operator / (const Float2& a, const Float& b)
	{
		return a / b;
	}

	// Binary operators, Float2-FLOAT32

	inline Float2 operator * (const Float2& a, Ceng::FLOAT32 b)
	{
		return a * b;
	}

	inline Float2 operator / (const Float2& a, Ceng::FLOAT32 b)
	{
		return a / b;
	}

	// Binary operators InFloat-Float2

	inline Float2 operator * (const Vshader::InFloat& a, const Float2& b)
	{
		return b * (Ceng::FLOAT32)a;
	}

	// Binary operators, Float2-Infloat

	inline Float2 operator * (const Float2& a, const Vshader::InFloat& b)
	{
		Float2 temp{ a };
		return temp *= a;
	}

	inline Float2 operator / (const Float2& a, const Vshader::InFloat& b)
	{
		Float2 temp{ a };
		return temp /= a;
	}

	// Binary operators, FLOAT32-Float2

	inline Float2 operator * (Ceng::FLOAT32 a, const Float2& b)
	{
		Float2 temp{ b };
		return temp *= a;
	}

	// Binary operators, InFloat2-Float2

	inline Float2 operator + (const Vshader::InFloat2& a, const Float2& b)
	{
		return (Ceng::VectorF2)a + b;
	}

	inline Float2 operator - (const Vshader::InFloat2& a, const Float2& b)
	{
		return (Ceng::VectorF2)a - b;
	}

	inline Float2 operator * (const Vshader::InFloat2& a, const Float2& b)
	{
		return (Ceng::VectorF2)a * b;
	}

	inline Float2 operator / (const Vshader::InFloat2& a, const Float2& b)
	{
		return (Ceng::VectorF2)a / b;
	}

	inline Ceng::BOOL operator == (const Vshader::InFloat2& a, const Float2& b)
	{
		return b == a;
	}

	inline Ceng::BOOL operator != (const Vshader::InFloat2& a, const Float2& b)
	{
		return b != a;
	}

	//********************************************************************************

	class alignas(16) Float3
	{
	public:
		Ceng::FLOAT32 x;
		Ceng::FLOAT32 y;
		Ceng::FLOAT32 z;
		Ceng::FLOAT32 padding;

	public:

		inline Float3(Ceng::FLOAT32 x, Ceng::FLOAT32 y, Ceng::FLOAT32 z)
			: x(x), y(y), z(z)
		{

		}

		inline Float3(const Float3& source)
			: x(source.x), y(source.y), z(source.z)
		{

		}

		inline Float3(const VectorF3& source)
			: x(source.x), y(source.y), z(source.z)
		{

		}

		inline Float3(const Vshader::InFloat3& source)
		{
			Ceng::VectorF3 temp = source;

			x = temp.x;
			y = temp.y;
			z = temp.z;
		}

		// Operators: self

		inline Float3& operator = (const Float3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;

			return *this;
		}

		inline Float3& operator += (const Float3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		inline Float3& operator -= (const Float3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		inline Float3& operator *= (const Float3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		inline Float3& operator /= (const Float3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
		
			return *this;
		}

		inline Ceng::BOOL operator == (const Float3& other) const
		{
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		inline Ceng::BOOL operator != (const Float3& other) const
		{
			return (x != other.x) || (y != other.y) || (z != other.z);
		}

		// Operators: Ceng::FLOAT32

		inline Float3& operator *= (Ceng::FLOAT32 other)
		{
			x *= other;
			y *= other;
			z *= other;

			return *this;
		}

		inline Float3& operator /= (Ceng::FLOAT32 other)
		{
			x /= other;
			y /= other;
			z *= other;

			return *this;
		}

		inline Ceng::BOOL operator == (const Ceng::VectorF3& other) const
		{
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		inline Ceng::BOOL operator != (const Ceng::VectorF3& other) const
		{
			return (x != other.x) || (y != other.y) || (z != other.z);
		}

		// Operators: InFloat

		inline Float3& operator *= (const Vshader::InFloat& other)
		{
			x *= (Ceng::FLOAT32)other;
			y *= (Ceng::FLOAT32)other;
			z *= (Ceng::FLOAT32)other;

			return *this;
		}

		inline Float3& operator /= (const Vshader::InFloat& other)
		{
			x /= (Ceng::FLOAT32)other;
			y /= (Ceng::FLOAT32)other;
			z /= (Ceng::FLOAT32)other;

			return *this;
		}

		inline Ceng::BOOL operator == (const Vshader::InFloat3& other) const
		{
			Ceng::VectorF3 temp = other;

			return (x == temp.x) && (y == temp.y) && (z == temp.z);
		}

		inline Ceng::BOOL operator != (const Vshader::InFloat3& other) const
		{
			Ceng::VectorF3 temp = other;

			return (x != temp.x) || (y != temp.y) || (z != temp.z);
		}
	};

	// Binary operators, Float3-Float3

	inline Float3 operator + (const Float3& a, const Float3& b)
	{
		Float3 temp{ a };
		return temp += b;
	}

	inline Float3 operator - (const Float3& a, const Float3& b)
	{
		Float3 temp{ a };
		return temp -= b;
	}

	inline Float3 operator * (const Float3& a, const Float3& b)
	{
		Float3 temp{ a };
		return temp *= b;
	}

	inline Float3 operator / (const Float3& a, const Float3& b)
	{
		Float3 temp{ a };
		return temp /= b;
	}

	// Binary operators, InFloat3-FLOAT32

	inline Float3 operator * (const Vshader::InFloat3& a, Ceng::FLOAT32 b)
	{
		return (Ceng::VectorF3)a * b;
	}

	inline Float3 operator / (const Vshader::InFloat3& a, Ceng::FLOAT32 b)
	{
		return (Ceng::VectorF3)a / b;
	}

	// Binary operators, Float3-Float

	inline Float3 operator * (const Float3& a, const Float& b)
	{
		return a * b;
	}

	inline Float3 operator / (const Float3& a, const Float& b)
	{
		return a / b;
	}

	// Binary operators, Float3-FLOAT32

	inline Float3 operator * (const Float3& a, Ceng::FLOAT32 b)
	{
		return a * b;
	}

	inline Float3 operator / (const Float3& a, Ceng::FLOAT32 b)
	{
		return a / b;
	}

	// Binary operators InFloat-Float3

	inline Float3 operator * (const Vshader::InFloat& a, const Float3& b)
	{
		return b * (Ceng::FLOAT32)a;
	}

	// Binary operators, Float3-Infloat

	inline Float3 operator * (const Float3& a, const Vshader::InFloat& b)
	{
		Float3 temp{ a };
		return temp *= a;
	}

	inline Float3 operator / (const Float3& a, const Vshader::InFloat& b)
	{
		Float3 temp{ a };
		return temp /= a;
	}

	// Binary operators, FLOAT32-Float3

	inline Float3 operator * (Ceng::FLOAT32 a, const Float3& b)
	{
		Float3 temp{ b };
		return temp *= a;
	}

	// Binary operators, InFloat3-Float3

	inline Float3 operator + (const Vshader::InFloat3& a, const Float3& b)
	{
		return (Ceng::VectorF3)a + b;
	}

	inline Float3 operator - (const Vshader::InFloat3& a, const Float3& b)
	{
		return (Ceng::VectorF3)a - b;
	}

	inline Float3 operator * (const Vshader::InFloat3& a, const Float3& b)
	{
		return (Ceng::VectorF3)a * b;
	}

	inline Float3 operator / (const Vshader::InFloat3& a, const Float3& b)
	{
		return (Ceng::VectorF3)a / b;
	}

	inline Ceng::BOOL operator == (const Vshader::InFloat3& a, const Float3& b)
	{
		return b == a;
	}

	inline Ceng::BOOL operator != (const Vshader::InFloat3& a, const Float3& b)
	{
		return b != a;
	}

	//********************************************************************************

	class alignas(16) Float4
	{
	public:
		Ceng::FLOAT32 x;
		Ceng::FLOAT32 y;
		Ceng::FLOAT32 z;
		Ceng::FLOAT32 w;

	public:

		inline Float4(Ceng::FLOAT32 x, Ceng::FLOAT32 y, Ceng::FLOAT32 z, Ceng::FLOAT32 w)
			: x(x), y(y), z(z),w(w)
		{

		}

		inline Float4(const Float4& source)
			: x(source.x), y(source.y), z(source.z), w(source.w)
		{

		}

		inline Float4(const VectorF4& source)
			: x(source.x), y(source.y), z(source.z), w(source.w)
		{

		}

		inline Float4(const Vshader::InFloat4& source)
		{
			Ceng::VectorF4 temp = source;

			x = temp.x;
			y = temp.y;
			z = temp.z;
			w = temp.w;
		}

		// Operators: self

		inline Float4& operator = (const Float4& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
			w = other.w;

			return *this;
		}

		inline Float4& operator += (const Float4& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;

			return *this;
		}

		inline Float4& operator -= (const Float4& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;

			return *this;
		}

		inline Float4& operator *= (const Float4& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;

			return *this;
		}

		inline Float4& operator /= (const Float4& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;

			return *this;
		}

		inline Ceng::BOOL operator == (const Float4& other) const
		{
			return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
		}

		inline Ceng::BOOL operator != (const Float4& other) const
		{
			return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w);
		}

		// Operators: Ceng::FLOAT32

		inline Float4& operator *= (Ceng::FLOAT32 other)
		{
			x *= other;
			y *= other;
			z *= other;
			w *= other;

			return *this;
		}

		inline Float4& operator /= (Ceng::FLOAT32 other)
		{
			x /= other;
			y /= other;
			z *= other;
			w *= other;

			return *this;
		}

		inline Ceng::BOOL operator == (const Ceng::VectorF4& other) const
		{
			return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
		}

		inline Ceng::BOOL operator != (const Ceng::VectorF4& other) const
		{
			return (x != other.x) || (y != other.y) || (z != other.z) || (w != other.w);
		}

		// Operators: InFloat

		inline Float4& operator *= (const Vshader::InFloat& other)
		{
			x *= (Ceng::FLOAT32)other;
			y *= (Ceng::FLOAT32)other;
			z *= (Ceng::FLOAT32)other;
			w *= (Ceng::FLOAT32)other;

			return *this;
		}

		inline Float4& operator /= (const Vshader::InFloat& other)
		{
			x /= (Ceng::FLOAT32)other;
			y /= (Ceng::FLOAT32)other;
			z /= (Ceng::FLOAT32)other;
			w /= (Ceng::FLOAT32)other;

			return *this;
		}

		inline Ceng::BOOL operator == (const Vshader::InFloat4& other) const
		{
			Ceng::VectorF4 temp = other;

			return (x == temp.x) && (y == temp.y) && (z == temp.z) && (w == temp.w);
		}

		inline Ceng::BOOL operator != (const Vshader::InFloat4& other) const
		{
			Ceng::VectorF4 temp = other;

			return (x != temp.x) || (y != temp.y) || (z != temp.z) || (w != temp.w);
		}
	};

	// Binary operators, Float4-Float4

	inline Float4 operator + (const Float4& a, const Float4& b)
	{
		Float4 temp{ a };
		return temp += b;
	}

	inline Float4 operator - (const Float4& a, const Float4& b)
	{
		Float4 temp{ a };
		return temp -= b;
	}

	inline Float4 operator * (const Float4& a, const Float4& b)
	{
		Float4 temp{ a };
		return temp *= b;
	}

	inline Float4 operator / (const Float4& a, const Float4& b)
	{
		Float4 temp{ a };
		return temp /= b;
	}

	// Binary operators, Float4-Float

	inline Float4 operator * (const Float4& a, const Float& b)
	{
		return a * b;
	}

	inline Float4 operator / (const Float4& a, const Float& b)
	{
		return a / b;
	}

	// Binary operators, InFloat4-FLOAT32

	inline Float4 operator * (const Vshader::InFloat4& a, Ceng::FLOAT32 b)
	{
		return (Ceng::VectorF4)a * b;
	}

	inline Float4 operator / (const Vshader::InFloat4& a, Ceng::FLOAT32 b)
	{
		return (Ceng::VectorF4)a / b;
	}

	// Binary operators, Float4-FLOAT32

	inline Float4 operator * (const Float4& a, Ceng::FLOAT32 b)
	{
		return a * b;
	}

	inline Float4 operator / (const Float4& a, Ceng::FLOAT32 b)
	{
		return a / b;
	}

	// Binary operators InFloat-Float4

	inline Float4 operator * (const Vshader::InFloat& a, const Float4& b)
	{
		return b * (Ceng::FLOAT32)a;
	}

	// Binary operators, Float4-Infloat

	inline Float4 operator * (const Float4& a, const Vshader::InFloat& b)
	{
		Float4 temp{ a };
		return temp *= a;
	}

	inline Float4 operator / (const Float4& a, const Vshader::InFloat& b)
	{
		Float4 temp{ a };
		return temp /= a;
	}

	// Binary operators, FLOAT32-Float2

	inline Float4 operator * (Ceng::FLOAT32 a, const Float4& b)
	{
		Float4 temp{ b };
		return temp *= a;
	}

	// Binary operators, InFloat2-Float2

	inline Float4 operator + (const Vshader::InFloat4& a, const Float4& b)
	{
		return (Ceng::VectorF4)a + b;
	}

	inline Float4 operator - (const Vshader::InFloat4& a, const Float4& b)
	{
		return (Ceng::VectorF4)a - b;
	}

	inline Float4 operator * (const Vshader::InFloat4& a, const Float4& b)
	{
		return (Ceng::VectorF4)a * b;
	}

	inline Float4 operator / (const Vshader::InFloat4& a, const Float4& b)
	{
		return (Ceng::VectorF4)a / b;
	}

	inline Ceng::BOOL operator == (const Vshader::InFloat4& a, const Float4& b)
	{
		return b == a;
	}

	inline Ceng::BOOL operator != (const Vshader::InFloat4& a, const Float4& b)
	{
		return b != a;
	}
}

#endif