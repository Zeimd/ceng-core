#pragma once

#ifndef CENG_SWRENDER_VSHADER_UTIL_H
#define CENG_SWRENDER_VSHADER_UTIL_H

#include <math.h>

#include <ceng/datatypes/basic-types.h>

#include "vshader-types.h"

constexpr double pi = 3.1415926535897932;

constexpr Ceng::FLOAT32 deg2rad = pi / 180.0;

constexpr Ceng::FLOAT32 rad2deg = 180.0 / pi;

namespace Ceng::Vshader
{
	//***************************
	// Degrees to radians

	inline Float Radians(const Float& a)
	{
		return a.x * deg2rad;
	}

	inline Float2 Radians(const Float2& a)
	{
		return { a.x * deg2rad, a.y * deg2rad };
	}

	inline Float3 Radians(const Float3& a)
	{
		return { a.x * deg2rad, a.y * deg2rad, a.z * deg2rad };
	}

	inline Float4 Radians(const Float4& a)
	{
		return { a.x * deg2rad, a.y * deg2rad, a.z * deg2rad, a.w * deg2rad };
	}

	//***************************
	// Radians to degrees

	inline Float Degrees(const Float& a)
	{
		return a * rad2deg;
	}

	inline Float2 Degrees(const Float2& a)
	{
		return { a.x * rad2deg, a.y * rad2deg };
	}

	inline Float3 Degrees(const Float3& a)
	{
		return { a.x * rad2deg, a.y * rad2deg, a.z * rad2deg };
	}

	inline Float4 Degrees(const Float4& a)
	{
		return { a.x * rad2deg, a.y * rad2deg, a.z * rad2deg, a.w * rad2deg };
	}

	//****************************
	// Sine

	inline Float Sin(const Float& a)
	{
		return sinf(a.x);
	}

	inline Float2 Sin(const Float2& a)
	{
		return { sinf(a.x), sinf(a.y) };
	}

	inline Float3 Sin(const Float3& a)
	{
		return { sinf(a.x), sinf(a.y), sinf(a.z) };
	}

	inline Float4 Sin(const Float4& a)
	{
		return { sinf(a.x), sinf(a.y), sinf(a.z), sinf(a.w) };
	}

	//****************************
	// Cosine

	inline Float Cos(const Float& a)
	{
		return cosf(a.x);
	}

	inline Float2 Cos(const Float2& a)
	{
		return { cosf(a.x), cosf(a.y) };
	}

	inline Float3 Cos(const Float3& a)
	{
		return { cosf(a.x), cosf(a.y), cosf(a.z) };
	}

	inline Float4 Cos(const Float4& a)
	{
		return { cosf(a.x), cosf(a.y), cosf(a.z), cosf(a.w) };
	}

	//****************************
	// Tangent

	inline Float Tan(const Float& a)
	{
		return tanf(a.x);
	}

	inline Float2 Tan(const Float2& a)
	{
		return { tanf(a.x), tanf(a.y) };
	}

	inline Float3 Tan(const Float3& a)
	{
		return { tanf(a.x), tanf(a.y), tanf(a.z) };
	}

	inline Float4 Tan(const Float4& a)
	{
		return { tanf(a.x), tanf(a.y), tanf(a.z), tanf(a.w) };
	}

	//****************************
	// Arcsin

	inline Float Asin(const Float& a)
	{
		return asinf(a.x);
	}

	inline Float2 Asin(const Float2& a)
	{
		return { asinf(a.x), asinf(a.y) };
	}

	inline Float3 Asin(const Float3& a)
	{
		return { asinf(a.x), asinf(a.y), asinf(a.z) };
	}

	inline Float4 Asin(const Float4& a)
	{
		return { asinf(a.x), asinf(a.y), asinf(a.z), asinf(a.w) };
	}

	//****************************
	// Arccos

	inline Float Acos(const Float& a)
	{
		return acosf(a.x);
	}

	inline Float2 Acos(const Float2& a)
	{
		return { acosf(a.x), acosf(a.y) };
	}

	inline Float3 Acos(const Float3& a)
	{
		return { acosf(a.x), acosf(a.y), acosf(a.z) };
	}

	inline Float4 Acos(const Float4& a)
	{
		return { acosf(a.x), acosf(a.y), acosf(a.z), acosf(a.w) };
	}

	//****************************
	// Arctan

	inline Float Atan(const Float& a)
	{
		return atanf(a.x);
	}

	inline Float2 Atan(const Float2& a)
	{
		return { atanf(a.x), atanf(a.y) };
	}

	inline Float3 Atan(const Float3& a)
	{
		return { atanf(a.x), atanf(a.y), atanf(a.z) };
	}

	inline Float4 Atan(const Float4& a)
	{
		return { atanf(a.x), atanf(a.y), atanf(a.z), atanf(a.w) };
	}

	//****************************
	// Atan2

	inline Float Atan2(const Float& y, const Float& x)
	{
		return  atan2f(y.x, x.x);
	}

	inline Float2 Atan2(const Float2& y, const Float2& x)
	{
		return { atan2f(y.x, x.x), atan2f(y.y, x.y) };
	}

	inline Float3 Atan2(const Float3& y, const Float3& x)
	{
		return { atan2f(y.x, x.x), atan2f(y.y, x.y), atan2f(y.z, x.z) };
	}

	inline Float4 Atan2(const Float4& y, const Float4& x)
	{
		return { atan2f(y.x, x.x), atan2f(y.y, x.y), atan2f(y.z, x.z), atan2f(y.w, x.w) };
	}

	//****************************
	// Hyperbolic sine

	inline Float Sinh(const Float& a)
	{
		return sinhf(a.x);
	}

	inline Float2 Sinh(const Float2& a)
	{
		return { sinhf(a.x), sinhf(a.y) };
	}

	inline Float3 Sinh(const Float3& a)
	{
		return { sinhf(a.x), sinhf(a.y), sinhf(a.z) };
	}

	inline Float4 Sinh(const Float4& a)
	{
		return { sinhf(a.x), sinhf(a.y), sinhf(a.z), sinhf(a.w) };
	}

	//****************************
	// Hyperbolic cosine

	inline Float Cosh(const Float& a)
	{
		return coshf(a.x);
	}

	inline Float2 Cosh(const Float2& a)
	{
		return { coshf(a.x), coshf(a.y) };
	}

	inline Float3 Cosh(const Float3& a)
	{
		return { coshf(a.x), coshf(a.y), coshf(a.z) };
	}

	inline Float4 Cosh(const Float4& a)
	{
		return { coshf(a.x), coshf(a.y), coshf(a.z), coshf(a.w) };
	}

	//****************************
	// Hyperbolic tangent

	inline Float Tanh(const Float& a)
	{
		return tanhf(a.x);
	}

	inline Float2 Tanh(const Float2& a)
	{
		return { tanhf(a.x), tanhf(a.y) };
	}

	inline Float3 Tanh(const Float3& a)
	{
		return { tanhf(a.x), tanhf(a.y), tanhf(a.z) };
	}

	inline Float4 Tanh(const Float4& a)
	{
		return { tanhf(a.x), tanhf(a.y), tanhf(a.z), tanhf(a.w) };
	}

	//****************************
	// Arcus Hyperbolic sine

	inline Float Asinh(const Float& a)
	{
		return asinhf(a.x);
	}

	inline Float2 Asinh(const Float2& a)
	{
		return { asinhf(a.x), asinhf(a.y) };
	}

	inline Float3 Asinh(const Float3& a)
	{
		return { asinhf(a.x), asinhf(a.y), asinhf(a.z) };
	}

	inline Float4 Asinh(const Float4& a)
	{
		return { asinhf(a.x), asinhf(a.y), asinhf(a.z), asinhf(a.w) };
	}

	//****************************
	// Arcus Hyperbolic cosine


	inline Float Acosh(const Float& a)
	{
		return acoshf(a.x);
	}

	inline Float2 Acosh(const Float2& a)
	{
		return { acoshf(a.x), acoshf(a.y) };
	}

	inline Float3 Acosh(const Float3& a)
	{
		return { acoshf(a.x), acoshf(a.y), acoshf(a.z) };
	}

	inline Float4 Acosh(const Float4& a)
	{
		return { acoshf(a.x), acoshf(a.y), acoshf(a.z), acoshf(a.w) };
	}


	//****************************
	// Arcus Hyperbolic tangent

	inline Float Atanh(const Float& a)
	{
		return atanhf(a.x);
	}

	inline Float2 Atanh(const Float2& a)
	{
		return { atanhf(a.x), atanhf(a.y) };
	}

	inline Float3 Atanh(const Float3& a)
	{
		return { atanhf(a.x), atanhf(a.y), atanhf(a.z) };
	}

	inline Float4 Atanh(const Float4& a)
	{
		return { atanhf(a.x), atanhf(a.y), atanhf(a.z), atanhf(a.w) };
	}

	//***************************
	// Natural exponential function

	inline Float Exp(const Float& a)
	{
		return expf(a.x);
	}

	inline Float2 Exp(const Float2& a)
	{
		return { expf(a.x), expf(a.y) };
	}

	inline Float3 Exp(const Float3& a)
	{
		return { expf(a.x), expf(a.y), expf(a.z) };
	}

	inline Float4 Exp(const Float4& a)
	{
		return { expf(a.x), expf(a.y), expf(a.z), expf(a.w) };
	}

	//***************************
	// Generic power function

	inline Float Pow(const Float& x, const Float& y)
	{
		return  powf(x.x, y.x);
	}

	inline Float2 Pow(const Float2& y, const Float2& x)
	{
		return { powf(x.x, y.x), powf(x.y, y.y) };
	}

	inline Float3 Pow(const Float3& y, const Float3& x)
	{
		return { powf(x.x, y.x), powf(x.y, y.y), powf(x.z, y.z) };
	}

	inline Float4 Pow(const Float4& y, const Float4& x)
	{
		return { powf(x.x, y.x), powf(x.y, y.y), powf(x.z, y.z), powf(x.w, y.w) };
	}

	//***************************
	// Natural logarithm

	inline Float Log(const Float& a)
	{
		return logf(a.x);
	}

	inline Float2 Log(const Float2& a)
	{
		return { logf(a.x), logf(a.y) };
	}

	inline Float3 Log(const Float3& a)
	{
		return { logf(a.x), logf(a.y), logf(a.z) };
	}

	inline Float4 Log(const Float4& a)
	{
		return { logf(a.x), logf(a.y), logf(a.z), logf(a.w) };
	}


	//***************************
	// Base 2 logarithm

	inline Float Log2(const Float& a)
	{
		return log2f(a.x);
	}

	inline Float2 Log2(const Float2& a)
	{
		return { log2f(a.x), log2f(a.y) };
	}

	inline Float3 Log2(const Float3& a)
	{
		return { log2f(a.x), log2f(a.y), log2f(a.z) };
	}

	inline Float4 Log2(const Float4& a)
	{
		return { log2f(a.x), log2f(a.y), log2f(a.z), log2f(a.w) };
	}

	//***************************
	// Base 2 exponent

	inline Float Exp2(const Float& a)
	{
		return exp2f(a.x);
	}

	inline Float2 Exp2(const Float2& a)
	{
		return { exp2f(a.x), exp2f(a.y) };
	}

	inline Float3 Exp2(const Float3& a)
	{
		return { exp2f(a.x), exp2f(a.y), exp2f(a.z) };
	}

	inline Float4 Exp2(const Float4& a)
	{
		return { exp2f(a.x), exp2f(a.y), exp2f(a.z), exp2f(a.w) };
	}

	//***************************
	// Square root

	inline Float Sqrt(const Float& a)
	{
		return sqrtf(a.x);
	}

	inline Float2 Sqrt(const Float2& a)
	{
		return { sqrtf(a.x), sqrtf(a.y) };
	}

	inline Float3 Sqrt(const Float3& a)
	{
		return { sqrtf(a.x), sqrtf(a.y), sqrtf(a.z) };
	}

	inline Float4 Sqrt(const Float4& a)
	{
		return { sqrtf(a.x), sqrtf(a.y), sqrtf(a.z), sqrtf(a.w) };
	}

	//***************************
	// Inverse Square root

	inline Float InverseSqrt(const Float& a)
	{
		return { 1.0f / sqrtf(a.x) };
	}

	inline Float2 InverseSqrt(const Float2& a)
	{
		return { 1.0f / sqrtf(a.x), 1.0f / sqrtf(a.y) };
	}

	inline Float3 InverseSqrt(const Float3& a)
	{
		return { 1.0f / sqrtf(a.x), 1.0f / sqrtf(a.y), 1.0f / sqrtf(a.z) };
	}

	inline Float4 InverseSqrt(const Float4& a)
	{
		return { 1.0f / sqrtf(a.x), 1.0f / sqrtf(a.y), 1.0f / sqrtf(a.z), 1.0f / sqrtf(a.w) };
	}


	//***************************
	// Dot product

	inline Float Dot(const Float& a, const Float& b)
	{
		return (a.x * b.x);
	}

	inline Float Dot(const Float2& a, const Float2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	inline Float Dot(const Float3& a, const Float3& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}

	inline Float Dot(const Float4& a, const Float4& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
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
		return Length(end - start);
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
		return { a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - b.x * a.y };
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

		Float out = n.x;

		if (dot.x >= 0.0f)
		{
			out.x *= -1.0f;
		}

		return out;
	}

	inline Float2 FaceForward(const Float2& n, const Float2& i, const Float2& nref)
	{
		auto dot = Dot(i, nref);

		Ceng::FLOAT32 outX = n.x;
		Ceng::FLOAT32 outY = n.y;

		if (dot.x >= 0.0f)
		{
			outX *= -1.0f;
			outY *= -1.0f;
		}

		return { outX,outY };
	}

	inline Float3 FaceForward(const Float3& n, const Float3& i, const Float3& nref)
	{
		auto dot = Dot(i, nref);

		Ceng::FLOAT32 outX = n.x;
		Ceng::FLOAT32 outY = n.y;
		Ceng::FLOAT32 outZ = n.z;

		if (dot.x >= 0.0f)
		{
			outX *= -1.0f;
			outY *= -1.0f;
			outZ *= -1.0f;
		}

		return { outX,outY, outZ };
	}

	inline Float4 FaceForward(const Float4& n, const Float4& i, const Float4& nref)
	{
		auto dot = Dot(i, nref);

		Ceng::FLOAT32 outX = n.x;
		Ceng::FLOAT32 outY = n.y;
		Ceng::FLOAT32 outZ = n.z;
		Ceng::FLOAT32 outW = n.w;

		if (dot.x >= 0.0f)
		{
			outX *= -1.0f;
			outY *= -1.0f;
			outZ *= -1.0f;
			outW *= -1.0f;
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

		if (k.x < 0.0f)
		{
			temp.x = 0.0f;
		}

		return temp;
	}

	inline Float2 Refract(const Float2& i, const Float2& n, const Float& eta)
	{
		Float k = 1.0f - eta * eta * (1.0f - Dot(n, i) * Dot(n, i));

		Float2 temp = i * eta - n * (eta * Dot(n, i) * Sqrt(k));

		if (k.x < 0.0f)
		{
			temp.x = 0.0f;
			temp.y = 0.0f;
		}

		return temp;
	}

	inline Float3 Refract(const Float3& i, const Float3& n, const Float& eta)
	{
		Float k = 1.0f - eta * eta * (1.0f - Dot(n, i) * Dot(n, i));

		Float3 temp = i * eta - n * (eta * Dot(n, i) * Sqrt(k));

		if (k.x < 0.0f)
		{
			temp.x = 0.0f;
			temp.y = 0.0f;
			temp.z = 0.0f;
		}

		return temp;
	}

	inline Float4 Refract(const Float4& i, const Float4& n, const Float& eta)
	{
		Float k = 1.0f - eta * eta * (1.0f - Dot(n, i) * Dot(n, i));

		Float4 temp = i * eta - n * (eta * Dot(n, i) * Sqrt(k));

		if (k.x < 0.0f)
		{
			temp.x = 0.0f;
			temp.y = 0.0f;
			temp.z = 0.0f;
			temp.w = 0.0f;
		}

		return temp;
	}

	//**********************************
	// Vector form for < operator

	inline Bool2 LessThan(const Float2& a, const Float2& b)
	{
		return  { a.x < b.x, a.y < b.y };
	}

	inline Bool3 LessThan(const Float3& a, const Float3& b)
	{
		return  { a.x < b.x, a.y < b.y, a.z < b.z };
	}

	inline Bool4 LessThan(const Float4& a, const Float4& b)
	{
		return  { a.x < b.x, a.y < b.y, a.z < b.z, a.w < b.w };
	}

	//**********************************
	// Vector form for <= operator

	inline Bool2 LessThanEqual(const Float2& a, const Float2& b)
	{
		return  { a.x <= b.x, a.y <= b.y };
	}

	inline Bool3 LessThanEqual(const Float3& a, const Float3& b)
	{
		return  { a.x <= b.x, a.y <= b.y, a.z <= b.z };
	}

	inline Bool4 LessThanEqual(const Float4& a, const Float4& b)
	{
		return  { a.x <= b.x, a.y <= b.y, a.z <= b.z, a.w <= b.w };
	}

	//**********************************
	// Vector form for > operator

	inline Bool2 GreaterThan(const Float2& a, const Float2& b)
	{
		return  { a.x > b.x, a.y > b.y };
	}

	inline Bool3 GreaterThan(const Float3& a, const Float3& b)
	{
		return  { a.x > b.x, a.y > b.y, a.z > b.z };
	}

	inline Bool4 GreaterThan(const Float4& a, const Float4& b)
	{
		return  { a.x > b.x, a.y > b.y, a.z > b.z, a.w > b.w };
	}

	//**********************************
	// Vector form for <= operator

	inline Bool2 GreaterThanEqual(const Float2& a, const Float2& b)
	{
		return  { a.x >= b.x, a.y >= b.y };
	}

	inline Bool3 GreaterThanEqual(const Float3& a, const Float3& b)
	{
		return  { a.x >= b.x, a.y >= b.y, a.z >= b.z };
	}

	inline Bool4 GreaterThanEqual(const Float4& a, const Float4& b)
	{
		return  { a.x >= b.x, a.y >= b.y, a.z >= b.z, a.w >= b.w };
	}

	//**********************************
	// Vector form for == operator

	inline Bool2 Equal(const Float2& a, const Float2& b)
	{
		return  { a.x == b.x, a.y == b.y };
	}

	inline Bool3 Equal(const Float3& a, const Float3& b)
	{
		return  { a.x == b.x, a.y == b.y, a.z == b.z };
	}

	inline Bool4 Equal(const Float4& a, const Float4& b)
	{
		return  { a.x == b.x, a.y == b.y, a.z == b.z, a.w == b.w };
	}

	//**********************************
	// Vector form for != operator

	inline Bool2 NotEqual(const Float2& a, const Float2& b)
	{
		return  { a.x != b.x, a.y != b.y };
	}

	inline Bool3 NotEqual(const Float3& a, const Float3& b)
	{
		return  { a.x != b.x, a.y != b.y, a.z != b.z };
	}

	inline Bool4 NotEqual(const Float4& a, const Float4& b)
	{
		return  { a.x != b.x, a.y != b.y, a.z != b.z, a.w != b.w };
	}

	//**********************************
	// Any bool check

	inline Bool Any(const Bool2& a)
	{
		return a.x || a.y;
	}

	inline Bool Any(const Bool3& a)
	{
		return a.x || a.y || a.z;
	}

	inline Bool Any(const Bool4& a)
	{
		return a.x || a.y || a.z || a.w;
	}

	//**********************************
	// All bool check

	inline Bool All(const Bool2& a)
	{
		return a.x && a.y;
	}

	inline Bool All(const Bool3& a)
	{
		return a.x && a.y && a.z;
	}

	inline Bool All(const Bool4& a)
	{
		return a.x && a.y && a.z && a.w;
	}

	//**********************************
	// Boolean vector negation

	inline Bool2 Not(const Bool2& a)
	{
		return { !a.x, !a.y };
	}

	inline Bool3 Not(const Bool3& a)
	{
		return { !a.x, !a.y, !a.z };
	}

	inline Bool4 Not(const Bool4& a)
	{
		return { !a.x, !a.y, !a.z, !a.w };
	}

	//*************************************
	// Absolute value

	inline Float Abs(const Float& a)
	{
		return fabsf(a.x);
	}

	inline Float2 Abs(const Float2& a)
	{
		return { fabsf(a.x), fabsf(a.y) };
	}

	inline Float3 Abs(const Float3& a)
	{
		return { fabsf(a.x), fabsf(a.y), fabsf(a.z) };
	}

	inline Float4 Abs(const Float4& a)
	{
		return { fabsf(a.x), fabsf(a.y), fabsf(a.z), fabsf(a.w) };
	}


	//*************************************
	// Sign function


	inline Float Sign(const Float& a)
	{
		return (Ceng::FLOAT32)copysign(1.0f, a.x);
	}

	inline Float2 Sign(const Float2& a)
	{
		return { (Ceng::FLOAT32)copysign(1.0f, a.x), (Ceng::FLOAT32)copysign(1.0f, a.y) };
	}

	inline Float3 Sign(const Float3& a)
	{
		return { (Ceng::FLOAT32)copysign(1.0f, a.x), (Ceng::FLOAT32)copysign(1.0f, a.y)
		, (Ceng::FLOAT32)copysign(1.0f, a.z) };
	}

	inline Float4 Sign(const Float4& a)
	{
		return { (Ceng::FLOAT32)copysign(1.0f, a.x), (Ceng::FLOAT32)copysign(1.0f, a.y),
		(Ceng::FLOAT32)copysign(1.0f, a.z), (Ceng::FLOAT32)copysign(1.0f, a.w) };
	}


	//*************************************
	// Floor

	inline Float Floor(const Float& a)
	{
		return floorf(a.x);
	}

	inline Float2 Floor(const Float2& a)
	{
		return { floorf(a.x), floorf(a.y) };
	}

	inline Float3 Floor(const Float3& a)
	{
		return { floorf(a.x), floorf(a.y), floorf(a.z) };
	}

	inline Float4 Floor(const Float4& a)
	{
		return { floorf(a.x), floorf(a.y), floorf(a.z), floorf(a.w) };
	}


	//*************************************
	// Ceil


	inline Float Ceil(const Float& a)
	{
		return ceilf(a.x);
	}

	inline Float2 Ceil(const Float2& a)
	{
		return { ceilf(a.x), ceilf(a.y) };
	}

	inline Float3 Ceil(const Float3& a)
	{
		return { ceilf(a.x), ceilf(a.y), ceilf(a.z) };
	}

	inline Float4 Ceil(const Float4& a)
	{
		return { ceilf(a.x), ceilf(a.y), ceilf(a.z), ceilf(a.w) };
	}


	//*************************************
	// Truncate


	inline Float Trunc(const Float& a)
	{
		return truncf(a.x);
	}

	inline Float2 Trunc(const Float2& a)
	{
		return { truncf(a.x), truncf(a.y) };
	}

	inline Float3 Trunc(const Float3& a)
	{
		return { truncf(a.x), truncf(a.y), truncf(a.z) };
	}

	inline Float4 Trunc(const Float4& a)
	{
		return { truncf(a.x), truncf(a.y), truncf(a.z), truncf(a.w) };
	}


	//*************************************
	// Round

	inline Float Round(const Float& a)
	{
		return roundf(a.x);
	}

	inline Float2 Round(const Float2& a)
	{
		return { roundf(a.x), roundf(a.y) };
	}

	inline Float3 Round(const Float3& a)
	{
		return { roundf(a.x), roundf(a.y), roundf(a.z) };
	}

	inline Float4 Round(const Float4& a)
	{
		return { roundf(a.x), roundf(a.y), roundf(a.z), roundf(a.w) };
	}

	//*************************************
	// Round half to even

	inline Ceng::FLOAT32 RoundEven(Ceng::FLOAT32 x)
	{
		return roundf(x * 0.5f) * 2.0f;
	}

	inline Float RoundEven(const Float& a)
	{
		return RoundEven(a.x);
	}

	inline Float2 RoundEven(const Float2& a)
	{
		return { RoundEven(a.x), RoundEven(a.y) };
	}

	inline Float3 RoundEven(const Float3& a)
	{
		return { RoundEven(a.x), RoundEven(a.y), RoundEven(a.z) };
	}

	inline Float4 RoundEven(const Float4& a)
	{
		return { RoundEven(a.x), RoundEven(a.y), RoundEven(a.z), RoundEven(a.w) };
	}


	//*************************************
	// Fractional part


	inline Ceng::FLOAT32 Fract(Ceng::FLOAT32 x)
	{
		return x - floorf(x);
	}

	inline Float Fract(const Float& a)
	{
		return Fract(a.x);
	}

	inline Float2 Fract(const Float2& a)
	{
		return { Fract(a.x), Fract(a.y) };
	}

	inline Float3 Fract(const Float3& a)
	{
		return { Fract(a.x), Fract(a.y), Fract(a.z) };
	}

	inline Float4 Fract(const Float4& a)
	{
		return { Fract(a.x), Fract(a.y), Fract(a.z), Fract(a.w) };
	}


	//*************************************
	// Modulus


	inline Ceng::FLOAT32 Mod(Ceng::FLOAT32 a, Ceng::FLOAT32 b)
	{
		return a - b * floorf(a / b);
	}

	inline Float Fract(const Float& a, const Float& b)
	{
		return Mod(a.x, b.x);
	}

	inline Float2 Fract(const Float2& a, const Float& b)
	{
		return { Mod(a.x, b.x), Mod(a.y, b.x) };
	}

	inline Float3 Fract(const Float3& a, const Float& b)
	{
		return { Mod(a.x, b.x), Mod(a.y, b.x), Mod(a.z, b.x) };
	}

	inline Float4 Fract(const Float4& a, const Float& b)
	{
		return { Mod(a.x, b.x), Mod(a.y, b.x), Mod(a.z, b.x), Mod(a.w, b.x) };
	}

	inline Float2 Fract(const Float2& a, const Float2& b)
	{
		return { Mod(a.x, b.x), Mod(a.y, b.y) };
	}

	inline Float3 Fract(const Float3& a, const Float3& b)
	{
		return { Mod(a.x, b.x), Mod(a.y, b.y), Mod(a.z, b.z) };
	}

	inline Float4 Fract(const Float4& a, const Float4& b)
	{
		return { Mod(a.x, b.x), Mod(a.y, b.y), Mod(a.z, b.z), Mod(a.w, b.w) };
	}


	//*************************************
	// modf

	//*************************************
	// min

	inline Float Min(const Float& a, const Float& b)
	{
		return std::min(a.x, b.x);
	}

	inline Float2 Min(const Float2& a, const Float2& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.y) };
	}

	inline Float3 Min(const Float3& a, const Float3& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) };
	}

	inline Float4 Min(const Float4& a, const Float4& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w) };
	}

	inline Float2 Min(const Float2& a, const Float& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.x) };
	}

	inline Float3 Min(const Float3& a, const Float& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.x), std::min(a.z, b.x) };
	}

	inline Float4 Min(const Float4& a, const Float& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.x), std::min(a.z, b.x), std::min(a.w, b.x) };
	}

	//*************************************
	// max


	inline Float Max(const Float& a, const Float& b)
	{
		return std::max(a.x, b.x);
	}

	inline Float2 Max(const Float2& a, const Float2& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.y) };
	}

	inline Float3 Max(const Float3& a, const Float3& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) };
	}

	inline Float4 Max(const Float4& a, const Float4& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w) };
	}

	inline Float2 Max(const Float2& a, const Float& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.x) };
	}

	inline Float3 Max(const Float3& a, const Float& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.x), std::max(a.z, b.x) };
	}

	inline Float4 Max(const Float4& a, const Float& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.x), std::max(a.z, b.x), std::max(a.w, b.x) };
	}

	//*************************************
	// Clamp

	inline Ceng::FLOAT32 Clamp(Ceng::FLOAT32 x, Ceng::FLOAT32 minVal, Ceng::FLOAT32 maxVal)
	{
		return std::min(std::max(x, minVal), maxVal);
	}

	inline Float Clamp(const Float& a, const Float& minVal, const Float& maxVal)
	{
		return Clamp(a.x, minVal.x, maxVal.x);
	}

	inline Float2 Clamp(const Float2& a, const Float2& minVal, const Float2& maxVal)
	{
		return { Clamp(a.x, minVal.x, maxVal.x), Clamp(a.y, minVal.y, maxVal.y) };
	}

	inline Float3 Clamp(const Float3& a, const Float3& minVal, const Float3& maxVal)
	{
		return { Clamp(a.x, minVal.x, maxVal.x), Clamp(a.y, minVal.y, maxVal.y), Clamp(a.z, minVal.z, maxVal.z) };
	}

	inline Float4 Clamp(const Float4& a, const Float4& minVal, const Float4& maxVal)
	{
		return { Clamp(a.x, minVal.x, maxVal.x),
				Clamp(a.y, minVal.y, maxVal.y),
				Clamp(a.z, minVal.z, maxVal.z),
				Clamp(a.w, minVal.w, maxVal.w) };
	}

	inline Float2 Clamp(const Float2& a, const Float& minVal, const Float& maxVal)
	{
		return { Clamp(a.x, minVal.x, maxVal.x), Clamp(a.y, minVal.x, maxVal.x) };
	}

	inline Float3 Clamp(const Float3& a, const Float& minVal, const Float& maxVal)
	{
		return { Clamp(a.x, minVal.x, maxVal.x), Clamp(a.y, minVal.x, maxVal.x), Clamp(a.z, minVal.x, maxVal.x) };
	}

	inline Float4 Clamp(const Float4& a, const Float& minVal, const Float& maxVal)
	{
		return { Clamp(a.x, minVal.x, maxVal.x),
				Clamp(a.y, minVal.x, maxVal.x),
				Clamp(a.z, minVal.x, maxVal.x),
				Clamp(a.w, minVal.x, maxVal.x) };
	}

	//*************************************
	// Mix

	inline Ceng::FLOAT32 Mix(Ceng::FLOAT32 x, Ceng::FLOAT32 y, Ceng::FLOAT32 a)
	{
		return x * (1.0f - a) + y * a;
	}

	inline Float Mix(const Float& x, const Float& y, const Float& a)
	{
		return Mix(x.x, y.x, a.x);
	}

	inline Float2 Mix(const Float2& x, const Float2& y, const Float2& a)
	{
		return { Mix(x.x, y.x, a.x), Mix(x.y, y.y, a.y) };
	}

	inline Float3 Mix(const Float3& x, const Float3& y, const Float3& a)
	{
		return { Mix(x.x, y.x, a.x), Mix(x.y, y.y, a.y), Mix(x.z, y.z, a.z) };
	}

	inline Float4 Mix(const Float4& x, const Float4& y, const Float4& a)
	{
		return { Mix(x.x, y.x, a.x), Mix(x.y, y.y, a.y), Mix(x.z, y.z, a.z), Mix(x.w, y.w, a.w) };
	}

	inline Float2 Mix(const Float2& x, const Float2& y, const Float& a)
	{
		return { Mix(x.x, y.x, a.x), Mix(x.y, y.y, a.x) };
	}

	inline Float3 Mix(const Float3& x, const Float3& y, const Float& a)
	{
		return { Mix(x.x, y.x, a.x), Mix(x.y, y.y, a.x), Mix(x.z, y.z, a.x) };
	}

	inline Float4 Mix(const Float4& x, const Float4& y, const Float& a)
	{
		return { Mix(x.x, y.x, a.x), Mix(x.y, y.y, a.x), Mix(x.z, y.z, a.x), Mix(x.w, y.w, a.x) };
	}
}

#endif