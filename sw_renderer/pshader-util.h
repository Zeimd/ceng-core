#pragma once

#ifndef CENG_SWR_PSHADER_UTIL_H
#define CENG_SWR_PSHADER_UTIL_H

#include <math.h>

#include "pshader-types.h"

constexpr double pi = 3.1415926535897932;

constexpr Ceng::FLOAT32 deg2rad = pi / 180.0;

constexpr Ceng::FLOAT32 rad2deg = 180.0 / pi;

namespace Ceng::Pshader
{
	// GLSL spec 3.0, section 8.1 - Angle and trigonometry functions

	//***************************
	// Degrees to radians

	inline SOAVecFloat Radians(const SOAVecFloat& x)
	{
		return x * deg2rad;
	}

	inline Float Radians(const Float& a)
	{
		return Radians(a.x);
	}

	inline Float2 Radians(const Float2& a)
	{
		return { Radians(a._x), Radians(a._y) };
	}

	inline Float3 Radians(const Float3& a)
	{
		return { Radians(a._x), Radians(a._y), Radians(a._z) };
	}

	inline Float4 Radians(const Float4& a)
	{
		return { Radians(a._x), Radians(a._y), Radians(a._z), Radians(a._w) };
	}

	//***************************
	// Radians to degrees

	inline SOAVecFloat Degrees(const SOAVecFloat& x)
	{
		return x * rad2deg;
	}

	inline Float Degrees(const Float& a)
	{
		return Degrees(a.x);
	}

	inline Float2 Degrees(const Float2& a)
	{
		return { Degrees(a._x), Degrees(a._y) };
	}

	inline Float3 Degrees(const Float3& a)
	{
		return { Degrees(a._x), Degrees(a._y), Degrees(a._z) };
	}

	inline Float4 Degrees(const Float4& a)
	{
		return { Degrees(a._x), Degrees(a._y), Degrees(a._z), Degrees(a._w) };
	}

	//****************************
	// Sine

	inline SOAVecFloat Sin(const SOAVecFloat& x)
	{
		return { sinf(x.a), sinf(x.b), sinf(x.c), sinf(x.d) };
	}

	inline Float Sin(const Float& a)
	{
		return Sin(a.x);
	}

	inline Float2 Sin(const Float2& a)
	{
		return { Sin(a._x), Sin(a._y) };
	}

	inline Float3 Sin(const Float3& a)
	{
		return { Sin(a._x), Sin(a._y), Sin(a._z) };
	}

	inline Float4 Sin(const Float4& a)
	{
		return { Sin(a._x), Sin(a._y), Sin(a._z), Sin(a._w) };
	}

	//****************************
	// Cosine

	inline SOAVecFloat Cos(const SOAVecFloat& x)
	{
		return { cosf(x.a), cosf(x.b), cosf(x.c), cosf(x.d) };
	}

	inline Float Cos(const Float& a)
	{
		return Cos(a.x);
	}

	inline Float2 Cos(const Float2& a)
	{
		return { Cos(a._x), Cos(a._y) };
	}

	inline Float3 Cos(const Float3& a)
	{
		return { Cos(a._x), Cos(a._y), Cos(a._z) };
	}

	inline Float4 Cos(const Float4& a)
	{
		return { Cos(a._x), Cos(a._y), Cos(a._z), Cos(a._w) };
	}

	//****************************
	// Tangent

	inline SOAVecFloat Tan(const SOAVecFloat& x)
	{
		return { tanf(x.a), tanf(x.b), tanf(x.c), tanf(x.d) };
	}

	inline Float Tan(const Float& a)
	{
		return Tan(a.x);
	}

	inline Float2 Tan(const Float2& a)
	{
		return { Tan(a._x), Tan(a._y) };
	}

	inline Float3 Tan(const Float3& a)
	{
		return { Tan(a._x), Tan(a._y), Tan(a._z) };
	}

	inline Float4 Tan(const Float4& a)
	{
		return { Tan(a._x), Tan(a._y), Tan(a._z), Tan(a._w) };
	}

	//****************************
	// Arcsin

	inline SOAVecFloat Asin(const SOAVecFloat& x)
	{
		return { asinf(x.a), asinf(x.b), asinf(x.c), asinf(x.d) };
	}

	inline Float Asin(const Float& a)
	{
		return Asin(a.x);
	}

	inline Float2 Asin(const Float2& a)
	{
		return { Asin(a._x), Asin(a._y) };
	}

	inline Float3 Asin(const Float3& a)
	{
		return { Asin(a._x), Asin(a._y), Asin(a._z) };
	}

	inline Float4 Asin(const Float4& a)
	{
		return { Asin(a._x), Asin(a._y), Asin(a._z), Asin(a._w) };
	}

	//****************************
	// Arccos

	inline SOAVecFloat Acos(const SOAVecFloat& x)
	{
		return { acosf(x.a), acosf(x.b), acosf(x.c), acosf(x.d) };
	}

	inline Float Acos(const Float& a)
	{
		return Acos(a.x);
	}

	inline Float2 Acos(const Float2& a)
	{
		return { Acos(a._x), Acos(a._y) };
	}

	inline Float3 Acos(const Float3& a)
	{
		return { Acos(a._x), Acos(a._y), Acos(a._z) };
	}

	inline Float4 Acos(const Float4& a)
	{
		return { Acos(a._x), Acos(a._y), Acos(a._z), Acos(a._w) };
	}

	//****************************
	// Arctan

	inline SOAVecFloat Atan(const SOAVecFloat& x)
	{
		return { atanf(x.a), atanf(x.b), atanf(x.c), atanf(x.d) };
	}

	inline Float Atan(const Float& a)
	{
		return Atan(a.x);
	}

	inline Float2 Atan(const Float2& a)
	{
		return { Atan(a._x), Atan(a._y) };
	}

	inline Float3 Atan(const Float3& a)
	{
		return { Atan(a._x), Atan(a._y), Atan(a._z) };
	}

	inline Float4 Atan(const Float4& a)
	{
		return { Atan(a._x), Atan(a._y), Atan(a._z), Atan(a._w) };
	}

	//****************************
	// Atan2

	inline SOAVecFloat Atan(const SOAVecFloat& y, const SOAVecFloat& x)
	{
		return { atan2f(y.a, x.a), atan2f(y.b, x.b), atan2f(y.c, x.c), atan2f(y.d, x.d) };
	}

	inline Float Atan(const Float& y, const Float& x)
	{
		return Atan(y.x, x.x);
	}

	inline Float2 Atan(const Float2& y, const Float2& x)
	{
		return { Atan(y._x, x._x), Atan(y._y, x._y) };
	}

	inline Float3 Atan(const Float3& y, const Float3& x)
	{
		return { Atan(y._x, x._x), Atan(y._y, x._y), Atan(y._z, x._z) };
	}

	inline Float4 Atan(const Float4& y, const Float4& x)
	{
		return { Atan(y._x, x._x), Atan(y._y, x._y), Atan(y._z, x._z), Atan(y._w, x._w) };
	}

	//***************************
	// Dot product

	inline Float Dot(const Float& a, const Float& b)
	{
		return (a.x * b.x);
	}

	inline Float Dot(const Float2& a, const Float2& b)
	{
		return (a._x * b._x + a._y * b._y);
	}

	inline Float Dot(const Float3& a, const Float3& b)
	{
		return (a._x * b._x + a._y * b._y + a._z * b._z);
	}

	inline Float Dot(const Float4& a, const Float4& b)
	{
		return (a._x * b._x + a._y * b._y + a._z * b._z + a._w * b._w);
	}

	inline SOAVecFloat Sqrt(const SOAVecFloat& x)
	{
		return { sqrtf(x.a), sqrtf(x.b), sqrtf(x.c), sqrtf(x.d) };
	}

	inline Float Sqrt(const Float& a)
	{
		return Sqrt(a.x);
	}

	inline Float2 Sqrt(const Float2& a)
	{
		return { Sqrt(a._x), Sqrt(a._y) };
	}

	inline Float3 Sqrt(const Float3& a)
	{
		return { Sqrt(a._x), Sqrt(a._y), Sqrt(a._z) };
	}

	inline Float4 Sqrt(const Float4& a)
	{
		return { Sqrt(a._x), Sqrt(a._y), Sqrt(a._z), Sqrt(a._w) };
	}

	inline Float Length(const Float& a)
	{
		return Sqrt(Dot(a, a));
	}

	inline Float Length(const Float2& a)
	{
		return Sqrt(Dot(a, a));
	}

	inline Float Length(const Float3& a)
	{
		return Sqrt(Dot(a, a));
	}

	inline Float Length(const Float4& a)
	{
		return Sqrt(Dot(a, a));
	}
}

#endif