#include "Writer_unbyte_argb.h"

#include "WriterCommon.h"

#include <ceng/swshader/pshader-types.h>

#include <emmintrin.h>
#include <xmmintrin.h>

using namespace Ceng;

//******************************************************************************
// Writer_unbyte_argb_noblend

Writer_unbyte_argb_noblend::~Writer_unbyte_argb_noblend()
{

}


void Writer_unbyte_argb_noblend::Release()
{
	delete this;
}

void Writer_unbyte_argb_noblend::WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unbyte_argb_noblend::WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unbyte_argb_noblend::WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unbyte_argb_noblend::WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex)
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

void Writer_unbyte_argb_noblend::WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex)
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

static alignas(16) Ceng::UINT8 uint8_max[4][4] =
{
	{255, 255, 255, 255},
	{255, 255, 255, 255},
	{255, 255, 255, 255},
	{255, 255, 255, 255},
};

static alignas(16) Ceng::UINT16 fx_0_8_max[] = { 255, 255, 255, 255, 255,255,255,255 };

void unbyte_argb_ColorBlend_zero(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	*out = _mm_setzero_si128();
}

void unbyte_argb_ColorBlend_one(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	*out = _mm_load_si128((__m128i*)uint8_max);
}

void unbyte_argb_ColorBlend_source_color(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	*out = *source;
}

void unbyte_argb_ColorBlend_invert_source_color(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// source = byte { {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedSource = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedSource = _mm_xor_si128(maxValues, *source);

	*out = invertedSource;
}

void unbyte_argb_ColorBlend_source_alpha(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// source = byte { {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	// allAlpha = byte { {a3,a2,a1,a0} , {a3,a2,a1,a0}, {a3,a2,a1,a0} , {a3,a2,a1,a0}
	__m128i allAlpha = _mm_shuffle_epi32(*source, 0b11111111);

	*out = allAlpha;
}

void unbyte_argb_ColorBlend_invert_source_alpha(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// source = byte { {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	// allAlpha = byte { {a3,a2,a1,a0} , {a3,a2,a1,a0}, {a3,a2,a1,a0} , {a3,a2,a1,a0}
	__m128i allAlpha = _mm_shuffle_epi32(*source, 0b11111111);

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedAlpha = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedAlpha = _mm_xor_si128(maxValues, allAlpha);

	*out = invertedAlpha;
}

void unbyte_argb_ColorBlend_dest_alpha(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// dest = byte { {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	// allAlpha = byte { {a3,a2,a1,a0} , {a3,a2,a1,a0}, {a3,a2,a1,a0} , {a3,a2,a1,a0}
	__m128i allAlpha = _mm_shuffle_epi32(*dest, 0b11111111);

	*out = allAlpha;
}

void unbyte_argb_ColorBlend_invert_dest_alpha(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// dest = byte { {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	// allAlpha = byte { {a3,a2,a1,a0} , {a3,a2,a1,a0}, {a3,a2,a1,a0} , {a3,a2,a1,a0}
	__m128i allAlpha = _mm_shuffle_epi32(*dest, 0b11111111);

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedAlpha = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedAlpha = _mm_xor_si128(maxValues, allAlpha);

	*out = invertedAlpha;
}

void unbyte_argb_ColorBlend_dest_color(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// dest = byte { {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	*out = *dest;	
}

void unbyte_argb_ColorBlend_invert_dest_color(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// dest = byte { {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedSource = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedSource = _mm_xor_si128(maxValues, *dest);

	*out = invertedSource;
}

void unbyte_argb_ColorBlend_source_alpha_saturate(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// 255 - dest
	__m128i invertedDest = _mm_xor_si128(maxValues, *dest);

	__m128i minimum = _mm_min_epu8(*source, invertedDest);

	// allAlpha = byte { {a3,a2,a1,a0} , {a3,a2,a1,a0}, {a3,a2,a1,a0} , {a3,a2,a1,a0}
	__m128i allAlpha = _mm_shuffle_epi32(minimum, 0b11111111);

	*out = allAlpha;
}

void unbyte_argb_ColorBlend_blend_factor(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	*out = _mm_load_si128((__m128i*)&apiBlendFactors[0]);
}

void unbyte_argb_ColorBlend_invert_blend_factor(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i factors = _mm_load_si128((__m128i*) & apiBlendFactors[0]);

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedSource = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedSource = _mm_xor_si128(maxValues, factors);

	*out = invertedSource;
}

void unbyte_argb_ColorBlend_second_source_color(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// TODO: needs to be implemented completely differently
}

void unbyte_argb_ColorBlend_invert_second_source_color(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// TODO: needs to be implemented completely differently
}

void unbyte_argb_ColorBlend_second_source_alpha(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// TODO: needs to be implemented completely differently
}

void unbyte_argb_ColorBlend_invert_second_source_alpha(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// TODO: needs to be implemented completely differently
}

static BlendPrepareColorCallback colorFactorCallbacks[] =
{
	&unbyte_argb_ColorBlend_zero,
	&unbyte_argb_ColorBlend_one,

	&unbyte_argb_ColorBlend_source_color,
	&unbyte_argb_ColorBlend_invert_source_color,

	& unbyte_argb_ColorBlend_source_alpha,
	& unbyte_argb_ColorBlend_invert_source_alpha,

	& unbyte_argb_ColorBlend_dest_alpha,
	& unbyte_argb_ColorBlend_invert_dest_alpha,

	& unbyte_argb_ColorBlend_dest_color,
	& unbyte_argb_ColorBlend_invert_dest_color,

	& unbyte_argb_ColorBlend_source_alpha_saturate,

	& unbyte_argb_ColorBlend_blend_factor,
	& unbyte_argb_ColorBlend_invert_blend_factor,

	& unbyte_argb_ColorBlend_second_source_color,
	& unbyte_argb_ColorBlend_invert_second_source_color,

	& unbyte_argb_ColorBlend_second_source_alpha,
	& unbyte_argb_ColorBlend_invert_second_source_alpha,
};

//************************************************************************
// Alpha prepare callbacks

void unbyte_argb_AlphaBlend_zero(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	__m128i alpha = _mm_setzero_si128();

	*inout_factors = _mm_blend_epi16(color, alpha, 0b11000000);
}

void unbyte_argb_AlphaBlend_one(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	__m128i alpha = _mm_load_si128((__m128i*)uint8_max);

	*inout_factors = _mm_blend_epi16(color, alpha, 0b11000000);
}

void unbyte_argb_AlphaBlend_source_alpha(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	*inout_factors = _mm_blend_epi16(color, *source, 0b11000000);
}

void unbyte_argb_AlphaBlend_invert_source_alpha(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedSource = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedSource = _mm_xor_si128(maxValues, *source);

	*inout_factors = _mm_blend_epi16(color, invertedSource, 0b11000000);
}

void unbyte_argb_AlphaBlend_dest_alpha(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	*inout_factors = _mm_blend_epi16(color, *dest, 0b11000000);
}

void unbyte_argb_AlphaBlend_invert_dest_alpha(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedDest = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedDest = _mm_xor_si128(maxValues, *dest);

	*inout_factors = _mm_blend_epi16(color, invertedDest, 0b11000000);
}

void unbyte_argb_AlphaBlend_source_alpha_saturate(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	*inout_factors = _mm_blend_epi16(color, maxValues, 0b11000000);
}

void unbyte_argb_AlphaBlend_blend_factor(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	__m128i factors = _mm_load_si128((__m128i*) & apiBlendFactors[0]);

	*inout_factors = _mm_blend_epi16(color, factors, 0b11000000);
}

void unbyte_argb_AlphaBlend_invert_blend_factor(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	__m128i color = *inout_factors;

	__m128i factors = _mm_load_si128((__m128i*) & apiBlendFactors[0]);

	__m128i maxValues = _mm_load_si128((__m128i*)uint8_max);

	// invertedFactors = byte { {255-a3,255-a2,255-a1,255-a0} , ...

	__m128i invertedFactors = _mm_xor_si128(maxValues, factors);

	*inout_factors = _mm_blend_epi16(color, invertedFactors, 0b11000000);
}

void unbyte_argb_AlphaBlend_second_source_alpha(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// TODO: needs to be implemented completely differently
}

void unbyte_argb_AlphaBlend_invert_second_source_alpha(__m128i* inout_factors, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors)
{
	// TODO: needs to be implemented completely differently
}

static BlendPrepareAlphaCallback alphaFactorCallbacks[] =
{
	&unbyte_argb_AlphaBlend_zero,
	&unbyte_argb_AlphaBlend_one,

	&unbyte_argb_AlphaBlend_source_alpha,
	&unbyte_argb_AlphaBlend_invert_source_alpha,

	&unbyte_argb_AlphaBlend_dest_alpha,
	&unbyte_argb_AlphaBlend_invert_dest_alpha,

	&unbyte_argb_AlphaBlend_source_alpha_saturate,

	&unbyte_argb_AlphaBlend_blend_factor,
	&unbyte_argb_AlphaBlend_invert_blend_factor,

	&unbyte_argb_AlphaBlend_second_source_alpha,
	&unbyte_argb_AlphaBlend_invert_second_source_alpha,
};

//************************************************************************
// Blend operation callbacks

// color blend operation = add
// alpha blend = add
void unbyte_argb_BlendOp_add_add(__m128i* out, __m128i* source, __m128i* dest)
{
	out[0] = _mm_add_epi16(source[0], dest[0]);
	out[1] = _mm_add_epi16(source[1], dest[1]);
}

// color blend operation = add
// alpha blend = sub
void unbyte_argb_BlendOp_add_sub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_add_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_add_epi16(source[1], dest[1]);

	__m128i alpha = _mm_sub_epi16(source[1], dest[1]);	

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = add
// alpha blend = reverse sub
void unbyte_argb_BlendOp_add_rsub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_add_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_add_epi16(source[1], dest[1]);

	__m128i alpha = _mm_sub_epi16(dest[1], source[1]);	

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = add
// alpha blend = min
void unbyte_argb_BlendOp_add_min(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_add_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_add_epi16(source[1], dest[1]);

	__m128i alpha = _mm_min_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = add
// alpha blend = max
void unbyte_argb_BlendOp_add_max(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_add_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_add_epi16(source[1], dest[1]);

	__m128i alpha = _mm_max_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

//*****************************


// color blend operation = sub
// alpha blend = add
void unbyte_argb_BlendOp_sub_add(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(source[1], dest[1]);

	__m128i alpha = _mm_add_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = sub
// alpha blend = sub
void unbyte_argb_BlendOp_sub_sub(__m128i* out, __m128i* source, __m128i* dest)
{
	out[0] = _mm_sub_epi16(source[0], dest[0]);
	out[1] = _mm_sub_epi16(source[1], dest[1]);
}

// color blend operation = sub
// alpha blend = reverse sub
void unbyte_argb_BlendOp_sub_rsub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(source[1], dest[1]);

	__m128i alpha = _mm_sub_epi16(dest[1], source[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = sub
// alpha blend = min
void unbyte_argb_BlendOp_sub_min(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(source[1], dest[1]);

	__m128i alpha = _mm_min_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = sub
// alpha blend = max
void unbyte_argb_BlendOp_sub_max(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(source[1], dest[1]);

	__m128i alpha = _mm_max_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

//*****************************

// color blend operation = reverse sub
// alpha blend = add
void unbyte_argb_BlendOp_rsub_add(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(dest[0], source[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(dest[1], source[1]);

	__m128i alpha = _mm_add_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = reverse sub
// // alpha blend = sub
void unbyte_argb_BlendOp_rsub_sub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(dest[0], source[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(dest[1], source[1]);

	__m128i alpha = _mm_sub_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = reverse sub
// alpha blend = reverse sub
void unbyte_argb_BlendOp_rsub_rsub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(dest[0], source[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(dest[1], source[1]);

	__m128i alpha = _mm_sub_epi16(dest[1], source[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = reverse sub
// alpha blend = min
void unbyte_argb_BlendOp_rsub_min(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(dest[0], source[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(dest[1], source[1]);

	__m128i alpha = _mm_min_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = reverse sub
// alpha blend = max
void unbyte_argb_BlendOp_rsub_max(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_sub_epi16(dest[0], source[0]);

	// separate operations for red and alpha

	__m128i red = _mm_sub_epi16(dest[1], source[1]);

	__m128i alpha = _mm_max_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

//*****************************

// color blend operation = min
// alpha blend = add
void unbyte_argb_BlendOp_min_add(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_min_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_min_epi16(source[1], dest[1]);

	__m128i alpha = _mm_add_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = min
// alpha blend = sub
void unbyte_argb_BlendOp_min_sub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_min_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_min_epi16(source[1], dest[1]);

	__m128i alpha = _mm_sub_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = min
// alpha blend = reverse sub
void unbyte_argb_BlendOp_min_rsub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_min_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_min_epi16(source[1], dest[1]);

	__m128i alpha = _mm_sub_epi16(dest[1], source[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = min
// alpha blend = min
void unbyte_argb_BlendOp_min_min(__m128i* out, __m128i* source, __m128i* dest)
{
	out[0] = _mm_min_epi16(source[0], dest[0]);
	out[1] = _mm_min_epi16(source[1], dest[1]);
}

// color blend operation = min
// alpha blend = max
void unbyte_argb_BlendOp_min_max(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_min_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_min_epi16(source[1], dest[1]);

	__m128i alpha = _mm_max_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

//*****************************

// color blend operation = max
// alpha blend = add
void unbyte_argb_BlendOp_max_add(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_max_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_max_epi16(source[1], dest[1]);

	__m128i alpha = _mm_add_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = max
// alpha blend = sub
void unbyte_argb_BlendOp_max_sub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_max_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_max_epi16(source[1], dest[1]);

	__m128i alpha = _mm_sub_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = max
// alpha blend = reverse sub
void unbyte_argb_BlendOp_max_rsub(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_max_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_max_epi16(source[1], dest[1]);

	__m128i alpha = _mm_sub_epi16(dest[1], source[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = max
// alpha blend = min
void unbyte_argb_BlendOp_max_min(__m128i* out, __m128i* source, __m128i* dest)
{
	// lower input only contains color channels
	out[0] = _mm_max_epi16(source[0], dest[0]);

	// separate operations for red and alpha

	__m128i red = _mm_max_epi16(source[1], dest[1]);

	__m128i alpha = _mm_min_epi16(source[1], dest[1]);

	out[1] = _mm_blend_epi16(red, alpha, 0b11110000);
}

// color blend operation = max
// alpha blend = max
void unbyte_argb_BlendOp_max_max(__m128i* out, __m128i* source, __m128i* dest)
{
	out[0] = _mm_max_epi16(source[0], dest[0]);
	out[1] = _mm_max_epi16(source[1], dest[1]);
}

static BlendOpCallback opCallbacks[5][5] =
{
	{
		&unbyte_argb_BlendOp_add_add,
		&unbyte_argb_BlendOp_add_sub,
		&unbyte_argb_BlendOp_add_rsub,
		&unbyte_argb_BlendOp_add_min,
		&unbyte_argb_BlendOp_add_max,
	},

	{
		&unbyte_argb_BlendOp_sub_add,
		&unbyte_argb_BlendOp_sub_sub,
		&unbyte_argb_BlendOp_sub_rsub,
		&unbyte_argb_BlendOp_sub_min,
		&unbyte_argb_BlendOp_sub_max,
	},

	{
		&unbyte_argb_BlendOp_rsub_add,
		&unbyte_argb_BlendOp_rsub_sub,
		&unbyte_argb_BlendOp_rsub_rsub,
		&unbyte_argb_BlendOp_rsub_min,
		&unbyte_argb_BlendOp_rsub_max,
	},

	{
		&unbyte_argb_BlendOp_min_add,
		&unbyte_argb_BlendOp_min_sub,
		&unbyte_argb_BlendOp_min_rsub,
		&unbyte_argb_BlendOp_min_min,
		&unbyte_argb_BlendOp_min_max,
	},

	{
		&unbyte_argb_BlendOp_max_add,
		&unbyte_argb_BlendOp_max_sub,
		&unbyte_argb_BlendOp_max_rsub,
		&unbyte_argb_BlendOp_max_min,
		&unbyte_argb_BlendOp_max_max,
	}
};

//******************************************************************************
// Writer_unorm_a8_r8_g8_b8

Writer_unbyte_argb::Writer_unbyte_argb(Ceng::RenderTargetBlendDesc& desc, std::array<Ceng::FLOAT32, 4>& blendFactors)
	: writeMask(desc.writeMask)
{
	Ceng::UINT8 red = Ceng::UINT8(blendFactors[0] * 255.0f);
	Ceng::UINT8 green = Ceng::UINT8(blendFactors[1] * 255.0f);
	Ceng::UINT8 blue = Ceng::UINT8(blendFactors[2] * 255.0f);
	Ceng::UINT8 alpha = Ceng::UINT8(blendFactors[3] * 255.0f);

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

	prepareSource = colorFactorCallbacks[desc.sourceBlend];
	prepareDest = colorFactorCallbacks[desc.destBlend];

	prepareSourceAlpha = alphaFactorCallbacks[desc.sourceBlendAlpha];
	prepareDestAlpha = alphaFactorCallbacks[desc.destBlendAlpha];

	blendOperation = opCallbacks[desc.blendOp][desc.blendAlphaOp];
	
}

Writer_unbyte_argb::~Writer_unbyte_argb()
{

}


void Writer_unbyte_argb::Release()
{
	delete this;
}

void Writer_unbyte_argb::WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unbyte_argb::WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unbyte_argb::WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{

}

void Writer_unbyte_argb::WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex)
{
	// TODO

	/*
	float* sourcePtr = (float*)&source._x;
	float* dest = (float*)targetAddress;

	const INT8* coverage = &coverageTable8[coverageIndex][0];

	const INT8* blendWriteMask = &blendWriteMaskTable8_abgr_soa[writeMask][0][0];

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

	// gb_word = {g3,g2,g1,g0} {b3,b2,b1,b0}
	__m128i gb_Word = _mm_packus_epi32(blueInt, greenInt);

	// ar_word = {a3,a2,a1,a0} {r3,r2,r1,r0}
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
	*/
}

void Writer_unbyte_argb::WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex)
{
	_declspec(align(16)) Ceng::FLOAT32 writeBuffer[16];

	sampler.SampleToUnbyte4(writeBuffer);

	float* sourcePtr = writeBuffer;
	float* dest = (float*)writeAddress;

	const INT8* coverage = &coverageTable8[coverageIndex][0];

	const INT8* blendWriteMask = &blendWriteMaskTable8_abgr_soa[writeMask][0][0];

	// Source is ubyte4

	__m128i writeVec;

	__m128* writeVecF = (__m128*) & writeVec;

	*writeVecF = _mm_load_ps(sourcePtr);

	// Pixel shader always writes ABGR, but this render target is ARGB,
	// so swap red and blue

	writeVec = _mm_shuffle_epi32(writeVec, 0b11000110);

	__m128i destVec = _mm_load_si128((__m128i*)dest);

	// We are operating in SOA, so both source and dest are in the following format:
	// byte{ {a3,a2,a1,a0} , {r3,r2,r1,r0}, {g3,g2,g1,g0} , {b3,b2,b1,b0}

	__m128i sourceFactors;
	__m128i destFactors;

	(*prepareSource)(&sourceFactors, &writeVec, &destVec, apiBlendFactors);
	(*prepareSourceAlpha)(&sourceFactors, &writeVec, &destVec, apiBlendFactors);

	(*prepareDest)(&destFactors, &writeVec, &destVec, apiBlendFactors);
	(*prepareDestAlpha)(&destFactors, &writeVec, &destVec, apiBlendFactors);

	// Convert source to 8.8 fixed point (using 255 ~ 1.0f)

	__m128i allZeroes = _mm_setzero_si128();

	// sourceLow = word { {g3, g2, g1, g0} , {b3, b2, b1, b0} }
	__m128i sourceLow = _mm_unpacklo_epi8(writeVec, allZeroes);

	// sourceLow = word { {a3, a2, a1, a0} , {r3, r2, r1, r0} }
	__m128i sourceHigh = _mm_unpackhi_epi8(writeVec, allZeroes);

	// Convert source factors to 8.8 fixed point (using 255 ~ 1.0f)

	// sourceLow = word { {g3, g2, g1, g0} , {b3, b2, b1, b0} }
	__m128i sourceFactorLow = _mm_unpacklo_epi8(sourceFactors, allZeroes);

	// sourceLow = word { {a3, a2, a1, a0} , {r3, r2, r1, r0} }
	__m128i sourceFactorHigh = _mm_unpackhi_epi8(sourceFactors, allZeroes);

	// Multiply source values with source factors

	__m128i sourceMul[2];

	sourceMul[0] = _mm_mullo_epi16(sourceFactorLow, sourceLow);

	sourceMul[0] = _mm_srli_epi16(sourceMul[0], 8);

	sourceMul[1] = _mm_mullo_epi16(sourceFactorHigh, sourceHigh);

	sourceMul[1] = _mm_srli_epi16(sourceMul[1], 8);

	//***************************************************************

	// Convert destination values to 8.8 fixed point (using 255 ~ 1.0f)

	// destLow = word { {g3, g2, g1, g0} , {b3, b2, b1, b0} }
	__m128i destLow = _mm_unpacklo_epi8(destVec, allZeroes);

	// destHigh = word { {a3, a2, a1, a0} , {r3, r2, r1, r0} }
	__m128i destHigh = _mm_unpackhi_epi8(destVec, allZeroes);

	// Convert destination factors to 8.8 fixed point (using 255 ~ 1.0f)

	// sourceLow = word { {g3, g2, g1, g0} , {b3, b2, b1, b0} }
	__m128i destFactorLow = _mm_unpacklo_epi8(destFactors, allZeroes);

	// sourceLow = word { {a3, a2, a1, a0} , {r3, r2, r1, r0} }
	__m128i destFactorHigh = _mm_unpackhi_epi8(destFactors, allZeroes);

	// Multiply source values with source factors

	__m128i destMul[2];

	destMul[0] = _mm_mullo_epi16(destFactorLow, destLow);

	destMul[0] = _mm_srli_epi16(destMul[0], 8);

	destMul[1] = _mm_mullo_epi16(destFactorHigh, destHigh);

	destMul[1] = _mm_srli_epi16(destMul[1], 8);

	__m128i blendResult[2];

	(*blendOperation)(blendResult, sourceMul, destMul);

	// Now
	// blendResult[0] = word { {g3,g2,g1,g0}, {b3,b2,b1,b0} }
	// blendResult[1] = word { {a3,a2,a1,a0}, {r3,r2,r1,r0} }

	// writeVec =  {a3,a2,a1,a0} {g3,g2,g1,g0} {r3,r2,r1,r0} {b3,b2,b1,b0}
	writeVec = _mm_packus_epi16(blendResult[0], blendResult[1]);

	__m128i writeMaskVec = _mm_load_si128((__m128i*)blendWriteMask);

	__m128 coverageVecF = _mm_load1_ps((float*)coverage);

	__m128i* coverageVec = (__m128i*) & coverageVecF;

	*coverageVec = _mm_and_epi32(*coverageVec, writeMaskVec);

	// Select pixels from render target that won't be overwritten
	destVec = _mm_andnot_si128(*coverageVec, destVec);

	// Select pixels from input that will be written
	writeVec = _mm_and_si128(*coverageVec, writeVec);

	// Combine pixels
	writeVec = _mm_or_si128(writeVec, destVec);

	_mm_store_si128((__m128i*)dest, writeVec);
}