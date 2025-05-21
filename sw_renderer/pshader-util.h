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

	//****************************
	// Hyperbolic sine

	inline SOAVecFloat Sinh(const SOAVecFloat& x)
	{
		return { sinhf(x.a), sinhf(x.b), sinhf(x.c), sinhf(x.d) };
	}

	inline Float Sinh(const Float& a)
	{
		return Sinh(a.x);
	}

	inline Float2 Sinh(const Float2& a)
	{
		return { Sinh(a._x), Sinh(a._y) };
	}

	inline Float3 Sinh(const Float3& a)
	{
		return { Sinh(a._x), Sinh(a._y), Sinh(a._z) };
	}

	inline Float4 Sinh(const Float4& a)
	{
		return { Sinh(a._x), Sinh(a._y), Sinh(a._z), Sinh(a._w) };
	}

	//****************************
	// Hyperbolic cosine

	inline SOAVecFloat Cosh(const SOAVecFloat& x)
	{
		return { coshf(x.a), coshf(x.b), coshf(x.c), coshf(x.d) };
	}

	inline Float Cosh(const Float& a)
	{
		return Cosh(a.x);
	}

	inline Float2 Cosh(const Float2& a)
	{
		return { Cosh(a._x), Cosh(a._y) };
	}

	inline Float3 Cosh(const Float3& a)
	{
		return { Cosh(a._x), Cosh(a._y), Cosh(a._z) };
	}

	inline Float4 SCoshinh(const Float4& a)
	{
		return { Cosh(a._x), Cosh(a._y), Cosh(a._z), Cosh(a._w) };
	}

	//****************************
	// Hyperbolic tangent

	inline SOAVecFloat Tanh(const SOAVecFloat& x)
	{
		return { tanhf(x.a), tanhf(x.b), tanhf(x.c), tanhf(x.d) };
	}

	inline Float Tanh(const Float& a)
	{
		return Tanh(a.x);
	}

	inline Float2 Tanh(const Float2& a)
	{
		return { Tanh(a._x), Tanh(a._y) };
	}

	inline Float3 Tanh(const Float3& a)
	{
		return { Tanh(a._x), Tanh(a._y), Tanh(a._z) };
	}

	inline Float4 Tanh(const Float4& a)
	{
		return { Tanh(a._x), Tanh(a._y), Tanh(a._z), Tanh(a._w) };
	}

	//****************************
	// Arcus Hyperbolic sine

	inline SOAVecFloat Asinh(const SOAVecFloat& x)
	{
		return { asinhf(x.a), asinhf(x.b), asinhf(x.c), asinhf(x.d) };
	}

	inline Float Asinh(const Float& a)
	{
		return Asinh(a.x);
	}

	inline Float2 Asinh(const Float2& a)
	{
		return { Asinh(a._x), Asinh(a._y) };
	}

	inline Float3 Asinh(const Float3& a)
	{
		return { Asinh(a._x), Asinh(a._y), Asinh(a._z) };
	}

	inline Float4 Asinh(const Float4& a)
	{
		return { Asinh(a._x), Asinh(a._y), Asinh(a._z), Asinh(a._w) };
	}

	//****************************
	// Arcus Hyperbolic cosine

	inline SOAVecFloat Acosh(const SOAVecFloat& x)
	{
		return { acoshf(x.a), acoshf(x.b), acoshf(x.c), acoshf(x.d) };
	}

	inline Float Acosh(const Float& a)
	{
		return Acosh(a.x);
	}

	inline Float2 Acosh(const Float2& a)
	{
		return { Acosh(a._x), Acosh(a._y) };
	}

	inline Float3 Acosh(const Float3& a)
	{
		return { Acosh(a._x), Acosh(a._y), Acosh(a._z) };
	}

	inline Float4 Acosh(const Float4& a)
	{
		return { Acosh(a._x), Acosh(a._y), Acosh(a._z), Acosh(a._w) };
	}

	//****************************
	// Arcus Hyperbolic tangent

	inline SOAVecFloat Atanh(const SOAVecFloat& x)
	{
		return { atanhf(x.a), atanhf(x.b), atanhf(x.c), atanhf(x.d) };
	}

	inline Float Atanh(const Float& a)
	{
		return Atanh(a.x);
	}

	inline Float2 Atanh(const Float2& a)
	{
		return { Atanh(a._x), Atanh(a._y) };
	}

	inline Float3 Atanh(const Float3& a)
	{
		return { Atanh(a._x), Atanh(a._y), Atanh(a._z) };
	}

	inline Float4 Atanh(const Float4& a)
	{
		return { Atanh(a._x), Atanh(a._y), Atanh(a._z), Atanh(a._w) };
	}

	//***************************
	// Natural exponential function

	inline SOAVecFloat Exp(const SOAVecFloat& x)
	{
		return { expf(x.a), expf(x.b), expf(x.c), expf(x.d) };
	}

	inline Float Exp(const Float& a)
	{
		return Exp(a.x);
	}

	inline Float2 Exp(const Float2& a)
	{
		return { Exp(a._x), Exp(a._y) };
	}

	inline Float3 Exp(const Float3& a)
	{
		return { Exp(a._x), Exp(a._y), Exp(a._z) };
	}

	inline Float4 Exp(const Float4& a)
	{
		return { Exp(a._x), Exp(a._y), Exp(a._z), Exp(a._w) };
	}


	//***************************
	// Generic power function

	inline SOAVecFloat Pow(const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { powf(x.a, y.a), powf(x.b, y.b), powf(x.c, y.c), powf(x.d, y.d) };
	}

	inline Float Pow(const Float& x, const Float& y)
	{
		return Pow(x.x, y.x);
	}

	inline Float2 Pow(const Float2& x, const Float2& y)
	{
		return { Pow(x._x, y._x), Pow(x._y, y._y) };
	}

	inline Float3 Pow(const Float3& x, const Float3& y)
	{
		return { Pow(x._x, y._x), Pow(x._y, y._y), Pow(x._z, y._z) };
	}

	inline Float4 Exp(const Float4& x, const Float4& y)
	{
		return { Pow(x._x, y._x), Pow(x._y, y._y), Pow(x._z, y._z), Pow(x._w, y._w)};
	}

	//***************************
	// Natural logarithm

	inline SOAVecFloat Log(const SOAVecFloat& x)
	{
		return { logf(x.a), logf(x.b), logf(x.c), logf(x.d) };
	}

	inline Float Log(const Float& a)
	{
		return Log(a.x);
	}

	inline Float2 Log(const Float2& a)
	{
		return { Log(a._x), Log(a._y) };
	}

	inline Float3 Log(const Float3& a)
	{
		return { Log(a._x), Log(a._y), Log(a._z) };
	}

	inline Float4 Log(const Float4& a)
	{
		return { Log(a._x), Log(a._y), Log(a._z), Log(a._w) };
	}

	//***************************
	// Base 2 logarithm

	inline SOAVecFloat Log2(const SOAVecFloat& x)
	{
		return { log2f(x.a), log2f(x.b), log2f(x.c), log2f(x.d) };
	}

	inline Float Log2(const Float& a)
	{
		return Log2(a.x);
	}

	inline Float2 Log2(const Float2& a)
	{
		return { Log2(a._x), Log2(a._y) };
	}

	inline Float3 Log2(const Float3& a)
	{
		return { Log2(a._x), Log2(a._y), Log2(a._z) };
	}

	inline Float4 Log2(const Float4& a)
	{
		return { Log2(a._x), Log2(a._y), Log2(a._z), Log2(a._w) };
	}

	//***************************
	// Base 2 exponent

	inline SOAVecFloat Exp2(const SOAVecFloat& x)
	{
		return { exp2f(x.a), exp2f(x.b), exp2f(x.c), exp2f(x.d) };
	}

	inline Float Exp2(const Float& a)
	{
		return Exp2(a.x);
	}

	inline Float2 Exp2(const Float2& a)
	{
		return { Exp2(a._x), Exp2(a._y) };
	}

	inline Float3 Exp2(const Float3& a)
	{
		return { Exp2(a._x), Exp2(a._y), Exp2(a._z) };
	}

	inline Float4 Exp2(const Float4& a)
	{
		return { Exp2(a._x), Exp2(a._y), Exp2(a._z), Exp2(a._w) };
	}

	//***************************
	// Square root

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

	//***************************
	// Inverse Square root

	inline SOAVecFloat InverseSqrt(const SOAVecFloat& x)
	{
		return { 1.0f / sqrtf(x.a), 1.0f / sqrtf(x.b), 1.0f / sqrtf(x.c), 1.0f / sqrtf(x.d) };
	}

	inline Float InverseSqrt(const Float& a)
	{
		return InverseSqrt(a.x);
	}

	inline Float2 InverseSqrt(const Float2& a)
	{
		return { InverseSqrt(a._x), InverseSqrt(a._y) };
	}

	inline Float3 InverseSqrt(const Float3& a)
	{
		return { InverseSqrt(a._x), InverseSqrt(a._y), InverseSqrt(a._z) };
	}

	inline Float4 InverseSqrt(const Float4& a)
	{
		return { InverseSqrt(a._x), InverseSqrt(a._y), InverseSqrt(a._z), InverseSqrt(a._w) };
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

	//****************************
	// Vector length
		
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

	//****************************
	// Distance between two points

	inline Float Distance(const Float& start, const Float& end)
	{
		return Length(end-start);
	}

	inline Float Distance(const Float2& start, const Float2& end)
	{
		return Length(end - start);
	}

	inline Float Distance(const Float3& start, const Float3& end)
	{
		return Length(end - start);
	}

	inline Float Distance(const Float4& start, const Float4& end)
	{
		return Length(end - start);
	}

	//******************************
	// Cross product

	inline Float3 Cross(const Float3& a, const Float3& b)
	{
		return { a._y * b._z - a._z * b._y,
			a._z * b._x - a._x * b._z,
			a._x * b._y - b._x * a._y };
	}

	//******************************
	// Normalize

	inline Float Normalize(const Float& a)
	{
		Float length = Length(a);

		return a / length;
	}

	inline Float2 Normalize(const Float2& a)
	{
		Float length = Length(a);

		return a / length;
	}

	inline Float3 Normalize(const Float3& a)
	{
		Float length = Length(a);

		return a / length;
	}

	inline Float4 Normalize(const Float4& a)
	{
		Float length = Length(a);

		return a / length;
	}

	//*******************************
	// Face forward

	inline Float FaceForward(const Float& n, const Float& i, const Float& nref)
	{
		auto dot = Dot(i, nref);

		SOAVecFloat out = n.x;

		if (dot.x.a >= 0.0f)
		{
			out.a *= -1.0f;
		}

		if (dot.x.b >= 0.0f)
		{
			out.b *= -1.0f;
		}

		if (dot.x.c >= 0.0f)
		{
			out.c *= -1.0f;
		}

		if (dot.x.d >= 0.0f)
		{
			out.d *= -1.0f;
		}

		return out;
	}

	inline Float2 FaceForward(const Float2& n, const Float2& i, const Float2& nref)
	{
		auto dot = Dot(i, nref);

		SOAVecFloat outX = n._x;
		SOAVecFloat outY = n._y;

		if (dot.x.a >= 0.0f)
		{
			outX.a *= -1.0f;
			outY.a *= -1.0f;
		}

		if (dot.x.b >= 0.0f)
		{
			outX.b *= -1.0f;
			outY.b *= -1.0f;
		}

		if (dot.x.c >= 0.0f)
		{
			outX.c *= -1.0f;
			outY.c *= -1.0f;
		}

		if (dot.x.d >= 0.0f)
		{
			outX.d *= -1.0f;
			outY.d *= -1.0f;
		}

		return { outX,outY };
	}

	inline Float3 FaceForward(const Float3& n, const Float3& i, const Float3& nref)
	{
		auto dot = Dot(i, nref);

		SOAVecFloat outX = n._x;
		SOAVecFloat outY = n._y;
		SOAVecFloat outZ = n._z;

		if (dot.x.a >= 0.0f)
		{
			outX.a *= -1.0f;
			outY.a *= -1.0f;
			outZ.a *= -1.0f;
		}

		if (dot.x.b >= 0.0f)
		{
			outX.b *= -1.0f;
			outY.b *= -1.0f;
			outZ.b *= -1.0f;
		}

		if (dot.x.c >= 0.0f)
		{
			outX.c *= -1.0f;
			outY.c *= -1.0f;
			outZ.c *= -1.0f;
		}

		if (dot.x.d >= 0.0f)
		{
			outX.d *= -1.0f;
			outY.d *= -1.0f;
			outZ.d *= -1.0f;
		}

		return { outX,outY, outZ };
	}

	inline Float4 FaceForward(const Float4& n, const Float4& i, const Float4& nref)
	{
		auto dot = Dot(i, nref);

		SOAVecFloat outX = n._x;
		SOAVecFloat outY = n._y;
		SOAVecFloat outZ = n._z;
		SOAVecFloat outW = n._w;

		if (dot.x.a >= 0.0f)
		{
			outX.a *= -1.0f;
			outY.a *= -1.0f;
			outZ.a *= -1.0f;
			outW.a *= -1.0f;
		}

		if (dot.x.b >= 0.0f)
		{
			outX.b *= -1.0f;
			outY.b *= -1.0f;
			outZ.b *= -1.0f;
			outW.b *= -1.0f;
		}

		if (dot.x.c >= 0.0f)
		{
			outX.c *= -1.0f;
			outY.c *= -1.0f;
			outZ.c *= -1.0f;
			outW.c *= -1.0f;
		}

		if (dot.x.d >= 0.0f)
		{
			outX.d *= -1.0f;
			outY.d *= -1.0f;
			outZ.d *= -1.0f;
			outW.d *= -1.0f;
		}

		return { outX,outY, outZ, outW };
	}

	//*******************************
	// Reflect

	inline Float Reflect(const Float& i, const Float& n)
	{
		return i - 2.0f * Dot(i, n) * n;
	}

	inline Float2 Reflect(const Float2& i, const Float2& n)
	{
		return i - n * 2.0f * Dot(i, n);
	}

	inline Float3 Reflect(const Float3& i, const Float3& n)
	{
		return i - n * 2.0f * Dot(i, n);
	}

	inline Float4 Reflect(const Float4& i, const Float4& n)
	{
		return i - n * 2.0f * Dot(i, n);
	}

	//*******************************
	// Refract

	inline Float Refract(const Float& i, const Float& n, const Float& eta)
	{
		Float k = 1.0f - eta * eta * (1.0f - Dot(n, i) * Dot(n, i));

		Float temp = eta * i - (eta * Dot(n, i) * Sqrt(k)) * n;

		if (k.x.a < 0.0f)
		{
			temp.x.a = 0.0f;
		}

		if (k.x.b < 0.0f)
		{
			temp.x.b = 0.0f;
		}

		if (k.x.c < 0.0f)
		{
			temp.x.c = 0.0f;
		}

		if (k.x.d < 0.0f)
		{
			temp.x.d = 0.0f;
		}

		return temp;
	}

	inline Float2 Refract(const Float2& i, const Float2& n, const Float& eta)
	{
		Float k = 1.0f - eta * eta * (1.0f - Dot(n, i) * Dot(n, i));

		Float2 temp = i * eta - n * (eta * Dot(n, i) * Sqrt(k));

		if (k.x.a < 0.0f)
		{
			temp._x.a = 0.0f;
			temp._y.a = 0.0f;
		}

		if (k.x.b < 0.0f)
		{
			temp._x.b = 0.0f;
			temp._y.b = 0.0f;
		}

		if (k.x.c < 0.0f)
		{
			temp._x.c = 0.0f;
			temp._y.c = 0.0f;
		}

		if (k.x.d < 0.0f)
		{
			temp._x.d = 0.0f;
			temp._y.d = 0.0f;
		}

		return temp;
	}

	inline Float3 Refract(const Float3& i, const Float3& n, const Float& eta)
	{
		Float k = 1.0f - eta * eta * (1.0f - Dot(n, i) * Dot(n, i));

		Float3 temp = i * eta - n * (eta * Dot(n, i) * Sqrt(k));

		if (k.x.a < 0.0f)
		{
			temp._x.a = 0.0f;
			temp._y.a = 0.0f;
			temp._z.a = 0.0f;
		}

		if (k.x.b < 0.0f)
		{
			temp._x.b = 0.0f;
			temp._y.b = 0.0f;
			temp._z.b = 0.0f;
		}

		if (k.x.c < 0.0f)
		{
			temp._x.c = 0.0f;
			temp._y.c = 0.0f;
			temp._z.c = 0.0f;
		}

		if (k.x.d < 0.0f)
		{
			temp._x.d = 0.0f;
			temp._y.d = 0.0f;
			temp._z.d = 0.0f;
		}

		return temp;
	}

	inline Float4 Refract(const Float4& i, const Float4& n, const Float& eta)
	{
		Float k = 1.0f - eta * eta * (1.0f - Dot(n, i) * Dot(n, i));

		Float4 temp = i * eta - n * (eta * Dot(n, i) * Sqrt(k));

		if (k.x.a < 0.0f)
		{
			temp._x.a = 0.0f;
			temp._y.a = 0.0f;
			temp._z.a = 0.0f;
			temp._w.a = 0.0f;
		}

		if (k.x.b < 0.0f)
		{
			temp._x.b = 0.0f;
			temp._y.b = 0.0f;
			temp._z.b = 0.0f;
			temp._w.b = 0.0f;
		}

		if (k.x.c < 0.0f)
		{
			temp._x.c = 0.0f;
			temp._y.c = 0.0f;
			temp._z.c = 0.0f;
			temp._w.c = 0.0f;
		}

		if (k.x.d < 0.0f)
		{
			temp._x.d = 0.0f;
			temp._y.d = 0.0f;
			temp._z.d = 0.0f;
			temp._w.d = 0.0f;
		}

		return temp;
	}	
	
}

#endif