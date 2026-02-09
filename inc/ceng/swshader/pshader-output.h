#pragma once

#ifndef CENG_PSHADER_OUTPUT_H
#define CENG_PSHADER_OUTPUT_H

#include "../math/ce-vector.h"

#include "pshader-types.h"

#include "pshader-uniform.h"

#include "PshaderTargetWriter.h"

namespace Ceng::Pshader
{
	class CR_psOutputRegister
	{
	public:

		Pshader::PshaderTargetWriter* writer;

		// Location of render target address.
		POINTER inputAddress;

		// How much to step per write cycle
		Ceng::UINT32 quadWriteStep;

		// Pointer to quad coverage values
		Ceng::UINT32* coverageMask;

	};

	class OutFloat : public CR_psOutputRegister
	{
	};

	class OutFloat2 : public CR_psOutputRegister
	{
	};

	class OutFloat3 : public CR_psOutputRegister
	{
	};

	class OutFloat4 : public CR_psOutputRegister
	{
	public:

		inline OutFloat4& operator = (const Pshader::Float &source)
		{
			POINTER* localWrite = (POINTER*)(inputAddress);

			writer->WriteFloat(source, (void*)(*localWrite), *coverageMask);

			// TODO: use correct size of render target

			*localWrite += quadWriteStep;
			return *this;			
		}

		inline OutFloat4& operator = (const Pshader::Float2& source)
		{
			POINTER* localWrite = (POINTER*)(inputAddress);

			writer->WriteFloat2(source, (void*)(*localWrite), *coverageMask);

			// TODO: use correct size of render target

			*localWrite += quadWriteStep;
			return *this;
		}

		inline OutFloat4& operator = (const Pshader::Float3& source)
		{
			POINTER* localWrite = (POINTER*)(inputAddress);

			writer->WriteFloat3(source, (void*)(*localWrite), *coverageMask);

			// TODO: use correct size of render target

			*localWrite += quadWriteStep;
			return *this;
		}

		inline OutFloat4& operator = (const Pshader::Float4 &source)
		{
			POINTER *localWrite = (POINTER*)(inputAddress);	

			writer->WriteFloat4(source, (void*)*localWrite, *coverageMask);

			// TODO: use correct size of render target

			*localWrite += quadWriteStep;
			return *this;
		}

		inline OutFloat4& operator = (const Ceng::FLOAT32 source)
		{
			POINTER* localWrite = (POINTER*)(inputAddress);

			Float soaTemp;

			__m128 sourceVec = _mm_load1_ps(&source);

			_mm_store_ps((float*) &soaTemp.x, sourceVec);

			writer->WriteFloat(soaTemp, (void*)(*localWrite), *coverageMask);

			// TODO: use correct size of render target

			*localWrite += quadWriteStep;
			return *this;
		}

		inline OutFloat4& operator = (const Ceng::VectorF2& source)
		{
			POINTER* localWrite = (POINTER*)(inputAddress);

			Float2 soaTemp;

			__m128 sourceVecX = _mm_load1_ps(&source.x);
			__m128 sourceVecY = _mm_load1_ps(&source.y);

			_mm_store_ps((float*)&soaTemp._x, sourceVecX);
			_mm_store_ps((float*)&soaTemp._y, sourceVecY);

			writer->WriteFloat2(soaTemp, (void*)(*localWrite), *coverageMask);

			// TODO: use correct size of render target

			*localWrite += quadWriteStep;
			return *this;
		}

		inline OutFloat4& operator = (const Ceng::VectorF4& source)
		{
			POINTER* localWrite = (POINTER*)(inputAddress);

			Float4 soaTemp;

			__m128 sourceVecX = _mm_load1_ps(&source.x);
			__m128 sourceVecY = _mm_load1_ps(&source.y);
			__m128 sourceVecZ = _mm_load1_ps(&source.z);
			__m128 sourceVecW = _mm_load1_ps(&source.w);

			_mm_store_ps((float*)&soaTemp._x, sourceVecX);
			_mm_store_ps((float*)&soaTemp._y, sourceVecY);
			_mm_store_ps((float*)&soaTemp._z, sourceVecZ);
			_mm_store_ps((float*)&soaTemp._w, sourceVecW);

			writer->WriteFloat4(soaTemp, (void*)(*localWrite), *coverageMask);

			// TODO: use correct size of render target

			*localWrite += quadWriteStep;
			return *this;
		}

		inline OutFloat4& operator = (const Pshader::DelayedSampler2D &source)
		{
			POINTER* localWrite = (POINTER*)(inputAddress);

			void* dest = (void*)(*localWrite);

			writer->WriteSampler2d(source, dest, *coverageMask);

			*localWrite += quadWriteStep;

			return *this;
		}	
	};
};

#endif