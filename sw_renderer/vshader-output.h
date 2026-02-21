/*****************************************************************************
*
* cr-vshader-output.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CR_VSHADER_OUTPUT_H
#define _CENG_CR_VSHADER_OUTPUT_H

#include <immintrin.h>

#include <ceng/enums/shader-datatype.h>
#include <ceng/enums/shader-semantic.h>

#include <ceng/math/ce-vector.h>

namespace Ceng::Vshader
{
	class CR_VertexShaderOutput
	{
	public:
		POINTER *destAddress;
		POINTER destOffset;
	};

	struct VertexShaderOutputRegister
	{
		CR_VertexShaderOutput* variable;
	};

	class OutFloat : public CR_VertexShaderOutput
	{
	public:

		OutFloat& operator = (const FLOAT32 source)
		{
			Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)(*destAddress + destOffset);

			*destPtr = source;

			return *this;
		}
	};

	class OutFloat2 : public CR_VertexShaderOutput
	{
	public:

		OutFloat2& operator = (const VectorF2& source)
		{
			__m128d temp = _mm_load_sd((double*)&source);

			_mm_store_sd((double*)(*destAddress + destOffset), temp);

			return *this;
		}
	};

	class OutFloat4 : public CR_VertexShaderOutput
	{
	public:

		OutFloat4& operator = (const VectorF4& source)
		{
			__m128 temp = _mm_load_ps((float*)&source);

			_mm_store_ps((float*)(*destAddress + destOffset), temp);

			return *this;
		}
	};
};

#endif