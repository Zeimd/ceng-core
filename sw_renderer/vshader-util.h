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
		return  { a._x < b._x, a._y < b._y };
	}

	inline Bool3 LessThan(const Float3& a, const Float3& b)
	{
		return  { a._x < b._x, a._y < b._y, a._z < b._z };
	}

	inline Bool4 LessThan(const Float4& a, const Float4& b)
	{
		return  { a._x < b._x, a._y < b._y, a._z < b._z, a._w < b._w };
	}

	//**********************************
	// Vector form for <= operator

	inline Bool2 LessThanEqual(const Float2& a, const Float2& b)
	{
		return  { a._x <= b._x, a._y <= b._y };
	}

	inline Bool3 LessThanEqual(const Float3& a, const Float3& b)
	{
		return  { a._x <= b._x, a._y <= b._y, a._z <= b._z };
	}

	inline Bool4 LessThanEqual(const Float4& a, const Float4& b)
	{
		return  { a._x <= b._x, a._y <= b._y, a._z <= b._z, a._w <= b._w };
	}

	//**********************************
	// Vector form for > operator

	inline Bool2 GreaterThan(const Float2& a, const Float2& b)
	{
		return  { a._x > b._x, a._y > b._y };
	}

	inline Bool3 GreaterThan(const Float3& a, const Float3& b)
	{
		return  { a._x > b._x, a._y > b._y, a._z > b._z };
	}

	inline Bool4 GreaterThan(const Float4& a, const Float4& b)
	{
		return  { a._x > b._x, a._y > b._y, a._z > b._z, a._w > b._w };
	}

	//**********************************
	// Vector form for <= operator

	inline Bool2 GreaterThanEqual(const Float2& a, const Float2& b)
	{
		return  { a._x >= b._x, a._y >= b._y };
	}

	inline Bool3 GreaterThanEqual(const Float3& a, const Float3& b)
	{
		return  { a._x >= b._x, a._y >= b._y, a._z >= b._z };
	}

	inline Bool4 GreaterThanEqual(const Float4& a, const Float4& b)
	{
		return  { a._x >= b._x, a._y >= b._y, a._z >= b._z, a._w >= b._w };
	}

	//**********************************
	// Vector form for == operator

	inline Bool2 Equal(const Float2& a, const Float2& b)
	{
		return  { a._x == b._x, a._y == b._y };
	}

	inline Bool3 Equal(const Float3& a, const Float3& b)
	{
		return  { a._x == b._x, a._y == b._y, a._z == b._z };
	}

	inline Bool4 Equal(const Float4& a, const Float4& b)
	{
		return  { a._x == b._x, a._y == b._y, a._z == b._z, a._w == b._w };
	}

	//**********************************
	// Vector form for != operator

	inline Bool2 NotEqual(const Float2& a, const Float2& b)
	{
		return  { a._x != b._x, a._y != b._y };
	}

	inline Bool3 NotEqual(const Float3& a, const Float3& b)
	{
		return  { a._x != b._x, a._y != b._y, a._z != b._z };
	}

	inline Bool4 NotEqual(const Float4& a, const Float4& b)
	{
		return  { a._x != b._x, a._y != b._y, a._z != b._z, a._w != b._w };
	}

	//**********************************
	// Any bool check

	inline Bool Any(const Bool2& a)
	{
		return LogicalOr(a.x, a.y);
	}

	inline Bool Any(const Bool3& a)
	{
		return LogicalOr(LogicalOr(a.x, a.y), a.z);
	}

	inline Bool Any(const Bool4& a)
	{
		return LogicalOr(LogicalOr(LogicalOr(a.x, a.y), a.z), a.w);
	}

	//**********************************
	// All bool check

	inline Bool All(const Bool2& a)
	{
		return LogicalAnd(a.x, a.y);
	}

	inline Bool All(const Bool3& a)
	{
		return LogicalAnd(LogicalAnd(a.x, a.y), a.z);
	}

	inline Bool All(const Bool4& a)
	{
		return LogicalAnd(LogicalAnd(LogicalAnd(a.x, a.y), a.z), a.w);
	}

	//**********************************
	// Boolean vector negation

	inline Bool2 Not(const Bool2& a)
	{
		return { LogicalNot(a.x),LogicalNot(a.y) };
	}

	inline Bool3 Not(const Bool3& a)
	{
		return { LogicalNot(a.x),LogicalNot(a.y),LogicalNot(a.z) };
	}

	inline Bool4 Not(const Bool4& a)
	{
		return { LogicalNot(a.x),LogicalNot(a.y),LogicalNot(a.z),LogicalNot(a.w) };
	}



	//*************************************
	// Absolute value


	inline SOAVecFloat Abs(const SOAVecFloat& x)
	{
		return { fabsf(x.a), fabsf(x.b), fabsf(x.c), fabsf(x.d) };
	}

	inline Float Abs(const Float& a)
	{
		return Abs(a.x);
	}

	inline Float2 Abs(const Float2& a)
	{
		return { Abs(a._x), Abs(a._y) };
	}

	inline Float3 Abs(const Float3& a)
	{
		return { Abs(a._x), Abs(a._y), Abs(a._z) };
	}

	inline Float4 Abs(const Float4& a)
	{
		return { Abs(a._x), Abs(a._y), Abs(a._z), Abs(a._w) };
	}


	//*************************************
	// Sign function


	inline SOAVecFloat Sign(const SOAVecFloat& x)
	{
		return { (Ceng::FLOAT32)copysign(1.0f, x.a),
			(Ceng::FLOAT32)copysign(1.0f, x.a),
			(Ceng::FLOAT32)copysign(1.0f, x.a),
			(Ceng::FLOAT32)copysign(1.0f, x.a) };
	}

	inline Float Sign(const Float& a)
	{
		return Sign(a.x);
	}

	inline Float2 Sign(const Float2& a)
	{
		return { Sign(a._x), Sign(a._y) };
	}

	inline Float3 Sign(const Float3& a)
	{
		return { Sign(a._x), Sign(a._y), Sign(a._z) };
	}

	inline Float4 Sign(const Float4& a)
	{
		return { Sign(a._x), Sign(a._y), Sign(a._z), Sign(a._w) };
	}


	//*************************************
	// Floor


	inline SOAVecFloat Floor(const SOAVecFloat& x)
	{
		return { floorf(x.a), floorf(x.b), floorf(x.c), floorf(x.d) };
	}

	inline Float Floor(const Float& a)
	{
		return Floor(a.x);
	}

	inline Float2 Floor(const Float2& a)
	{
		return { Floor(a._x), Floor(a._y) };
	}

	inline Float3 Floor(const Float3& a)
	{
		return { Floor(a._x), Floor(a._y), Floor(a._z) };
	}

	inline Float4 Floor(const Float4& a)
	{
		return { Floor(a._x), Floor(a._y), Floor(a._z), Floor(a._w) };
	}


	//*************************************
	// Ceil


	inline SOAVecFloat Ceil(const SOAVecFloat& x)
	{
		return { ceilf(x.a), ceilf(x.b), ceilf(x.c), ceilf(x.d) };
	}

	inline Float Ceil(const Float& a)
	{
		return Ceil(a.x);
	}

	inline Float2 Ceil(const Float2& a)
	{
		return { Ceil(a._x), Ceil(a._y) };
	}

	inline Float3 Ceil(const Float3& a)
	{
		return { Ceil(a._x), Ceil(a._y), Ceil(a._z) };
	}

	inline Float4 Ceil(const Float4& a)
	{
		return { Ceil(a._x), Ceil(a._y), Ceil(a._z), Ceil(a._w) };
	}


	//*************************************
	// Truncate


	inline SOAVecFloat Trunc(const SOAVecFloat& x)
	{
		return { truncf(x.a), truncf(x.b), truncf(x.c), truncf(x.d) };
	}

	inline Float Trunc(const Float& a)
	{
		return Trunc(a.x);
	}

	inline Float2 Trunc(const Float2& a)
	{
		return { Trunc(a._x), Trunc(a._y) };
	}

	inline Float3 Trunc(const Float3& a)
	{
		return { Trunc(a._x), Trunc(a._y), Trunc(a._z) };
	}

	inline Float4 Trunc(const Float4& a)
	{
		return { Trunc(a._x), Trunc(a._y), Trunc(a._z), Trunc(a._w) };
	}


	//*************************************
	// Round


	inline SOAVecFloat Round(const SOAVecFloat& x)
	{
		return { roundf(x.a), roundf(x.b), roundf(x.c), roundf(x.d) };
	}

	inline Float Round(const Float& a)
	{
		return Round(a.x);
	}

	inline Float2 Round(const Float2& a)
	{
		return { Round(a._x), Round(a._y) };
	}

	inline Float3 Round(const Float3& a)
	{
		return { Round(a._x), Round(a._y), Round(a._z) };
	}

	inline Float4 Round(const Float4& a)
	{
		return { Round(a._x), Round(a._y), Round(a._z), Round(a._w) };
	}


	//*************************************
	// Round half to even


	inline SOAVecFloat RoundEven(const SOAVecFloat& x)
	{
		return { roundf(x.a * 0.5f) * 2.0f,
			roundf(x.b * 0.5f) * 2.0f,
			roundf(x.c * 0.5f) * 2.0f,
			roundf(x.d * 0.5f) * 2.0f };

	}

	inline Float RoundEven(const Float& a)
	{
		return RoundEven(a.x);
	}

	inline Float2 RoundEven(const Float2& a)
	{
		return { RoundEven(a._x), RoundEven(a._y) };
	}

	inline Float3 RoundEven(const Float3& a)
	{
		return { RoundEven(a._x), RoundEven(a._y), RoundEven(a._z) };
	}

	inline Float4 RoundEven(const Float4& a)
	{
		return { RoundEven(a._x), RoundEven(a._y), RoundEven(a._z), RoundEven(a._w) };
	}


	//*************************************
	// Fractional part


	inline SOAVecFloat Fract(const SOAVecFloat& x)
	{
		return x - Floor(x);
	}

	inline Float Fract(const Float& a)
	{
		return Fract(a.x);
	}

	inline Float2 Fract(const Float2& a)
	{
		return { Fract(a._x), Fract(a._y) };
	}

	inline Float3 Fract(const Float3& a)
	{
		return { Fract(a._x), Fract(a._y), Fract(a._z) };
	}

	inline Float4 Fract(const Float4& a)
	{
		return { Fract(a._x), Fract(a._y), Fract(a._z), Fract(a._w) };
	}


	//*************************************
	// Modulus


	inline SOAVecFloat Mod(const SOAVecFloat& a, const SOAVecFloat& b)
	{
		return a - b * Floor(a / b);
	}

	inline Float Fract(const Float& a, const Float& b)
	{
		return Mod(a.x, b.x);
	}

	inline Float2 Fract(const Float2& a, const Float& b)
	{
		return { Mod(a._x, b.x), Mod(a._y, b.x) };
	}

	inline Float3 Fract(const Float3& a, const Float& b)
	{
		return { Mod(a._x, b.x), Mod(a._y, b.x), Mod(a._z, b.x) };
	}

	inline Float4 Fract(const Float4& a, const Float& b)
	{
		return { Mod(a._x, b.x), Mod(a._y, b.x), Mod(a._z, b.x), Mod(a._w, b.x) };
	}

	inline Float2 Fract(const Float2& a, const Float2& b)
	{
		return { Mod(a._x, b._x), Mod(a._y, b._y) };
	}

	inline Float3 Fract(const Float3& a, const Float3& b)
	{
		return { Mod(a._x, b._x), Mod(a._y, b._y), Mod(a._z, b._z) };
	}

	inline Float4 Fract(const Float4& a, const Float4& b)
	{
		return { Mod(a._x, b._x), Mod(a._y, b._y), Mod(a._z, b._z), Mod(a._w, b._w) };
	}


	//*************************************
	// modf

	//*************************************
	// min


	inline SOAVecFloat Min(const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { std::min(x.a, y.a), std::min(x.b, y.b), std::min(x.c, y.c), std::min(x.d, y.d) };
	}

	inline Float Min(const Float& a, const Float& b)
	{
		return Min(a.x, b.x);
	}

	inline Float2 Min(const Float2& a, const Float2& b)
	{
		return { Min(a._x, b._x), Min(a._y, b._y) };
	}

	inline Float3 Min(const Float3& a, const Float3& b)
	{
		return { Min(a._x, b._x), Min(a._y, b._y), Min(a._z, b._z) };
	}

	inline Float4 Min(const Float4& a, const Float4& b)
	{
		return { Min(a._x, b._x), Min(a._y, b._y), Min(a._z, b._z), Min(a._w, b._w) };
	}

	inline Float2 Min(const Float2& a, const Float& b)
	{
		return { Min(a._x, b.x), Min(a._y, b.x) };
	}

	inline Float3 Min(const Float3& a, const Float& b)
	{
		return { Min(a._x, b.x), Min(a._y, b.x), Min(a._z, b.x) };
	}

	inline Float4 Min(const Float4& a, const Float& b)
	{
		return { Min(a._x, b.x), Min(a._y, b.x), Min(a._z, b.x), Min(a._w, b.x) };
	}

	//*************************************
	// max

	inline SOAVecFloat Max(const SOAVecFloat& x, const SOAVecFloat& y)
	{
		return { std::max(x.a, y.a), std::max(x.b, y.b), std::max(x.c, y.c), std::max(x.d, y.d) };
	}

	inline Float Max(const Float& a, const Float& b)
	{
		return Max(a.x, b.x);
	}

	inline Float2 Max(const Float2& a, const Float2& b)
	{
		return { Max(a._x, b._x), Max(a._y, b._y) };
	}

	inline Float3 Max(const Float3& a, const Float3& b)
	{
		return { Max(a._x, b._x), Max(a._y, b._y), Max(a._z, b._z) };
	}

	inline Float4 Max(const Float4& a, const Float4& b)
	{
		return { Max(a._x, b._x), Max(a._y, b._y), Max(a._z, b._z), Max(a._w, b._w) };
	}

	inline Float2 Max(const Float2& a, const Float& b)
	{
		return { Max(a._x, b.x), Max(a._y, b.x) };
	}

	inline Float3 Max(const Float3& a, const Float& b)
	{
		return { Max(a._x, b.x), Max(a._y, b.x), Max(a._z, b.x) };
	}

	inline Float4 Max(const Float4& a, const Float& b)
	{
		return { Max(a._x, b.x), Max(a._y, b.x), Max(a._z, b.x), Max(a._w, b.x) };
	}

	//*************************************
	// Clamp

	inline SOAVecFloat Clamp(const SOAVecFloat& x, const SOAVecFloat& minVal, const SOAVecFloat& maxVal)
	{
		return Min(Max(x, minVal), maxVal);
	}

	inline Float Clamp(const Float& a, const Float& minVal, const Float& maxVal)
	{
		return Clamp(a.x, minVal.x, maxVal.x);
	}

	inline Float2 Clamp(const Float2& a, const Float2& minVal, const Float2& maxVal)
	{
		return { Clamp(a._x, minVal._x, maxVal._x), Clamp(a._y, minVal._y, maxVal._y) };
	}

	inline Float3 Clamp(const Float3& a, const Float3& minVal, const Float3& maxVal)
	{
		return { Clamp(a._x, minVal._x, maxVal._x), Clamp(a._y, minVal._y, maxVal._y), Clamp(a._z, minVal._z, maxVal._z) };
	}

	inline Float4 Clamp(const Float4& a, const Float4& minVal, const Float4& maxVal)
	{
		return { Clamp(a._x, minVal._x, maxVal._x),
				Clamp(a._y, minVal._y, maxVal._y),
				Clamp(a._z, minVal._z, maxVal._z),
				Clamp(a._w, minVal._w, maxVal._w) };
	}

	inline Float2 Clamp(const Float2& a, const Float& minVal, const Float& maxVal)
	{
		return { Clamp(a._x, minVal.x, maxVal.x), Clamp(a._y, minVal.x, maxVal.x) };
	}

	inline Float3 Clamp(const Float3& a, const Float& minVal, const Float& maxVal)
	{
		return { Clamp(a._x, minVal.x, maxVal.x), Clamp(a._y, minVal.x, maxVal.x), Clamp(a._z, minVal.x, maxVal.x) };
	}

	inline Float4 Clamp(const Float4& a, const Float& minVal, const Float& maxVal)
	{
		return { Clamp(a._x, minVal.x, maxVal.x),
				Clamp(a._y, minVal.x, maxVal.x),
				Clamp(a._z, minVal.x, maxVal.x),
				Clamp(a._w, minVal.x, maxVal.x) };
	}

	//*************************************
	// Mix

	inline SOAVecFloat Mix(const SOAVecFloat& x, const SOAVecFloat& y, const SOAVecFloat& a)
	{
		return x * (SOAVecFloat(1.0f) - a) + y * a;
	}

	inline Float Mix(const Float& x, const Float& y, const Float& a)
	{
		return Mix(x.x, y.x, a.x);
	}

	inline Float2 Mix(const Float2& x, const Float2& y, const Float2& a)
	{
		return { Mix(x._x, y._x, a._x), Mix(x._y, y._y, a._y) };
	}

	inline Float3 Mix(const Float3& x, const Float3& y, const Float3& a)
	{
		return { Mix(x._x, y._x, a._x), Mix(x._y, y._y, a._y), Mix(x._z, y._z, a._z) };
	}

	inline Float4 Mix(const Float4& x, const Float4& y, const Float4& a)
	{
		return { Mix(x._x, y._x, a._x), Mix(x._y, y._y, a._y), Mix(x._z, y._z, a._z), Mix(x._w, y._w, a._w) };
	}

	inline Float2 Mix(const Float2& x, const Float2& y, const Float& a)
	{
		return { Mix(x._x, y._x, a.x), Mix(x._y, y._y, a.x) };
	}

	inline Float3 Mix(const Float3& x, const Float3& y, const Float& a)
	{
		return { Mix(x._x, y._x, a.x), Mix(x._y, y._y, a.x), Mix(x._z, y._z, a.x) };
	}

	inline Float4 Mix(const Float4& x, const Float4& y, const Float& a)
	{
		return { Mix(x._x, y._x, a.x), Mix(x._y, y._y, a.x), Mix(x._z, y._z, a.x), Mix(x._w, y._w, a.x) };
	}
}

#endif