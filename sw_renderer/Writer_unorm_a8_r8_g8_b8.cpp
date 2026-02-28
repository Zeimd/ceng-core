#include "Writer_unorm_a8_r8_g8_b8.h"

#include "WriterCommon.h"

#include <ceng/swshader/pshader-types.h>

#include <emmintrin.h>
#include <xmmintrin.h>

using namespace Ceng;

//******************************************************************************
// Writer_unorm_a8_r8_g8_b8_noblend

Writer_unorm_a8_r8_g8_b8_noblend::~Writer_unorm_a8_r8_g8_b8_noblend()
{

}


void Writer_unorm_a8_r8_g8_b8_noblend::Release()
{
	delete this;
}

void Writer_unorm_a8_r8_g8_b8_noblend::WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unorm_a8_r8_g8_b8_noblend::WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unorm_a8_r8_g8_b8_noblend::WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unorm_a8_r8_g8_b8_noblend::WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{
	float* sourcePtr = (float*) & source._x;
	float* dest = (float*)targetAddress;

	const INT8* coverage = &coverageTable8[coverageIndex][0];

	__m128 colorScaleVec = _mm_load1_ps(&colorScale8);

	// Pixel shader always writes ABGR, but this render target is ARGB,
	// so swap red and blue

	__m128 redChannel = _mm_load_ps(&sourcePtr[0]);
	__m128 greenChannel = _mm_load_ps(&sourcePtr[4]);
	__m128 blueChannel = _mm_load_ps(&sourcePtr[8]);
	__m128 alphaChannel = _mm_load_ps(&sourcePtr[12]);

	blueChannel = _mm_mul_ps(blueChannel, colorScaleVec);
	greenChannel = _mm_mul_ps(greenChannel, colorScaleVec);
	redChannel = _mm_mul_ps(redChannel, colorScaleVec);
	alphaChannel = _mm_mul_ps(alphaChannel, colorScaleVec);

	__m128i blueInt = _mm_cvtps_epi32(blueChannel);
	__m128i greenInt = _mm_cvtps_epi32(greenChannel);
	__m128i redInt = _mm_cvtps_epi32(redChannel);
	__m128i alphaInt = _mm_cvtps_epi32(alphaChannel);

	// br_word = {r3,r2,r1,r0} {b3,b2,b1,b0}
	__m128i gb_Word = _mm_packus_epi32(blueInt, greenInt);

	// ga_word = {a3,a2,a1,a0} {g3,g2,g1,g0}
	__m128i ar_Word = _mm_packus_epi32(redInt, alphaInt);

	// writeVec =  {a3,a2,a1,a0} {g3,g2,g1,g0} {r3,r2,r1,r0} {b3,b2,b1,b0}
	__m128i writeVec = _mm_packus_epi16(gb_Word, ar_Word);

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
}

void Writer_unorm_a8_r8_g8_b8_noblend::WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex)
{
	_declspec(align(16)) Ceng::FLOAT32 writeBuffer[16];

	sampler.SampleToUnbyte4(writeBuffer);

	float* sourcePtr = writeBuffer;
	float* dest = (float*)writeAddress;

	const INT8* coverage = &coverageTable8[coverageIndex][0];

	// Source is ubyte4

	__m128i writeVec;

	__m128* writeVecF = (__m128*) & writeVec;

	*writeVecF = _mm_load_ps(sourcePtr);

	// Pixel shader always writes ABGR, but this render target is ARGB,
	// so swap red and blue

	writeVec = _mm_shuffle_epi32(writeVec, 0b11000110);

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
}

//******************************************************************************
// Writer_unorm_a8_r8_g8_b8_noblend

Writer_unorm_a8_r8_g8_b8::Writer_unorm_a8_r8_g8_b8(Ceng::UINT32 writeMask, std::array<Ceng::FLOAT32, 4>& blendFactors)
	: writeMask(writeMask)
{
	Ceng::UINT16 red = Ceng::UINT16(blendFactors[0] * 256.0f);
	Ceng::UINT16 green = Ceng::UINT16(blendFactors[1] * 256.0f);
	Ceng::UINT16 blue = Ceng::UINT16(blendFactors[2] * 256.0f);
	Ceng::UINT16 alpha = Ceng::UINT16(blendFactors[3] * 256.0f);

	this->apiBlendFactors[0] = blue;
	this->apiBlendFactors[1] = blue;
	this->apiBlendFactors[2] = blue;
	this->apiBlendFactors[3] = blue;

	this->apiBlendFactors[4] = green;
	this->apiBlendFactors[5] = green;
	this->apiBlendFactors[6] = green;
	this->apiBlendFactors[7] = green;

	this->apiBlendFactors[8] = red;
	this->apiBlendFactors[9] = red;
	this->apiBlendFactors[10] = red;
	this->apiBlendFactors[11] = red;

	this->apiBlendFactors[12] = alpha;
	this->apiBlendFactors[13] = alpha;
	this->apiBlendFactors[14] = alpha;
	this->apiBlendFactors[15] = alpha;
}

Writer_unorm_a8_r8_g8_b8::~Writer_unorm_a8_r8_g8_b8()
{

}


void Writer_unorm_a8_r8_g8_b8::Release()
{
	delete this;
}

void Writer_unorm_a8_r8_g8_b8::WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unorm_a8_r8_g8_b8::WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unorm_a8_r8_g8_b8::WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unorm_a8_r8_g8_b8::WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{
	float* sourcePtr = (float*)&source._x;
	float* dest = (float*)targetAddress;

	const INT8* coverage = &coverageTable8[coverageIndex][0];

	__m128 colorScaleVec = _mm_load1_ps(&colorScale8);

	// Pixel shader always writes ABGR, but this render target is ARGB,
	// so swap red and blue

	__m128 redChannel = _mm_load_ps(&sourcePtr[0]);
	__m128 greenChannel = _mm_load_ps(&sourcePtr[4]);
	__m128 blueChannel = _mm_load_ps(&sourcePtr[8]);
	__m128 alphaChannel = _mm_load_ps(&sourcePtr[12]);

	blueChannel = _mm_mul_ps(blueChannel, colorScaleVec);
	greenChannel = _mm_mul_ps(greenChannel, colorScaleVec);
	redChannel = _mm_mul_ps(redChannel, colorScaleVec);
	alphaChannel = _mm_mul_ps(alphaChannel, colorScaleVec);

	__m128i blueInt = _mm_cvtps_epi32(blueChannel);
	__m128i greenInt = _mm_cvtps_epi32(greenChannel);
	__m128i redInt = _mm_cvtps_epi32(redChannel);
	__m128i alphaInt = _mm_cvtps_epi32(alphaChannel);

	// br_word = {r3,r2,r1,r0} {b3,b2,b1,b0}
	__m128i gb_Word = _mm_packus_epi32(blueInt, greenInt);

	// ga_word = {a3,a2,a1,a0} {g3,g2,g1,g0}
	__m128i ar_Word = _mm_packus_epi32(redInt, alphaInt);

	// writeVec =  {a3,a2,a1,a0} {g3,g2,g1,g0} {r3,r2,r1,r0} {b3,b2,b1,b0}
	__m128i writeVec = _mm_packus_epi16(gb_Word, ar_Word);

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
}

void Writer_unorm_a8_r8_g8_b8::WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex)
{
	_declspec(align(16)) Ceng::FLOAT32 writeBuffer[16];

	sampler.SampleToUnbyte4(writeBuffer);

	float* sourcePtr = writeBuffer;
	float* dest = (float*)writeAddress;

	const INT8* coverage = &coverageTable8[coverageIndex][0];

	// Source is ubyte4

	__m128i writeVec;

	__m128* writeVecF = (__m128*) & writeVec;

	*writeVecF = _mm_load_ps(sourcePtr);

	// Pixel shader always writes ABGR, but this render target is ARGB,
	// so swap red and blue

	writeVec = _mm_shuffle_epi32(writeVec, 0b11000110);

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
}