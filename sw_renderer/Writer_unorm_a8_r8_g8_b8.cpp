#include "Writer_unorm_a8_r8_g8_b8.h"

#include "WriterCommon.h"

#include <ceng/swshader/pshader-sampler.h>

using namespace Ceng;

Writer_unorm_a8_r8_g8_b8::~Writer_unorm_a8_r8_g8_b8()
{

}


void Writer_unorm_a8_r8_g8_b8::Release()
{
	delete this;
}

void Writer_unorm_a8_r8_g8_b8::WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverage)
{

}

void Writer_unorm_a8_r8_g8_b8::WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverage)
{

}

void Writer_unorm_a8_r8_g8_b8::WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverage)
{

}

void Writer_unorm_a8_r8_g8_b8::WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverage)
{

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