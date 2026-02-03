#pragma once

#ifndef CENG_PSHADER_OUTPUT_H
#define CENG_PSHADER_OUTPUT_H

#include "../math/ce-vector.h"

#include "pshader-types.h"

#include "pshader-uniform.h"
#include "pshader-sampler.h"

#include "PshaderTargetWriter.h"

namespace Ceng::Pshader
{
	const FLOAT32 colorScaleScalar = FLOAT32(255.0f);

	_declspec(align(64)) const Ceng::INT8 coverageTable8[16][4] =
	{
		{ 0, 0, 0, 0 },
		{ -1, 0, 0, 0 },
		{ 0, -1, 0, 0 },
		{ -1, -1, 0, 0 },
		{ 0, 0, -1, 0 },
		{ -1, 0, -1, 0 },
		{ 0, -1, -1, 0 },
		{ -1, -1, -1, 0 },
		{ 0, 0, 0, -1 },
		{ -1, 0, 0, -1 },
		{ 0, -1, 0, -1 },
		{ -1, -1, 0, -1 },
		{ 0, 0, -1, -1 },
		{ -1, 0, -1, -1 },
		{ 0, -1, -1, -1 },
		{ -1, -1, -1, -1 }
	};

	class CR_psOutputRegister
	{
	public:

		Pshader::PshaderTargetWriter* writer;

		// Location of render target address.
		POINTER inputAddress;

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
			/*
			POINTER *localWrite = (POINTER*)(inputAddress);

			(*call_from_Float[bufferFormat])((void*)(*localWrite),(void*)&source.x,
												(void*)(*coverageAddress));
			*/
			//POINTER* localWrite = (POINTER*)(inputAddress);

			POINTER* localWrite = (POINTER*)(inputAddress);

			writer->WriteFloat(source, (void*)(*localWrite), *coverageMask);

			*localWrite += 16;
			return *this;			
		}

		inline OutFloat4& operator = (const Pshader::Float4 &source)
		{
			//POINTER *localWrite = (POINTER*)(inputAddress);			

			/*
			(*call_from_Float4[bufferFormat]) ( (void*)(*localWrite),(void*)source.dataAddress,
													(void*)(*coverageAddress));
													*/
													
			
			/*
			// NOTE: use this code blob

			float *dest = (float*)(*localWrite);

			const INT8 *coverage = &coverageTable8[(INT32)(*coverageAddress)][0];

			__m128 colorScaleVec = _mm_load1_ps(&colorScaleScalar);

			float *sourcePtr = (float*)&source._x;

			__m128 blueChannel = _mm_load_ps(&sourcePtr[0]);
			__m128 greenChannel = _mm_load_ps(&sourcePtr[4]);
			__m128 redChannel = _mm_load_ps(&sourcePtr[8]);
			__m128 alphaChannel = _mm_load_ps(&sourcePtr[12]);

			blueChannel = _mm_mul_ps(blueChannel, colorScaleVec);
			greenChannel = _mm_mul_ps(greenChannel, colorScaleVec);
			redChannel = _mm_mul_ps(redChannel, colorScaleVec);
			alphaChannel = _mm_mul_ps(alphaChannel, colorScaleVec);

			__m128i blueInt = _mm_cvtps_epi32(blueChannel);
			__m128i greenInt = _mm_cvtps_epi32(greenChannel);
			__m128i redInt = _mm_cvtps_epi32(redChannel);
			__m128i alphaInt = _mm_cvtps_epi32(alphaChannel);

			__m128i br_Word = _mm_packs_epi32(blueInt, redInt);
			__m128i ga_Word = _mm_packs_epi32(greenInt, alphaInt);

			__m128i writeVec = _mm_packs_epi16(br_Word, ga_Word);

			__m128 coverageVecF = _mm_load1_ps((float*)coverage);

			__m128i *coverageVec = (__m128i*)&coverageVecF;

			__m128i destVec = _mm_load_si128((__m128i*)dest);

			// Select pixels from render target that won't be overwritten
			destVec = _mm_andnot_si128(*coverageVec, destVec);

			// Select pixels from input that will be written
			writeVec = _mm_and_si128(*coverageVec, writeVec);

			// Combine pixels
			writeVec = _mm_or_si128(writeVec, destVec);

			_mm_store_si128((__m128i*)dest, writeVec);
			*/

			POINTER *localWrite = (POINTER*)(inputAddress);	

			writer->WriteFloat4(source, (void*)*localWrite, *coverageMask);

			*localWrite += 16;
			return *this;
		}

		/*
		inline void Write(const Ceng::VectorF4 &source,const Ceng::INT32 coverageIndex)
		{
			POINTER *localWrite = (POINTER*)(inputAddress);

			
			//(*call_from_Float[bufferFormat])((void*)(*localWrite), (void*)source,
				//(void*)(*coverageAddress));
				

			const INT8 *coverage = &coverageTable8[coverageIndex][0];

			_declspec(align(16)) Ceng::UINT8 writeBuffer[16];

			// blue
			writeBuffer[0] = Ceng::UINT8(255.0f*source.x);
			writeBuffer[1] = Ceng::UINT8(255.0f*source.x);
			writeBuffer[2] = Ceng::UINT8(255.0f*source.x);
			writeBuffer[3] = Ceng::UINT8(255.0f*source.x);

			// green
			writeBuffer[4] = Ceng::UINT8(255.0f*source.y);
			writeBuffer[5] = Ceng::UINT8(255.0f*source.y);
			writeBuffer[6] = Ceng::UINT8(255.0f*source.y);
			writeBuffer[7] = Ceng::UINT8(255.0f*source.y);

			// red
			writeBuffer[8] = Ceng::UINT8(255.0f*source.z);
			writeBuffer[9] = Ceng::UINT8(255.0f*source.z);
			writeBuffer[10] = Ceng::UINT8(255.0f*source.z);
			writeBuffer[11] = Ceng::UINT8(255.0f*source.z);

			writeBuffer[12] = Ceng::UINT8(255.0f*source.w);
			writeBuffer[13] = Ceng::UINT8(255.0f*source.w);
			writeBuffer[14] = Ceng::UINT8(255.0f*source.w);
			writeBuffer[15] = Ceng::UINT8(255.0f*source.w);

			// Source is ubyte4

			//float *sourcePtr = writeBuffer;
			float *dest = (float*)(*localWrite);

			__m128i writeVec;

			__m128 *writeVecF = (__m128*)&writeVec;

			*writeVecF = _mm_load_ps((float*)writeBuffer);

			__m128 coverageVecF = _mm_load1_ps((float*)coverage);

			__m128i *coverageVec = (__m128i*)&coverageVecF;

			__m128i destVec = _mm_load_si128((__m128i*)dest);

			// Select pixels from render target that won't be overwritten
			destVec = _mm_andnot_si128(*coverageVec, destVec);

			// Select pixels from input that will be written
			writeVec = _mm_and_si128(*coverageVec, writeVec);

			// Combine pixels
			writeVec = _mm_or_si128(writeVec, destVec);

			//_mm_adds_epu8(writeVec, destVec);

			_mm_store_si128((__m128i*)dest, writeVec);


			*localWrite += 16;

		};
		*/

		/*
		inline void Write(const Pshader::SampleTexture2D &source, const Ceng::INT32 coverageIndex)
		{
			_declspec(align(16)) Ceng::FLOAT32 writeBuffer[16];

			source.SampleToFloat4(writeBuffer);

			POINTER *localWrite = (POINTER*)(inputAddress);

			float *sourcePtr = writeBuffer;
			float *dest = (float*)(*localWrite);

			const INT8 *coverage = &coverageTable8[coverageIndex][0];

			// Source is ubyte4

			__m128i writeVec;

			__m128 *writeVecF = (__m128*)&writeVec;

			*writeVecF = _mm_load_ps(sourcePtr);

			__m128 coverageVecF = _mm_load1_ps((float*)coverage);

			__m128i *coverageVec = (__m128i*)&coverageVecF;

			__m128i destVec = _mm_load_si128((__m128i*)dest);

			// Select pixels from render target that won't be overwritten
			destVec = _mm_andnot_si128(*coverageVec, destVec);

			// Select pixels from input that will be written
			writeVec = _mm_and_si128(*coverageVec, writeVec);

			// Combine pixels
			writeVec = _mm_or_si128(writeVec, destVec);

			_mm_store_si128((__m128i*)dest, writeVec);

			/*

			// Source is float4

			__m128 colorScaleVec = _mm_load1_ps(&colorScaleScalar);
		
			__m128 blueChannel = _mm_load_ps(&sourcePtr[0]);
			__m128 greenChannel = _mm_load_ps(&sourcePtr[4]);
			__m128 redChannel = _mm_load_ps(&sourcePtr[8]);
			__m128 alphaChannel = _mm_load_ps(&sourcePtr[12]);

			blueChannel = _mm_mul_ps(blueChannel, colorScaleVec);
			greenChannel = _mm_mul_ps(greenChannel, colorScaleVec);
			redChannel = _mm_mul_ps(redChannel, colorScaleVec);
			alphaChannel = _mm_mul_ps(alphaChannel, colorScaleVec);

			__m128i blueInt = _mm_cvtps_epi32(blueChannel);
			__m128i greenInt = _mm_cvtps_epi32(greenChannel);
			__m128i redInt = _mm_cvtps_epi32(redChannel);
			__m128i alphaInt = _mm_cvtps_epi32(alphaChannel);

			__m128i br_Word = _mm_packs_epi32(blueInt, redInt);
			__m128i ga_Word = _mm_packs_epi32(greenInt, alphaInt);

			__m128i writeVec = _mm_packus_epi16(br_Word, ga_Word);

			__m128 coverageVecF = _mm_load1_ps((float*)coverage);

			__m128i *coverageVec = (__m128i*)&coverageVecF;

			__m128i destVec = _mm_load_si128((__m128i*)dest);

			// Select pixels from render target that won't be overwritten
			destVec = _mm_andnot_si128(*coverageVec, destVec);

			// Select pixels from input that will be written
			writeVec = _mm_and_si128(*coverageVec, writeVec);

			// Combine pixels
			writeVec = _mm_or_si128(writeVec, destVec);

			_mm_store_si128((__m128i*)dest, writeVec);
			*/

			// Step quad chain's target address to next quad on the right
			//*localWrite += 16;
		//}
		

		inline void Write(const Pshader::DelayedSampler2D& source, const Ceng::INT32 coverageIndex)
		{
			_declspec(align(16)) Ceng::FLOAT32 writeBuffer[16];

			source.SampleToFloat4(writeBuffer);

			POINTER* localWrite = (POINTER*)(inputAddress);

			float* sourcePtr = writeBuffer;
			float* dest = (float*)(*localWrite);

			const INT8* coverage = &coverageTable8[coverageIndex][0];

			// Source is ubyte4

			__m128i writeVec;

			__m128* writeVecF = (__m128*) & writeVec;

			*writeVecF = _mm_load_ps(sourcePtr);

			__m128 coverageVecF = _mm_load1_ps((float*)coverage);

			__m128i* coverageVec = (__m128i*) & coverageVecF;

			__m128i destVec = _mm_load_si128((__m128i*)dest);

			// Select pixels from render target that won't be overwritten
			destVec = _mm_andnot_si128(*coverageVec, destVec);

			// Select pixels from input that will be written
			writeVec = _mm_and_si128(*coverageVec, writeVec);

			// Combine pixels
			writeVec = _mm_or_si128(writeVec, destVec);

			_mm_store_si128((__m128i*)dest, writeVec);

			/*

			// Source is float4

			__m128 colorScaleVec = _mm_load1_ps(&colorScaleScalar);

			__m128 blueChannel = _mm_load_ps(&sourcePtr[0]);
			__m128 greenChannel = _mm_load_ps(&sourcePtr[4]);
			__m128 redChannel = _mm_load_ps(&sourcePtr[8]);
			__m128 alphaChannel = _mm_load_ps(&sourcePtr[12]);

			blueChannel = _mm_mul_ps(blueChannel, colorScaleVec);
			greenChannel = _mm_mul_ps(greenChannel, colorScaleVec);
			redChannel = _mm_mul_ps(redChannel, colorScaleVec);
			alphaChannel = _mm_mul_ps(alphaChannel, colorScaleVec);

			__m128i blueInt = _mm_cvtps_epi32(blueChannel);
			__m128i greenInt = _mm_cvtps_epi32(greenChannel);
			__m128i redInt = _mm_cvtps_epi32(redChannel);
			__m128i alphaInt = _mm_cvtps_epi32(alphaChannel);

			__m128i br_Word = _mm_packs_epi32(blueInt, redInt);
			__m128i ga_Word = _mm_packs_epi32(greenInt, alphaInt);

			__m128i writeVec = _mm_packus_epi16(br_Word, ga_Word);

			__m128 coverageVecF = _mm_load1_ps((float*)coverage);

			__m128i *coverageVec = (__m128i*)&coverageVecF;

			__m128i destVec = _mm_load_si128((__m128i*)dest);

			// Select pixels from render target that won't be overwritten
			destVec = _mm_andnot_si128(*coverageVec, destVec);

			// Select pixels from input that will be written
			writeVec = _mm_and_si128(*coverageVec, writeVec);

			// Combine pixels
			writeVec = _mm_or_si128(writeVec, destVec);

			_mm_store_si128((__m128i*)dest, writeVec);
			*/

			// Step quad chain's target address to next quad on the right
			*localWrite += 16;
		}

		inline OutFloat4& operator = (const Pshader::DelayedSampler2D &source)
		{
			POINTER *localWrite = (POINTER*)(inputAddress);

			/*
			(*call_from_Float4[bufferFormat]) ((void*)(*localWrite), (void*)source.dataAddress,
				(void*)(*coverageAddress));
				*/

			float *dest = (float*)(*localWrite);

			const INT8 *coverage = &coverageTable8[*coverageMask][0];

			__m128 colorScaleVec = _mm_load1_ps(&colorScaleScalar);

			float *sourcePtr = (float*)source.dataAddress;

			__m128 blueChannel = _mm_load_ps(&sourcePtr[0]);
			__m128 greenChannel = _mm_load_ps(&sourcePtr[4]);
			__m128 redChannel = _mm_load_ps(&sourcePtr[8]);
			__m128 alphaChannel = _mm_load_ps(&sourcePtr[12]);

			blueChannel = _mm_mul_ps(blueChannel, colorScaleVec);
			greenChannel = _mm_mul_ps(greenChannel, colorScaleVec);
			redChannel = _mm_mul_ps(redChannel, colorScaleVec);
			alphaChannel = _mm_mul_ps(alphaChannel, colorScaleVec);

			__m128i blueInt = _mm_cvtps_epi32(blueChannel);
			__m128i greenInt = _mm_cvtps_epi32(greenChannel);
			__m128i redInt = _mm_cvtps_epi32(redChannel);
			__m128i alphaInt = _mm_cvtps_epi32(alphaChannel);

			__m128i br_Word = _mm_packs_epi32(blueInt, redInt);
			__m128i ga_Word = _mm_packs_epi32(greenInt, alphaInt);

			__m128i writeVec = _mm_packs_epi16(br_Word, ga_Word);

			__m128 coverageVecF = _mm_load1_ps((float*)coverage);

			__m128i *coverageVec = (__m128i*)&coverageVecF;

			__m128i destVec = _mm_load_si128((__m128i*)dest);

			// Select pixels from render target that won't be overwritten
			destVec = _mm_andnot_si128(*coverageVec, destVec);

			// Select pixels from input that will be written
			writeVec = _mm_and_si128(*coverageVec, writeVec);

			// Combine pixels
			writeVec = _mm_or_si128(writeVec, destVec);

			_mm_store_si128((__m128i*)dest, writeVec);

			// Step quad chain's target address to next quad on the right
			*localWrite += 16;
			return *this;
		}	
	};
};

#endif