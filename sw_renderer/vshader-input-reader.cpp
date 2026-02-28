/*****************************************************************************
*
* vshader-input.cpp
*
* By Jari Korkala 5/2013
*
* ----------------------------------------------
*
* Jari Korkala 8/2014
*
* - Renamed to vshader-input.cpp
*
*****************************************************************************/

#include <immintrin.h>
#include "vshader-input-reader.h"
#include "conversion_util.h"

namespace Ceng::Vshader
{
	void NullVertexReader(void* dest, void* source)
	{

	}

	//*************************************************
	// Destination is float

	void VSIN_FLOAT_FLOAT(void* dest, void* source);
	void VSIN_FLOAT_FLOAT2(void* dest, void* source);
	void VSIN_FLOAT_FLOAT3(void* dest, void* source);
	void VSIN_FLOAT_FLOAT4(void* dest, void* source);

	void VSIN_FLOAT_DOUBLE(void* dest, void* source);
	void VSIN_FLOAT_DOUBLE2(void* dest, void* source);
	void VSIN_FLOAT_DOUBLE3(void* dest, void* source);
	void VSIN_FLOAT_DOUBLE4(void* dest, void* source);	

	void VSIN_FLOAT_FP16(void* dest, void* source);
	void VSIN_FLOAT_FP16_2(void* dest, void* source);
	void VSIN_FLOAT_FP16_3(void* dest, void* source);
	void VSIN_FLOAT_FP16_4(void* dest, void* source);

	void VSIN_FLOAT_INT(void* dest, void* source);
	void VSIN_FLOAT_INT2(void* dest, void* source);
	void VSIN_FLOAT_INT3(void* dest, void* source);
	void VSIN_FLOAT_INT4(void* dest, void* source);

	void VSIN_FLOAT_UINT(void* dest, void* source);
	void VSIN_FLOAT_UINT2(void* dest, void* source);
	void VSIN_FLOAT_UINT3(void* dest, void* source);
	void VSIN_FLOAT_UINT4(void* dest, void* source);

	void VSIN_FLOAT_SHORT(void* dest, void* source);
	void VSIN_FLOAT_SHORT2(void* dest, void* source);
	void VSIN_FLOAT_SHORT3(void* dest, void* source);
	void VSIN_FLOAT_SHORT4(void* dest, void* source);

	void VSIN_FLOAT_USHORT(void* dest, void* source);
	void VSIN_FLOAT_USHORT2(void* dest, void* source);
	void VSIN_FLOAT_USHORT3(void* dest, void* source);
	void VSIN_FLOAT_USHORT4(void* dest, void* source);

	void VSIN_FLOAT_UNSHORT(void* dest, void* source);
	void VSIN_FLOAT_UNSHORT2(void* dest, void* source);
	void VSIN_FLOAT_UNSHORT3(void* dest, void* source);
	void VSIN_FLOAT_UNSHORT4(void* dest, void* source);

	void VSIN_FLOAT_NSHORT(void* dest, void* source);
	void VSIN_FLOAT_NSHORT2(void* dest, void* source);
	void VSIN_FLOAT_NSHORT3(void* dest, void* source);
	void VSIN_FLOAT_NSHORT4(void* dest, void* source);

	void VSIN_FLOAT_BYTE(void* dest, void* source);
	void VSIN_FLOAT_BYTE2(void* dest, void* source);
	void VSIN_FLOAT_BYTE3(void* dest, void* source);
	void VSIN_FLOAT_BYTE4(void* dest, void* source);

	void VSIN_FLOAT_UBYTE(void* dest, void* source);
	void VSIN_FLOAT_UBYTE2(void* dest, void* source);
	void VSIN_FLOAT_UBYTE3(void* dest, void* source);
	void VSIN_FLOAT_UBYTE4(void* dest, void* source);

	void VSIN_FLOAT_UNBYTE(void* dest, void* source);
	void VSIN_FLOAT_UNBYTE2(void* dest, void* source);
	void VSIN_FLOAT_UNBYTE3(void* dest, void* source);
	void VSIN_FLOAT_UNBYTE4(void* dest, void* source);	
	
	void VSIN_FLOAT_UNORM_R5_G6_B5(void* dest, void* source);	
	void VSIN_FLOAT_UNORM_B5_G6_R5(void* dest, void* source);
	
	void VSIN_FLOAT_UNORM_A1_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT_UNORM_A1_B5_G5_R5(void* dest, void* source);
		
	void VSIN_FLOAT_UNORM_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT_UNORM_B5_G5_R5(void* dest, void* source);
		
	void VSIN_FLOAT_UNORM_A4_R4_G4_B4(void* dest, void* source);
	void VSIN_FLOAT_UNORM_A4_B4_G4_R4(void* dest, void* source);
		
	void VSIN_FLOAT_UNORM_A6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT_UNORM_A6_B6_G6_R6(void* dest, void* source);
		
	void VSIN_FLOAT_UNORM_X6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT_UNORM_X6_B6_G6_R6(void* dest, void* source);
		
	void VSIN_FLOAT_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source);
	void VSIN_FLOAT_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source);	
	void VSIN_FLOAT_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source);	
	void VSIN_FLOAT_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source);
	
	void VSIN_FLOAT_UNORM_A2_B10_G10_R10(void* dest, void* source);	
	void VSIN_FLOAT_UINT_A2_B10_G10_R10(void* dest, void* source);
	
	void VSIN_FLOAT_UNORM_A8(void* dest, void* source);	
	void VSIN_FLOAT_UNORM_R1(void* dest, void* source);
	
	void VSIN_FLOAT_FLOAT_B10_G11_R11(void* dest, void* source);
	void VSIN_FLOAT_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source);

	void VSIN_FLOAT_UNORM_G8_B8_G8_R8(void* dest, void* source);	
	void VSIN_FLOAT_UNORM_B8_G8_R8_G8(void* dest, void* source);

	//*************************************************
	// Destination is float2

	void VSIN_FLOAT2_FLOAT(void* dest, void* source);
	void VSIN_FLOAT2_FLOAT2(void* dest, void* source);
	void VSIN_FLOAT2_FLOAT3(void* dest, void* source);
	void VSIN_FLOAT2_FLOAT4(void* dest, void* source);

	void VSIN_FLOAT2_DOUBLE(void* dest, void* source);
	void VSIN_FLOAT2_DOUBLE2(void* dest, void* source);
	void VSIN_FLOAT2_DOUBLE3(void* dest, void* source);
	void VSIN_FLOAT2_DOUBLE4(void* dest, void* source);

	void VSIN_FLOAT2_FP16(void* dest, void* source);
	void VSIN_FLOAT2_FP16_2(void* dest, void* source);
	void VSIN_FLOAT2_FP16_3(void* dest, void* source);
	void VSIN_FLOAT2_FP16_4(void* dest, void* source);

	void VSIN_FLOAT2_INT(void* dest, void* source);
	void VSIN_FLOAT2_INT2(void* dest, void* source);
	void VSIN_FLOAT2_INT3(void* dest, void* source);
	void VSIN_FLOAT2_INT4(void* dest, void* source);

	void VSIN_FLOAT2_UINT(void* dest, void* source);
	void VSIN_FLOAT2_UINT2(void* dest, void* source);
	void VSIN_FLOAT2_UINT3(void* dest, void* source);
	void VSIN_FLOAT2_UINT4(void* dest, void* source);

	void VSIN_FLOAT2_SHORT(void* dest, void* source);
	void VSIN_FLOAT2_SHORT2(void* dest, void* source);
	void VSIN_FLOAT2_SHORT3(void* dest, void* source);
	void VSIN_FLOAT2_SHORT4(void* dest, void* source);

	void VSIN_FLOAT2_USHORT(void* dest, void* source);
	void VSIN_FLOAT2_USHORT2(void* dest, void* source);
	void VSIN_FLOAT2_USHORT3(void* dest, void* source);
	void VSIN_FLOAT2_USHORT4(void* dest, void* source);

	void VSIN_FLOAT2_UNSHORT(void* dest, void* source);
	void VSIN_FLOAT2_UNSHORT2(void* dest, void* source);
	void VSIN_FLOAT2_UNSHORT3(void* dest, void* source);
	void VSIN_FLOAT2_UNSHORT4(void* dest, void* source);

	void VSIN_FLOAT2_NSHORT(void* dest, void* source);
	void VSIN_FLOAT2_NSHORT2(void* dest, void* source);
	void VSIN_FLOAT2_NSHORT3(void* dest, void* source);
	void VSIN_FLOAT2_NSHORT4(void* dest, void* source);

	void VSIN_FLOAT2_BYTE(void* dest, void* source);
	void VSIN_FLOAT2_BYTE2(void* dest, void* source);
	void VSIN_FLOAT2_BYTE3(void* dest, void* source);
	void VSIN_FLOAT2_BYTE4(void* dest, void* source);

	void VSIN_FLOAT2_UBYTE(void* dest, void* source);
	void VSIN_FLOAT2_UBYTE2(void* dest, void* source);
	void VSIN_FLOAT2_UBYTE3(void* dest, void* source);
	void VSIN_FLOAT2_UBYTE4(void* dest, void* source);

	void VSIN_FLOAT2_UNBYTE(void* dest, void* source);
	void VSIN_FLOAT2_UNBYTE2(void* dest, void* source);
	void VSIN_FLOAT2_UNBYTE3(void* dest, void* source);
	void VSIN_FLOAT2_UNBYTE4(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_R5_G6_B5(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_B5_G6_R5(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_A1_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_A1_B5_G5_R5(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_B5_G5_R5(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_A4_R4_G4_B4(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_A4_B4_G4_R4(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_A6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_A6_B6_G6_R6(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_X6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_X6_B6_G6_R6(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_A2_B10_G10_R10(void* dest, void* source);
	void VSIN_FLOAT2_UINT_A2_B10_G10_R10(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_A8(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_R1(void* dest, void* source);

	void VSIN_FLOAT2_FLOAT_B10_G11_R11(void* dest, void* source);
	void VSIN_FLOAT2_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source);

	void VSIN_FLOAT2_UNORM_G8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT2_UNORM_B8_G8_R8_G8(void* dest, void* source);

	//*************************************************
	// Destination is float3

	void VSIN_FLOAT3_FLOAT(void* dest, void* source);
	void VSIN_FLOAT3_FLOAT2(void* dest, void* source);
	void VSIN_FLOAT3_FLOAT3(void* dest, void* source);
	void VSIN_FLOAT3_FLOAT4(void* dest, void* source);

	void VSIN_FLOAT3_DOUBLE(void* dest, void* source);
	void VSIN_FLOAT3_DOUBLE2(void* dest, void* source);
	void VSIN_FLOAT3_DOUBLE3(void* dest, void* source);
	void VSIN_FLOAT3_DOUBLE4(void* dest, void* source);

	void VSIN_FLOAT3_FP16(void* dest, void* source);
	void VSIN_FLOAT3_FP16_2(void* dest, void* source);
	void VSIN_FLOAT3_FP16_3(void* dest, void* source);
	void VSIN_FLOAT3_FP16_4(void* dest, void* source);

	void VSIN_FLOAT3_INT(void* dest, void* source);
	void VSIN_FLOAT3_INT2(void* dest, void* source);
	void VSIN_FLOAT3_INT3(void* dest, void* source);
	void VSIN_FLOAT3_INT4(void* dest, void* source);

	void VSIN_FLOAT3_UINT(void* dest, void* source);
	void VSIN_FLOAT3_UINT2(void* dest, void* source);
	void VSIN_FLOAT3_UINT3(void* dest, void* source);
	void VSIN_FLOAT3_UINT4(void* dest, void* source);

	void VSIN_FLOAT3_SHORT(void* dest, void* source);
	void VSIN_FLOAT3_SHORT2(void* dest, void* source);
	void VSIN_FLOAT3_SHORT3(void* dest, void* source);
	void VSIN_FLOAT3_SHORT4(void* dest, void* source);

	void VSIN_FLOAT3_USHORT(void* dest, void* source);
	void VSIN_FLOAT3_USHORT2(void* dest, void* source);
	void VSIN_FLOAT3_USHORT3(void* dest, void* source);
	void VSIN_FLOAT3_USHORT4(void* dest, void* source);

	void VSIN_FLOAT3_UNSHORT(void* dest, void* source);
	void VSIN_FLOAT3_UNSHORT2(void* dest, void* source);
	void VSIN_FLOAT3_UNSHORT3(void* dest, void* source);
	void VSIN_FLOAT3_UNSHORT4(void* dest, void* source);

	void VSIN_FLOAT3_NSHORT(void* dest, void* source);
	void VSIN_FLOAT3_NSHORT2(void* dest, void* source);
	void VSIN_FLOAT3_NSHORT3(void* dest, void* source);
	void VSIN_FLOAT3_NSHORT4(void* dest, void* source);

	void VSIN_FLOAT3_BYTE(void* dest, void* source);
	void VSIN_FLOAT3_BYTE2(void* dest, void* source);
	void VSIN_FLOAT3_BYTE3(void* dest, void* source);
	void VSIN_FLOAT3_BYTE4(void* dest, void* source);

	void VSIN_FLOAT3_UBYTE(void* dest, void* source);
	void VSIN_FLOAT3_UBYTE2(void* dest, void* source);
	void VSIN_FLOAT3_UBYTE3(void* dest, void* source);
	void VSIN_FLOAT3_UBYTE4(void* dest, void* source);

	void VSIN_FLOAT3_UNBYTE(void* dest, void* source);
	void VSIN_FLOAT3_UNBYTE2(void* dest, void* source);
	void VSIN_FLOAT3_UNBYTE3(void* dest, void* source);
	void VSIN_FLOAT3_UNBYTE4(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_R5_G6_B5(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_B5_G6_R5(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_A1_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_A1_B5_G5_R5(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_B5_G5_R5(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_A4_R4_G4_B4(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_A4_B4_G4_R4(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_A6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_A6_B6_G6_R6(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_X6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_X6_B6_G6_R6(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_A2_B10_G10_R10(void* dest, void* source);
	void VSIN_FLOAT3_UINT_A2_B10_G10_R10(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_A8(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_R1(void* dest, void* source);

	void VSIN_FLOAT3_FLOAT_B10_G11_R11(void* dest, void* source);
	void VSIN_FLOAT3_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source);

	void VSIN_FLOAT3_UNORM_G8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT3_UNORM_B8_G8_R8_G8(void* dest, void* source);

	//*************************************************
	// Destination is float4

	void VSIN_FLOAT4_FLOAT(void* dest, void* source);
	void VSIN_FLOAT4_FLOAT2(void* dest, void* source);
	void VSIN_FLOAT4_FLOAT3(void* dest, void* source);
	void VSIN_FLOAT4_FLOAT4(void* dest, void* source);

	void VSIN_FLOAT4_DOUBLE(void* dest, void* source);
	void VSIN_FLOAT4_DOUBLE2(void* dest, void* source);
	void VSIN_FLOAT4_DOUBLE3(void* dest, void* source);
	void VSIN_FLOAT4_DOUBLE4(void* dest, void* source);

	void VSIN_FLOAT4_FP16(void* dest, void* source);
	void VSIN_FLOAT4_FP16_2(void* dest, void* source);
	void VSIN_FLOAT4_FP16_3(void* dest, void* source);
	void VSIN_FLOAT4_FP16_4(void* dest, void* source);

	void VSIN_FLOAT4_INT(void* dest, void* source);
	void VSIN_FLOAT4_INT2(void* dest, void* source);
	void VSIN_FLOAT4_INT3(void* dest, void* source);
	void VSIN_FLOAT4_INT4(void* dest, void* source);

	void VSIN_FLOAT4_UINT(void* dest, void* source);
	void VSIN_FLOAT4_UINT2(void* dest, void* source);
	void VSIN_FLOAT4_UINT3(void* dest, void* source);
	void VSIN_FLOAT4_UINT4(void* dest, void* source);

	void VSIN_FLOAT4_SHORT(void* dest, void* source);
	void VSIN_FLOAT4_SHORT2(void* dest, void* source);
	void VSIN_FLOAT4_SHORT3(void* dest, void* source);
	void VSIN_FLOAT4_SHORT4(void* dest, void* source);

	void VSIN_FLOAT4_USHORT(void* dest, void* source);
	void VSIN_FLOAT4_USHORT2(void* dest, void* source);
	void VSIN_FLOAT4_USHORT3(void* dest, void* source);
	void VSIN_FLOAT4_USHORT4(void* dest, void* source);

	void VSIN_FLOAT4_UNSHORT(void* dest, void* source);
	void VSIN_FLOAT4_UNSHORT2(void* dest, void* source);
	void VSIN_FLOAT4_UNSHORT3(void* dest, void* source);
	void VSIN_FLOAT4_UNSHORT4(void* dest, void* source);

	void VSIN_FLOAT4_NSHORT(void* dest, void* source);
	void VSIN_FLOAT4_NSHORT2(void* dest, void* source);
	void VSIN_FLOAT4_NSHORT3(void* dest, void* source);
	void VSIN_FLOAT4_NSHORT4(void* dest, void* source);

	void VSIN_FLOAT4_BYTE(void* dest, void* source);
	void VSIN_FLOAT4_BYTE2(void* dest, void* source);
	void VSIN_FLOAT4_BYTE3(void* dest, void* source);
	void VSIN_FLOAT4_BYTE4(void* dest, void* source);

	void VSIN_FLOAT4_UBYTE(void* dest, void* source);
	void VSIN_FLOAT4_UBYTE2(void* dest, void* source);
	void VSIN_FLOAT4_UBYTE3(void* dest, void* source);
	void VSIN_FLOAT4_UBYTE4(void* dest, void* source);

	void VSIN_FLOAT4_UNBYTE(void* dest, void* source);
	void VSIN_FLOAT4_UNBYTE2(void* dest, void* source);
	void VSIN_FLOAT4_UNBYTE3(void* dest, void* source);
	void VSIN_FLOAT4_UNBYTE4(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_R5_G6_B5(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_B5_G6_R5(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_A1_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_A1_B5_G5_R5(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_R5_G5_B5(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_B5_G5_R5(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_A4_R4_G4_B4(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_A4_B4_G4_R4(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_A6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_A6_B6_G6_R6(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_X6_R6_G6_B6(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_X6_B6_G6_R6(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_A2_B10_G10_R10(void* dest, void* source);
	void VSIN_FLOAT4_UINT_A2_B10_G10_R10(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_A8(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_R1(void* dest, void* source);

	void VSIN_FLOAT4_FLOAT_B10_G11_R11(void* dest, void* source);
	void VSIN_FLOAT4_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source);

	void VSIN_FLOAT4_UNORM_G8_B8_G8_R8(void* dest, void* source);
	void VSIN_FLOAT4_UNORM_B8_G8_R8_G8(void* dest, void* source);
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat2(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat3(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat4(Ceng::VTX_DATATYPE::value sourceFormat);

Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble2(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble3(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble4(Ceng::VTX_DATATYPE::value sourceFormat);

Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt2(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt3(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt4(Ceng::VTX_DATATYPE::value sourceFormat);

Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt2(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt3(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt4(Ceng::VTX_DATATYPE::value sourceFormat);

Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool2(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool3(Ceng::VTX_DATATYPE::value sourceFormat);
Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool4(Ceng::VTX_DATATYPE::value sourceFormat);


Ceng::Vshader::VertexShaderInputReader Ceng::Vshader::GetReadCallback(Ceng::SHADER_DATATYPE::value destFormat,
	Ceng::VTX_DATATYPE::value sourceFormat)
{
	switch (destFormat)
	{
	case Ceng::SHADER_DATATYPE::FLOAT:
		return GetReadCallbackFloat(sourceFormat);
	case Ceng::SHADER_DATATYPE::FLOAT2:
		return GetReadCallbackFloat2(sourceFormat);
	case Ceng::SHADER_DATATYPE::FLOAT3:
		return GetReadCallbackFloat3(sourceFormat);
	case Ceng::SHADER_DATATYPE::FLOAT4:
		return GetReadCallbackFloat4(sourceFormat);
		
	case Ceng::SHADER_DATATYPE::DOUBLE:
		return GetReadCallbackDouble(sourceFormat);
	case Ceng::SHADER_DATATYPE::DOUBLE2:
		return GetReadCallbackDouble2(sourceFormat);
	case Ceng::SHADER_DATATYPE::DOUBLE3:
		return GetReadCallbackDouble3(sourceFormat);
	case Ceng::SHADER_DATATYPE::DOUBLE4:
		return GetReadCallbackDouble4(sourceFormat);

	case Ceng::SHADER_DATATYPE::UINT:
		return GetReadCallbackUInt(sourceFormat);
	case Ceng::SHADER_DATATYPE::UINT2:
		return GetReadCallbackUInt2(sourceFormat);
	case Ceng::SHADER_DATATYPE::UINT3:
		return GetReadCallbackUInt3(sourceFormat);
	case Ceng::SHADER_DATATYPE::UINT4:
		return GetReadCallbackUInt4(sourceFormat);

	case Ceng::SHADER_DATATYPE::INT:
		return GetReadCallbackInt(sourceFormat);
	case Ceng::SHADER_DATATYPE::INT2:
		return GetReadCallbackInt2(sourceFormat);
	case Ceng::SHADER_DATATYPE::INT3:
		return GetReadCallbackInt3(sourceFormat);
	case Ceng::SHADER_DATATYPE::INT4:
		return GetReadCallbackInt4(sourceFormat);

	case Ceng::SHADER_DATATYPE::BOOL:
		return GetReadCallbackBool(sourceFormat);
	case Ceng::SHADER_DATATYPE::BOOL2:
		return GetReadCallbackBool2(sourceFormat);
	case Ceng::SHADER_DATATYPE::BOOL3:
		return GetReadCallbackBool3(sourceFormat);
	case Ceng::SHADER_DATATYPE::BOOL4:
		return GetReadCallbackBool4(sourceFormat);

	default:
		return &Ceng::Vshader::NullVertexReader;
	}
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat(Ceng::VTX_DATATYPE::value sourceFormat)
{
	switch (sourceFormat)
	{
	case Ceng::VTX_DATATYPE::FLOAT:
		return &Ceng::Vshader::VSIN_FLOAT_FLOAT;
	case Ceng::VTX_DATATYPE::FLOAT2:
		return &Ceng::Vshader::VSIN_FLOAT_FLOAT2;
	case Ceng::VTX_DATATYPE::FLOAT3:
		return &Ceng::Vshader::VSIN_FLOAT_FLOAT3;
	case Ceng::VTX_DATATYPE::FLOAT4:
		return &Ceng::Vshader::VSIN_FLOAT_FLOAT4;

	case Ceng::VTX_DATATYPE::DOUBLE:
		return &Ceng::Vshader::VSIN_FLOAT_DOUBLE;
	case Ceng::VTX_DATATYPE::DOUBLE2:
		return &Ceng::Vshader::VSIN_FLOAT_DOUBLE2;
	case Ceng::VTX_DATATYPE::DOUBLE3:
		return &Ceng::Vshader::VSIN_FLOAT_DOUBLE3;
	case Ceng::VTX_DATATYPE::DOUBLE4:
		return &Ceng::Vshader::VSIN_FLOAT_DOUBLE4;

	case Ceng::VTX_DATATYPE::FP16:
		return &Ceng::Vshader::VSIN_FLOAT_FP16;
	case Ceng::VTX_DATATYPE::FP16_2:
		return &Ceng::Vshader::VSIN_FLOAT_FP16_2;
	case Ceng::VTX_DATATYPE::FP16_3:
		return &Ceng::Vshader::VSIN_FLOAT_FP16_3;
	case Ceng::VTX_DATATYPE::FP16_4:
		return &Ceng::Vshader::VSIN_FLOAT_FP16_4;

	case Ceng::VTX_DATATYPE::INT:
		return &Ceng::Vshader::VSIN_FLOAT_INT;
	case Ceng::VTX_DATATYPE::INT2:
		return &Ceng::Vshader::VSIN_FLOAT_INT2;
	case Ceng::VTX_DATATYPE::INT3:
		return &Ceng::Vshader::VSIN_FLOAT_INT3;
	case Ceng::VTX_DATATYPE::INT4:
		return &Ceng::Vshader::VSIN_FLOAT_INT4;

	case Ceng::VTX_DATATYPE::UINT:
		return &Ceng::Vshader::VSIN_FLOAT_UINT;
	case Ceng::VTX_DATATYPE::UINT2:
		return &Ceng::Vshader::VSIN_FLOAT_UINT2;
	case Ceng::VTX_DATATYPE::UINT3:
		return &Ceng::Vshader::VSIN_FLOAT_UINT3;
	case Ceng::VTX_DATATYPE::UINT4:
		return &Ceng::Vshader::VSIN_FLOAT_UINT4;

	case Ceng::VTX_DATATYPE::SHORT:
		return &Ceng::Vshader::VSIN_FLOAT_SHORT;
	case Ceng::VTX_DATATYPE::SHORT2:
		return &Ceng::Vshader::VSIN_FLOAT_SHORT2;
	case Ceng::VTX_DATATYPE::SHORT3:
		return &Ceng::Vshader::VSIN_FLOAT_SHORT3;
	case Ceng::VTX_DATATYPE::SHORT4:
		return &Ceng::Vshader::VSIN_FLOAT_SHORT4;

	case Ceng::VTX_DATATYPE::NSHORT:
		return &Ceng::Vshader::VSIN_FLOAT_NSHORT;
	case Ceng::VTX_DATATYPE::NSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT_NSHORT2;
	case Ceng::VTX_DATATYPE::NSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT_NSHORT3;
	case Ceng::VTX_DATATYPE::NSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT_NSHORT4;

	case Ceng::VTX_DATATYPE::USHORT:
		return &Ceng::Vshader::VSIN_FLOAT_USHORT;
	case Ceng::VTX_DATATYPE::USHORT2:
		return &Ceng::Vshader::VSIN_FLOAT_USHORT2;
	case Ceng::VTX_DATATYPE::USHORT3:
		return &Ceng::Vshader::VSIN_FLOAT_USHORT3;
	case Ceng::VTX_DATATYPE::USHORT4:
		return &Ceng::Vshader::VSIN_FLOAT_USHORT4;

	case Ceng::VTX_DATATYPE::UNSHORT:
		return &Ceng::Vshader::VSIN_FLOAT_UNSHORT;
	case Ceng::VTX_DATATYPE::UNSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT_UNSHORT2;
	case Ceng::VTX_DATATYPE::UNSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT_UNSHORT3;
	case Ceng::VTX_DATATYPE::UNSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT_UNSHORT4;

	case Ceng::VTX_DATATYPE::BYTE:
		return &Ceng::Vshader::VSIN_FLOAT_BYTE;
	case Ceng::VTX_DATATYPE::BYTE2:
		return &Ceng::Vshader::VSIN_FLOAT_BYTE2;
	case Ceng::VTX_DATATYPE::BYTE3:
		return &Ceng::Vshader::VSIN_FLOAT_BYTE3;
	case Ceng::VTX_DATATYPE::BYTE4:
		return &Ceng::Vshader::VSIN_FLOAT_BYTE4
			;
	case Ceng::VTX_DATATYPE::UBYTE:
		return &Ceng::Vshader::VSIN_FLOAT_UBYTE;
	case Ceng::VTX_DATATYPE::UBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT_UBYTE2;
	case Ceng::VTX_DATATYPE::UBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT_UBYTE3;
	case Ceng::VTX_DATATYPE::UBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT_UBYTE4;

	case Ceng::VTX_DATATYPE::UNBYTE:
		return &Ceng::Vshader::VSIN_FLOAT_UNBYTE;
	case Ceng::VTX_DATATYPE::UNBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT_UNBYTE2;
	case Ceng::VTX_DATATYPE::UNBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT_UNBYTE3;
	case Ceng::VTX_DATATYPE::UNBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT_UNBYTE4;

	case Ceng::VTX_DATATYPE::UNORM_R5_G6_B5:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_R5_G6_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G6_R5:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_B5_G6_R5;

	case Ceng::VTX_DATATYPE::UNORM_A1_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A1_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_A1_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A1_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_A4_R4_G4_B4:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A4_R4_G4_B4;
	case Ceng::VTX_DATATYPE::UNORM_A4_B4_G4_R4:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A4_B4_G4_R4;

	case Ceng::VTX_DATATYPE::UNORM_A6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_A6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_X6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_X6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_X6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_SRGB_A8_R8_G8_B8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_SRGB_A8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_SRGB_X8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_SRGB_X8_R8_G8_B8;

	case Ceng::VTX_DATATYPE::UNORM_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A2_B10_G10_R10;
	case Ceng::VTX_DATATYPE::UINT_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT_UINT_A2_B10_G10_R10;

	case Ceng::VTX_DATATYPE::UNORM_A8:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_A8;

	case Ceng::VTX_DATATYPE::UNORM_R1:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_R1;

	case Ceng::VTX_DATATYPE::FLOAT_B10_G11_R11:
		return &Ceng::Vshader::VSIN_FLOAT_FLOAT_B10_G11_R11;

	case Ceng::VTX_DATATYPE::SHAREDEXP_E5_B9_G9_R9:
		return &Ceng::Vshader::VSIN_FLOAT_SHAREDEXP_E5_B9_G9_R9;
	default:
		return &Ceng::Vshader::NullVertexReader;
	}
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat2(Ceng::VTX_DATATYPE::value sourceFormat)
{
	switch (sourceFormat)
	{
	case Ceng::VTX_DATATYPE::FLOAT:
		return &Ceng::Vshader::VSIN_FLOAT2_FLOAT;
	case Ceng::VTX_DATATYPE::FLOAT2:
		return &Ceng::Vshader::VSIN_FLOAT2_FLOAT2;
	case Ceng::VTX_DATATYPE::FLOAT3:
		return &Ceng::Vshader::VSIN_FLOAT2_FLOAT3;
	case Ceng::VTX_DATATYPE::FLOAT4:
		return &Ceng::Vshader::VSIN_FLOAT2_FLOAT4;

	case Ceng::VTX_DATATYPE::DOUBLE:
		return &Ceng::Vshader::VSIN_FLOAT2_DOUBLE;
	case Ceng::VTX_DATATYPE::DOUBLE2:
		return &Ceng::Vshader::VSIN_FLOAT2_DOUBLE2;
	case Ceng::VTX_DATATYPE::DOUBLE3:
		return &Ceng::Vshader::VSIN_FLOAT2_DOUBLE3;
	case Ceng::VTX_DATATYPE::DOUBLE4:
		return &Ceng::Vshader::VSIN_FLOAT2_DOUBLE4;

	case Ceng::VTX_DATATYPE::FP16:
		return &Ceng::Vshader::VSIN_FLOAT2_FP16;
	case Ceng::VTX_DATATYPE::FP16_2:
		return &Ceng::Vshader::VSIN_FLOAT2_FP16_2;
	case Ceng::VTX_DATATYPE::FP16_3:
		return &Ceng::Vshader::VSIN_FLOAT2_FP16_3;
	case Ceng::VTX_DATATYPE::FP16_4:
		return &Ceng::Vshader::VSIN_FLOAT2_FP16_4;

	case Ceng::VTX_DATATYPE::INT:
		return &Ceng::Vshader::VSIN_FLOAT2_INT;
	case Ceng::VTX_DATATYPE::INT2:
		return &Ceng::Vshader::VSIN_FLOAT2_INT2;
	case Ceng::VTX_DATATYPE::INT3:
		return &Ceng::Vshader::VSIN_FLOAT2_INT3;
	case Ceng::VTX_DATATYPE::INT4:
		return &Ceng::Vshader::VSIN_FLOAT2_INT4;

	case Ceng::VTX_DATATYPE::UINT:
		return &Ceng::Vshader::VSIN_FLOAT2_UINT;
	case Ceng::VTX_DATATYPE::UINT2:
		return &Ceng::Vshader::VSIN_FLOAT2_UINT2;
	case Ceng::VTX_DATATYPE::UINT3:
		return &Ceng::Vshader::VSIN_FLOAT2_UINT3;
	case Ceng::VTX_DATATYPE::UINT4:
		return &Ceng::Vshader::VSIN_FLOAT2_UINT4;

	case Ceng::VTX_DATATYPE::SHORT:
		return &Ceng::Vshader::VSIN_FLOAT2_SHORT;
	case Ceng::VTX_DATATYPE::SHORT2:
		return &Ceng::Vshader::VSIN_FLOAT2_SHORT2;
	case Ceng::VTX_DATATYPE::SHORT3:
		return &Ceng::Vshader::VSIN_FLOAT2_SHORT3;
	case Ceng::VTX_DATATYPE::SHORT4:
		return &Ceng::Vshader::VSIN_FLOAT2_SHORT4;

	case Ceng::VTX_DATATYPE::NSHORT:
		return &Ceng::Vshader::VSIN_FLOAT2_NSHORT;
	case Ceng::VTX_DATATYPE::NSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT2_NSHORT2;
	case Ceng::VTX_DATATYPE::NSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT2_NSHORT3;
	case Ceng::VTX_DATATYPE::NSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT2_NSHORT4;

	case Ceng::VTX_DATATYPE::USHORT:
		return &Ceng::Vshader::VSIN_FLOAT2_USHORT;
	case Ceng::VTX_DATATYPE::USHORT2:
		return &Ceng::Vshader::VSIN_FLOAT2_USHORT2;
	case Ceng::VTX_DATATYPE::USHORT3:
		return &Ceng::Vshader::VSIN_FLOAT2_USHORT3;
	case Ceng::VTX_DATATYPE::USHORT4:
		return &Ceng::Vshader::VSIN_FLOAT2_USHORT4;

	case Ceng::VTX_DATATYPE::UNSHORT:
		return &Ceng::Vshader::VSIN_FLOAT2_UNSHORT;
	case Ceng::VTX_DATATYPE::UNSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT2_UNSHORT2;
	case Ceng::VTX_DATATYPE::UNSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT2_UNSHORT3;
	case Ceng::VTX_DATATYPE::UNSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT2_UNSHORT4;

	case Ceng::VTX_DATATYPE::BYTE:
		return &Ceng::Vshader::VSIN_FLOAT2_BYTE;
	case Ceng::VTX_DATATYPE::BYTE2:
		return &Ceng::Vshader::VSIN_FLOAT2_BYTE2;
	case Ceng::VTX_DATATYPE::BYTE3:
		return &Ceng::Vshader::VSIN_FLOAT2_BYTE3;
	case Ceng::VTX_DATATYPE::BYTE4:
		return &Ceng::Vshader::VSIN_FLOAT2_BYTE4
			;
	case Ceng::VTX_DATATYPE::UBYTE:
		return &Ceng::Vshader::VSIN_FLOAT2_UBYTE;
	case Ceng::VTX_DATATYPE::UBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT2_UBYTE2;
	case Ceng::VTX_DATATYPE::UBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT2_UBYTE3;
	case Ceng::VTX_DATATYPE::UBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT2_UBYTE4;

	case Ceng::VTX_DATATYPE::UNBYTE:
		return &Ceng::Vshader::VSIN_FLOAT2_UNBYTE;
	case Ceng::VTX_DATATYPE::UNBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT2_UNBYTE2;
	case Ceng::VTX_DATATYPE::UNBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT2_UNBYTE3;
	case Ceng::VTX_DATATYPE::UNBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT2_UNBYTE4;

	case Ceng::VTX_DATATYPE::UNORM_R5_G6_B5:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_R5_G6_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G6_R5:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_B5_G6_R5;

	case Ceng::VTX_DATATYPE::UNORM_A1_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A1_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_A1_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A1_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_A4_R4_G4_B4:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A4_R4_G4_B4;
	case Ceng::VTX_DATATYPE::UNORM_A4_B4_G4_R4:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A4_B4_G4_R4;

	case Ceng::VTX_DATATYPE::UNORM_A6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_A6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_X6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_X6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_X6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_SRGB_A8_R8_G8_B8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_SRGB_A8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_SRGB_X8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_SRGB_X8_R8_G8_B8;

	case Ceng::VTX_DATATYPE::UNORM_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A2_B10_G10_R10;
	case Ceng::VTX_DATATYPE::UINT_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT2_UINT_A2_B10_G10_R10;

	case Ceng::VTX_DATATYPE::UNORM_A8:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_A8;

	case Ceng::VTX_DATATYPE::UNORM_R1:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_R1;

	case Ceng::VTX_DATATYPE::FLOAT_B10_G11_R11:
		return &Ceng::Vshader::VSIN_FLOAT2_FLOAT_B10_G11_R11;

	case Ceng::VTX_DATATYPE::SHAREDEXP_E5_B9_G9_R9:
		return &Ceng::Vshader::VSIN_FLOAT2_SHAREDEXP_E5_B9_G9_R9;

	default:
		return &Ceng::Vshader::NullVertexReader;
	}
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat3(Ceng::VTX_DATATYPE::value sourceFormat)
{
	switch (sourceFormat)
	{
	case Ceng::VTX_DATATYPE::FLOAT:
		return &Ceng::Vshader::VSIN_FLOAT3_FLOAT;
	case Ceng::VTX_DATATYPE::FLOAT2:
		return &Ceng::Vshader::VSIN_FLOAT3_FLOAT2;
	case Ceng::VTX_DATATYPE::FLOAT3:
		return &Ceng::Vshader::VSIN_FLOAT3_FLOAT3;
	case Ceng::VTX_DATATYPE::FLOAT4:
		return &Ceng::Vshader::VSIN_FLOAT3_FLOAT4;

	case Ceng::VTX_DATATYPE::DOUBLE:
		return &Ceng::Vshader::VSIN_FLOAT3_DOUBLE;
	case Ceng::VTX_DATATYPE::DOUBLE2:
		return &Ceng::Vshader::VSIN_FLOAT3_DOUBLE2;
	case Ceng::VTX_DATATYPE::DOUBLE3:
		return &Ceng::Vshader::VSIN_FLOAT3_DOUBLE3;
	case Ceng::VTX_DATATYPE::DOUBLE4:
		return &Ceng::Vshader::VSIN_FLOAT3_DOUBLE4;

	case Ceng::VTX_DATATYPE::FP16:
		return &Ceng::Vshader::VSIN_FLOAT3_FP16;
	case Ceng::VTX_DATATYPE::FP16_2:
		return &Ceng::Vshader::VSIN_FLOAT3_FP16_2;
	case Ceng::VTX_DATATYPE::FP16_3:
		return &Ceng::Vshader::VSIN_FLOAT3_FP16_3;
	case Ceng::VTX_DATATYPE::FP16_4:
		return &Ceng::Vshader::VSIN_FLOAT3_FP16_4;

	case Ceng::VTX_DATATYPE::INT:
		return &Ceng::Vshader::VSIN_FLOAT3_INT;
	case Ceng::VTX_DATATYPE::INT2:
		return &Ceng::Vshader::VSIN_FLOAT3_INT2;
	case Ceng::VTX_DATATYPE::INT3:
		return &Ceng::Vshader::VSIN_FLOAT3_INT3;
	case Ceng::VTX_DATATYPE::INT4:
		return &Ceng::Vshader::VSIN_FLOAT3_INT4;

	case Ceng::VTX_DATATYPE::UINT:
		return &Ceng::Vshader::VSIN_FLOAT3_UINT;
	case Ceng::VTX_DATATYPE::UINT2:
		return &Ceng::Vshader::VSIN_FLOAT3_UINT2;
	case Ceng::VTX_DATATYPE::UINT3:
		return &Ceng::Vshader::VSIN_FLOAT3_UINT3;
	case Ceng::VTX_DATATYPE::UINT4:
		return &Ceng::Vshader::VSIN_FLOAT3_UINT4;

	case Ceng::VTX_DATATYPE::SHORT:
		return &Ceng::Vshader::VSIN_FLOAT3_SHORT;
	case Ceng::VTX_DATATYPE::SHORT2:
		return &Ceng::Vshader::VSIN_FLOAT3_SHORT2;
	case Ceng::VTX_DATATYPE::SHORT3:
		return &Ceng::Vshader::VSIN_FLOAT3_SHORT3;
	case Ceng::VTX_DATATYPE::SHORT4:
		return &Ceng::Vshader::VSIN_FLOAT3_SHORT4;

	case Ceng::VTX_DATATYPE::NSHORT:
		return &Ceng::Vshader::VSIN_FLOAT3_NSHORT;
	case Ceng::VTX_DATATYPE::NSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT3_NSHORT2;
	case Ceng::VTX_DATATYPE::NSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT3_NSHORT3;
	case Ceng::VTX_DATATYPE::NSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT3_NSHORT4;

	case Ceng::VTX_DATATYPE::USHORT:
		return &Ceng::Vshader::VSIN_FLOAT3_USHORT;
	case Ceng::VTX_DATATYPE::USHORT2:
		return &Ceng::Vshader::VSIN_FLOAT3_USHORT2;
	case Ceng::VTX_DATATYPE::USHORT3:
		return &Ceng::Vshader::VSIN_FLOAT3_USHORT3;
	case Ceng::VTX_DATATYPE::USHORT4:
		return &Ceng::Vshader::VSIN_FLOAT3_USHORT4;

	case Ceng::VTX_DATATYPE::UNSHORT:
		return &Ceng::Vshader::VSIN_FLOAT3_UNSHORT;
	case Ceng::VTX_DATATYPE::UNSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT3_UNSHORT2;
	case Ceng::VTX_DATATYPE::UNSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT3_UNSHORT3;
	case Ceng::VTX_DATATYPE::UNSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT3_UNSHORT4;

	case Ceng::VTX_DATATYPE::BYTE:
		return &Ceng::Vshader::VSIN_FLOAT3_BYTE;
	case Ceng::VTX_DATATYPE::BYTE2:
		return &Ceng::Vshader::VSIN_FLOAT3_BYTE2;
	case Ceng::VTX_DATATYPE::BYTE3:
		return &Ceng::Vshader::VSIN_FLOAT3_BYTE3;
	case Ceng::VTX_DATATYPE::BYTE4:
		return &Ceng::Vshader::VSIN_FLOAT3_BYTE4
			;
	case Ceng::VTX_DATATYPE::UBYTE:
		return &Ceng::Vshader::VSIN_FLOAT3_UBYTE;
	case Ceng::VTX_DATATYPE::UBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT3_UBYTE2;
	case Ceng::VTX_DATATYPE::UBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT3_UBYTE3;
	case Ceng::VTX_DATATYPE::UBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT3_UBYTE4;

	case Ceng::VTX_DATATYPE::UNBYTE:
		return &Ceng::Vshader::VSIN_FLOAT3_UNBYTE;
	case Ceng::VTX_DATATYPE::UNBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT3_UNBYTE2;
	case Ceng::VTX_DATATYPE::UNBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT3_UNBYTE3;
	case Ceng::VTX_DATATYPE::UNBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT3_UNBYTE4;

	case Ceng::VTX_DATATYPE::UNORM_R5_G6_B5:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_R5_G6_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G6_R5:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_B5_G6_R5;

	case Ceng::VTX_DATATYPE::UNORM_A1_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A1_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_A1_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A1_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_A4_R4_G4_B4:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A4_R4_G4_B4;
	case Ceng::VTX_DATATYPE::UNORM_A4_B4_G4_R4:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A4_B4_G4_R4;

	case Ceng::VTX_DATATYPE::UNORM_A6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_A6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_X6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_X6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_X6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_SRGB_A8_R8_G8_B8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_SRGB_A8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_SRGB_X8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_SRGB_X8_R8_G8_B8;

	case Ceng::VTX_DATATYPE::UNORM_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A2_B10_G10_R10;
	case Ceng::VTX_DATATYPE::UINT_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT3_UINT_A2_B10_G10_R10;

	case Ceng::VTX_DATATYPE::UNORM_A8:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_A8;

	case Ceng::VTX_DATATYPE::UNORM_R1:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_R1;

	case Ceng::VTX_DATATYPE::FLOAT_B10_G11_R11:
		return &Ceng::Vshader::VSIN_FLOAT3_FLOAT_B10_G11_R11;

	case Ceng::VTX_DATATYPE::SHAREDEXP_E5_B9_G9_R9:
		return &Ceng::Vshader::VSIN_FLOAT3_SHAREDEXP_E5_B9_G9_R9;

	default:
		return &Ceng::Vshader::NullVertexReader;
	}
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackFloat4(Ceng::VTX_DATATYPE::value sourceFormat)
{
	switch (sourceFormat)
	{
	case Ceng::VTX_DATATYPE::FLOAT:
		return &Ceng::Vshader::VSIN_FLOAT4_FLOAT;
	case Ceng::VTX_DATATYPE::FLOAT2:
		return &Ceng::Vshader::VSIN_FLOAT4_FLOAT2;
	case Ceng::VTX_DATATYPE::FLOAT3:
		return &Ceng::Vshader::VSIN_FLOAT4_FLOAT3;
	case Ceng::VTX_DATATYPE::FLOAT4:
		return &Ceng::Vshader::VSIN_FLOAT4_FLOAT4;

	case Ceng::VTX_DATATYPE::DOUBLE:
		return &Ceng::Vshader::VSIN_FLOAT4_DOUBLE;
	case Ceng::VTX_DATATYPE::DOUBLE2:
		return &Ceng::Vshader::VSIN_FLOAT4_DOUBLE2;
	case Ceng::VTX_DATATYPE::DOUBLE3:
		return &Ceng::Vshader::VSIN_FLOAT4_DOUBLE3;
	case Ceng::VTX_DATATYPE::DOUBLE4:
		return &Ceng::Vshader::VSIN_FLOAT4_DOUBLE4;

	case Ceng::VTX_DATATYPE::FP16:
		return &Ceng::Vshader::VSIN_FLOAT4_FP16;
	case Ceng::VTX_DATATYPE::FP16_2:
		return &Ceng::Vshader::VSIN_FLOAT4_FP16_2;
	case Ceng::VTX_DATATYPE::FP16_3:
		return &Ceng::Vshader::VSIN_FLOAT4_FP16_3;
	case Ceng::VTX_DATATYPE::FP16_4:
		return &Ceng::Vshader::VSIN_FLOAT4_FP16_4;

	case Ceng::VTX_DATATYPE::INT:
		return &Ceng::Vshader::VSIN_FLOAT4_INT;
	case Ceng::VTX_DATATYPE::INT2:
		return &Ceng::Vshader::VSIN_FLOAT4_INT2;
	case Ceng::VTX_DATATYPE::INT3:
		return &Ceng::Vshader::VSIN_FLOAT4_INT3;
	case Ceng::VTX_DATATYPE::INT4:
		return &Ceng::Vshader::VSIN_FLOAT4_INT4;

	case Ceng::VTX_DATATYPE::UINT:
		return &Ceng::Vshader::VSIN_FLOAT4_UINT;
	case Ceng::VTX_DATATYPE::UINT2:
		return &Ceng::Vshader::VSIN_FLOAT4_UINT2;
	case Ceng::VTX_DATATYPE::UINT3:
		return &Ceng::Vshader::VSIN_FLOAT4_UINT3;
	case Ceng::VTX_DATATYPE::UINT4:
		return &Ceng::Vshader::VSIN_FLOAT4_UINT4;

	case Ceng::VTX_DATATYPE::SHORT:
		return &Ceng::Vshader::VSIN_FLOAT4_SHORT;
	case Ceng::VTX_DATATYPE::SHORT2:
		return &Ceng::Vshader::VSIN_FLOAT4_SHORT2;
	case Ceng::VTX_DATATYPE::SHORT3:
		return &Ceng::Vshader::VSIN_FLOAT4_SHORT3;
	case Ceng::VTX_DATATYPE::SHORT4:
		return &Ceng::Vshader::VSIN_FLOAT4_SHORT4;

	case Ceng::VTX_DATATYPE::NSHORT:
		return &Ceng::Vshader::VSIN_FLOAT4_NSHORT;
	case Ceng::VTX_DATATYPE::NSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT4_NSHORT2;
	case Ceng::VTX_DATATYPE::NSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT4_NSHORT3;
	case Ceng::VTX_DATATYPE::NSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT4_NSHORT4;

	case Ceng::VTX_DATATYPE::USHORT:
		return &Ceng::Vshader::VSIN_FLOAT4_USHORT;
	case Ceng::VTX_DATATYPE::USHORT2:
		return &Ceng::Vshader::VSIN_FLOAT4_USHORT2;
	case Ceng::VTX_DATATYPE::USHORT3:
		return &Ceng::Vshader::VSIN_FLOAT4_USHORT3;
	case Ceng::VTX_DATATYPE::USHORT4:
		return &Ceng::Vshader::VSIN_FLOAT4_USHORT4;

	case Ceng::VTX_DATATYPE::UNSHORT:
		return &Ceng::Vshader::VSIN_FLOAT4_UNSHORT;
	case Ceng::VTX_DATATYPE::UNSHORT2:
		return &Ceng::Vshader::VSIN_FLOAT4_UNSHORT2;
	case Ceng::VTX_DATATYPE::UNSHORT3:
		return &Ceng::Vshader::VSIN_FLOAT4_UNSHORT3;
	case Ceng::VTX_DATATYPE::UNSHORT4:
		return &Ceng::Vshader::VSIN_FLOAT4_UNSHORT4;

	case Ceng::VTX_DATATYPE::BYTE:
		return &Ceng::Vshader::VSIN_FLOAT4_BYTE;
	case Ceng::VTX_DATATYPE::BYTE2:
		return &Ceng::Vshader::VSIN_FLOAT4_BYTE2;
	case Ceng::VTX_DATATYPE::BYTE3:
		return &Ceng::Vshader::VSIN_FLOAT4_BYTE3;
	case Ceng::VTX_DATATYPE::BYTE4:
		return &Ceng::Vshader::VSIN_FLOAT4_BYTE4
			;
	case Ceng::VTX_DATATYPE::UBYTE:
		return &Ceng::Vshader::VSIN_FLOAT4_UBYTE;
	case Ceng::VTX_DATATYPE::UBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT4_UBYTE2;
	case Ceng::VTX_DATATYPE::UBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT4_UBYTE3;
	case Ceng::VTX_DATATYPE::UBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT4_UBYTE4;

	case Ceng::VTX_DATATYPE::UNBYTE:
		return &Ceng::Vshader::VSIN_FLOAT4_UNBYTE;
	case Ceng::VTX_DATATYPE::UNBYTE2:
		return &Ceng::Vshader::VSIN_FLOAT4_UNBYTE2;
	case Ceng::VTX_DATATYPE::UNBYTE3:
		return &Ceng::Vshader::VSIN_FLOAT4_UNBYTE3;
	case Ceng::VTX_DATATYPE::UNBYTE4:
		return &Ceng::Vshader::VSIN_FLOAT4_UNBYTE4;

	case Ceng::VTX_DATATYPE::UNORM_R5_G6_B5:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_R5_G6_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G6_R5:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_B5_G6_R5;

	case Ceng::VTX_DATATYPE::UNORM_A1_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A1_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_A1_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A1_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_R5_G5_B5:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_R5_G5_B5;
	case Ceng::VTX_DATATYPE::UNORM_B5_G5_R5:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_B5_G5_R5;

	case Ceng::VTX_DATATYPE::UNORM_A4_R4_G4_B4:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A4_R4_G4_B4;
	case Ceng::VTX_DATATYPE::UNORM_A4_B4_G4_R4:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A4_B4_G4_R4;

	case Ceng::VTX_DATATYPE::UNORM_A6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_A6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_X6_R6_G6_B6:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_X6_R6_G6_B6;
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R6:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_X6_B6_G6_R6;

	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_SRGB_A8_R8_G8_B8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_A8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_SRGB_A8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_SRGB_X8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_SRGB_X8_R8_G8_B8:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_SRGB_X8_R8_G8_B8;

	case Ceng::VTX_DATATYPE::UNORM_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A2_B10_G10_R10;
	case Ceng::VTX_DATATYPE::UINT_A2_B10_G10_R10:
		return &Ceng::Vshader::VSIN_FLOAT4_UINT_A2_B10_G10_R10;

	case Ceng::VTX_DATATYPE::UNORM_A8:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_A8;

	case Ceng::VTX_DATATYPE::UNORM_R1:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_R1;

	case Ceng::VTX_DATATYPE::FLOAT_B10_G11_R11:
		return &Ceng::Vshader::VSIN_FLOAT4_FLOAT_B10_G11_R11;

	case Ceng::VTX_DATATYPE::SHAREDEXP_E5_B9_G9_R9:
		return &Ceng::Vshader::VSIN_FLOAT4_SHAREDEXP_E5_B9_G9_R9;

	default:
		return &Ceng::Vshader::NullVertexReader;
	}
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble2(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble3(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackDouble4(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt2(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt3(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackInt4(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt2(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt3(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackUInt4(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool2(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool3(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

Ceng::Vshader::VertexShaderInputReader GetReadCallbackBool4(Ceng::VTX_DATATYPE::value sourceFormat)
{
	return &Ceng::Vshader::NullVertexReader;
}

namespace Ceng::Vshader
{
	/*
	void VSIN_FLOAT_FLOAT_X86(void *dest,void *source)
	{
		Ceng::UINT32 *destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32 *sourcePtr = (Ceng::UINT32*)source;

		*destPtr = *sourcePtr;
	}

	void VSIN_FLOAT2_FLOAT2_X86_SSE2(void *dest,void *source)
	{
		__m128d temp = _mm_load_sd((double*)source);

		_mm_store_sd((double*)dest,temp);
	}

	void VSIN_FLOAT3_FLOAT3_X86(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
		destPtr[2] = sourcePtr[2];
	}

	void VSIN_FLOAT4_FLOAT4_X86_SSE(void *dest,void *source)
	{
		__m128 temp = _mm_load_ps((float*)source);

		_mm_store_ps((float*)dest, temp);
	}
	*/

	//*************************************************
	// From FLOAT

	void VSIN_FLOAT_FLOAT(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = *sourcePtr;
	}

	void VSIN_FLOAT2_FLOAT(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = *sourcePtr;
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_FLOAT(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = *sourcePtr;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_FLOAT(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = *sourcePtr;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From FLOAT2

	void VSIN_FLOAT_FLOAT2(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = *sourcePtr;
	}

	void VSIN_FLOAT2_FLOAT2(void* dest, void* source)
	{
		__m128d temp = _mm_load_sd((double*)source);

		_mm_store_sd((double*)dest, temp);
	}

	void VSIN_FLOAT3_FLOAT2(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_FLOAT2(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From FLOAT3

	void VSIN_FLOAT_FLOAT3(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = *sourcePtr;
	}

	void VSIN_FLOAT2_FLOAT3(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
	}

	void VSIN_FLOAT3_FLOAT3(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
		destPtr[2] = sourcePtr[2];
	}

	void VSIN_FLOAT4_FLOAT3(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
		destPtr[2] = sourcePtr[2];
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From FLOAT4

	void VSIN_FLOAT_FLOAT4(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = *sourcePtr;
	}

	void VSIN_FLOAT2_FLOAT4(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
	}

	void VSIN_FLOAT3_FLOAT4(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
		destPtr[2] = sourcePtr[2];
	}

	void VSIN_FLOAT4_FLOAT4(void* dest, void* source)
	{
		__m128 temp = _mm_load_ps((float*)source);

		_mm_store_ps((float*)dest, temp);
	}

	//*************************************************
	// From DOUBLE

	void VSIN_FLOAT_DOUBLE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		*destPtr = (Ceng::FLOAT32)*sourcePtr;
	}

	void VSIN_FLOAT2_DOUBLE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)*sourcePtr;
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_DOUBLE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)*sourcePtr;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_DOUBLE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)*sourcePtr;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From DOUBLE2

	void VSIN_FLOAT_DOUBLE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		*destPtr = (Ceng::FLOAT32)*sourcePtr;
	}

	void VSIN_FLOAT2_DOUBLE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
	}

	void VSIN_FLOAT3_DOUBLE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_DOUBLE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From DOUBLE3

	void VSIN_FLOAT_DOUBLE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		*destPtr = (Ceng::FLOAT32)*sourcePtr;
	}

	void VSIN_FLOAT2_DOUBLE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
	}

	void VSIN_FLOAT3_DOUBLE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
		destPtr[2] = (Ceng::FLOAT32)sourcePtr[2];
	}

	void VSIN_FLOAT4_DOUBLE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
		destPtr[2] = (Ceng::FLOAT32)sourcePtr[2];
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From DOUBLE4

	void VSIN_FLOAT_DOUBLE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		*destPtr = (Ceng::FLOAT32)*sourcePtr;
	}

	void VSIN_FLOAT2_DOUBLE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
	}

	void VSIN_FLOAT3_DOUBLE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
		destPtr[2] = (Ceng::FLOAT32)sourcePtr[2];
	}

	void VSIN_FLOAT4_DOUBLE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT64* sourcePtr = (Ceng::FLOAT64*)source;

		destPtr[0] = (Ceng::FLOAT32)sourcePtr[0];
		destPtr[1] = (Ceng::FLOAT32)sourcePtr[1];
		destPtr[2] = (Ceng::FLOAT32)sourcePtr[2];
		destPtr[3] = (Ceng::FLOAT32)sourcePtr[3];
	}

	//*************************************************
	// From FP16

	void VSIN_FLOAT_FP16(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = HalfToFloat(*sourcePtr);
	}

	void VSIN_FLOAT2_FP16(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_FP16(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_FP16(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From FP16_2

	void VSIN_FLOAT_FP16_2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = HalfToFloat(*sourcePtr);
	}

	void VSIN_FLOAT2_FP16_2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
	}

	void VSIN_FLOAT3_FP16_2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_FP16_2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From FP16_3

	void VSIN_FLOAT_FP16_3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = HalfToFloat(*sourcePtr);
	}

	void VSIN_FLOAT2_FP16_3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
	}

	void VSIN_FLOAT3_FP16_3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
		destPtr[2] = HalfToFloat(sourcePtr[2]);
	}

	void VSIN_FLOAT4_FP16_3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
		destPtr[2] = HalfToFloat(sourcePtr[2]);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From FP16_4

	void VSIN_FLOAT_FP16_4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = HalfToFloat(*sourcePtr);
	}

	void VSIN_FLOAT2_FP16_4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
	}

	void VSIN_FLOAT3_FP16_4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
		destPtr[2] = HalfToFloat(sourcePtr[2]);
	}

	void VSIN_FLOAT4_FP16_4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = HalfToFloat(sourcePtr[0]);
		destPtr[1] = HalfToFloat(sourcePtr[1]);
		destPtr[2] = HalfToFloat(sourcePtr[2]);
		destPtr[3] = HalfToFloat(sourcePtr[3]);
	}

	//*************************************************
	// From INT

	void VSIN_FLOAT_INT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_INT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_INT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_INT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From INT2

	void VSIN_FLOAT_INT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_INT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_INT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_INT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From INT3

	void VSIN_FLOAT_INT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_INT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_INT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_INT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From INT4

	void VSIN_FLOAT_INT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_INT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_INT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_INT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT32* sourcePtr = (Ceng::INT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]);
	}

	//*************************************************
	// From UINT

	void VSIN_FLOAT_UINT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UINT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_UINT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UINT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UINT2

	void VSIN_FLOAT_UINT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UINT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_UINT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UINT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UINT3

	void VSIN_FLOAT_UINT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UINT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_UINT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_UINT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UINT4

	void VSIN_FLOAT_UINT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UINT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_UINT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_UINT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]);
	}

	//*************************************************
	// From SHORT

	void VSIN_FLOAT_SHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_SHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_SHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_SHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From SHORT2

	void VSIN_FLOAT_SHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_SHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_SHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_SHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From SHORT3

	void VSIN_FLOAT_SHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_SHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_SHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_SHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From SHORT4

	void VSIN_FLOAT_SHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_SHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_SHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_SHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]);
	}

	//*************************************************
	// From USHORT

	void VSIN_FLOAT_USHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_USHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_USHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_USHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From USHORT2

	void VSIN_FLOAT_USHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_USHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_USHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_USHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From USHORT3

	void VSIN_FLOAT_USHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_USHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_USHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_USHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From USHORT4

	void VSIN_FLOAT_USHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_USHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_USHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_USHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]);
	}

	//*************************************************
	// From UNSHORT

	void VSIN_FLOAT_UNSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT2_UNSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_UNSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UNSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNSHORT2

	void VSIN_FLOAT_UNSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT2_UNSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT3_UNSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UNSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNSHORT3

	void VSIN_FLOAT_UNSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT2_UNSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT3_UNSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT4_UNSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint16;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNSHORT4

	void VSIN_FLOAT_UNSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT2_UNSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT3_UNSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint16;
	}

	void VSIN_FLOAT4_UNSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint16;
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]) * scaleNormalizeUint16;
	}

	//*************************************************
	// From NSHORT

	void VSIN_FLOAT_NSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT2_NSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_NSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_NSHORT(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From NSHORT2

	void VSIN_FLOAT_NSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT2_NSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT3_NSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_NSHORT2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From NSHORT3

	void VSIN_FLOAT_NSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT2_NSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT3_NSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT4_NSHORT3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeInt16;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From NSHORT4

	void VSIN_FLOAT_NSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT2_NSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT3_NSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeInt16;
	}

	void VSIN_FLOAT4_NSHORT4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT16* sourcePtr = (Ceng::INT16*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeInt16;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeInt16;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeInt16;
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]) * scaleNormalizeInt16;
	}

	//*************************************************
	// From BYTE

	void VSIN_FLOAT_BYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_BYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_BYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_BYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From BYTE2

	void VSIN_FLOAT_BYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_BYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_BYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_BYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From BYTE3

	void VSIN_FLOAT_BYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_BYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_BYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_BYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From BYTE4

	void VSIN_FLOAT_BYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_BYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_BYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_BYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::INT8* sourcePtr = (Ceng::INT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]);
	}

	//*************************************************
	// From UBYTE

	void VSIN_FLOAT_UBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_UBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UBYTE2

	void VSIN_FLOAT_UBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_UBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UBYTE3

	void VSIN_FLOAT_UBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_UBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_UBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UBYTE4

	void VSIN_FLOAT_UBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr);
	}

	void VSIN_FLOAT2_UBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
	}

	void VSIN_FLOAT3_UBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
	}

	void VSIN_FLOAT4_UBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]);
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]);
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]);
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]);
	}

	//*************************************************
	// From UNBYTE

	void VSIN_FLOAT_UNBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT2_UNBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_UNBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UNBYTE(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNBYTE2

	void VSIN_FLOAT_UNBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT2_UNBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT3_UNBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UNBYTE2(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNBYTE3

	void VSIN_FLOAT_UNBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT2_UNBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT3_UNBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT4_UNBYTE3(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint8;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNBYTE4

	void VSIN_FLOAT_UNBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		*destPtr = Ceng::FLOAT32(*sourcePtr) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT2_UNBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT3_UNBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint8;
	}

	void VSIN_FLOAT4_UNBYTE4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT8* sourcePtr = (Ceng::UINT8*)source;

		destPtr[0] = Ceng::FLOAT32(sourcePtr[0]) * scaleNormalizeUint8;
		destPtr[1] = Ceng::FLOAT32(sourcePtr[1]) * scaleNormalizeUint8;
		destPtr[2] = Ceng::FLOAT32(sourcePtr[2]) * scaleNormalizeUint8;
		destPtr[3] = Ceng::FLOAT32(sourcePtr[3]) * scaleNormalizeUint8;
	}

	//*************************************************
	// From UNORM_B5_G6_R5

	void VSIN_FLOAT_UNORM_B5_G6_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G6_R5(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT2_UNORM_B5_G6_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G6_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_B5_G6_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G6_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT4_UNORM_B5_G6_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G6_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNORM_R5_G6_B5

	void VSIN_FLOAT_UNORM_R5_G6_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G6_B5(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT2_UNORM_R5_G6_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G6_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_R5_G6_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G6_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT4_UNORM_R5_G6_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G6_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNORM_A1_R5_G5_B5

	void VSIN_FLOAT_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_R5_G5_B5(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT2_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_R5_G5_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_R5_G5_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT4_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_R5_G5_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[3] = Ceng::FLOAT32(color.a);
	}

	//*************************************************
	// From UNORM_A1_B5_G5_R5

	void VSIN_FLOAT_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_B5_G5_R5(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT2_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_B5_G5_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_B5_G5_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT4_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A1_B5_G5_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[3] = Ceng::FLOAT32(color.a);
	}

	//*************************************************
	// From UNORM_R5_G5_B5

	void VSIN_FLOAT_UNORM_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G5_B5(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT2_UNORM_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G5_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G5_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT4_UNORM_R5_G5_B5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_R5_G5_B5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[4] = 1.0f;
	}

	//*************************************************
	// From UNORM_B5_G5_R5

	void VSIN_FLOAT_UNORM_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G5_R5(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT2_UNORM_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G5_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G5_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
	}

	void VSIN_FLOAT4_UNORM_B5_G5_R5(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color3_Int32 color = Extract_B5_G5_R5(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx5;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx5;
		destPtr[4] = 1.0f;
	}

	//*************************************************
	// From UNORM_A4_R4_G4_B4

	void VSIN_FLOAT_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_R4_G4_B4(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx4;
	}

	void VSIN_FLOAT2_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_R4_G4_B4(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx4;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx4;
	}

	void VSIN_FLOAT3_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_R4_G4_B4(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx4;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx4;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx4;
	}

	void VSIN_FLOAT4_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_R4_G4_B4(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx4;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx4;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx4;
		destPtr[3] = Ceng::FLOAT32(color.a) * scaleNormalizeUNfx4;
	}

	//*************************************************
	// From UNORM_A4_B4_G4_R4

	void VSIN_FLOAT_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_B4_G4_R4(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx4;
	}

	void VSIN_FLOAT2_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_B4_G4_R4(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx4;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx4;
	}

	void VSIN_FLOAT3_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_B4_G4_R4(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx4;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx4;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx4;
	}

	void VSIN_FLOAT4_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT16* sourcePtr = (Ceng::UINT16*)source;

		Color4_Int32 color = Extract_A4_B4_G4_R4(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx4;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx4;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx4;
		destPtr[3] = Ceng::FLOAT32(color.a) * scaleNormalizeUNfx4;
	}

	//*************************************************
	// From UNORM_A6_R6_G6_B6

	void VSIN_FLOAT_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_R6_G6_B6(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT2_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_R6_G6_B6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_R6_G6_B6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT4_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_R6_G6_B6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[3] = Ceng::FLOAT32(color.a) * scaleNormalizeUNfx6;
	}

	//*************************************************
	// From UNORM_A6_B6_G6_R6

	void VSIN_FLOAT_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_B6_G6_R6(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT2_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_B6_G6_R6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_B6_G6_R6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT4_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A6_B6_G6_R6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[3] = Ceng::FLOAT32(color.a) * scaleNormalizeUNfx6;
	}

	//*************************************************
	// From UNORM_X6_R6_G6_B6

	void VSIN_FLOAT_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_R6_G6_B6(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT2_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_R6_G6_B6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_R6_G6_B6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT4_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_R6_G6_B6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNORM_X6_B6_G6_R6

	void VSIN_FLOAT_UNORM_X6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_B6_G6_R6(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT2_UNORM_X6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_B6_G6_R6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT3_UNORM_X6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_B6_G6_R6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
	}

	void VSIN_FLOAT4_UNORM_X6_B6_G6_R6(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X6_B6_G6_R6(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx6;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx6;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx6;
		destPtr[3] = 1.0f;
	}
	//*************************************************
	// From UNORM_SRGB_A8_R8_G8_B8

	void VSIN_FLOAT_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_R8_G8_B8(*sourcePtr);

		*destPtr = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT2_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_R8_G8_B8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT3_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_R8_G8_B8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT4_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_R8_G8_B8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[3] = SrgbToLinear(Ceng::FLOAT32(color.a) * scaleNormalizeUint8);
	}

	//*************************************************
	// From UNORM_SRGB_A8_B8_G8_R8

	void VSIN_FLOAT_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_B8_G8_R8(*sourcePtr);

		*destPtr = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT2_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_B8_G8_R8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT3_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_B8_G8_R8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT4_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A8_B8_G8_R8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[3] = SrgbToLinear(Ceng::FLOAT32(color.a) * scaleNormalizeUint8);
	}
	//*************************************************
	// From UNORM_SRGB_X8_B8_G8_R8

	void VSIN_FLOAT_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_B8_G8_R8(*sourcePtr);

		*destPtr = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT2_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_B8_G8_R8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT3_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_B8_G8_R8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT4_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_B8_G8_R8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNORM_SRGB_X8_R8_G8_B8

	void VSIN_FLOAT_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_R8_G8_B8(*sourcePtr);

		*destPtr = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT2_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_R8_G8_B8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT3_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_R8_G8_B8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
	}

	void VSIN_FLOAT4_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Int32 color = Extract_X8_R8_G8_B8(*sourcePtr);

		destPtr[0] = SrgbToLinear(Ceng::FLOAT32(color.b) * scaleNormalizeUint8);
		destPtr[1] = SrgbToLinear(Ceng::FLOAT32(color.g) * scaleNormalizeUint8);
		destPtr[2] = SrgbToLinear(Ceng::FLOAT32(color.r) * scaleNormalizeUint8);
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From UNORM_A2_B10_G10_R10

	void VSIN_FLOAT_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx10;
	}

	void VSIN_FLOAT2_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx10;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx10;
	}

	void VSIN_FLOAT3_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx10;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx10;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx10;
	}

	void VSIN_FLOAT4_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r) * scaleNormalizeUNfx10;
		destPtr[1] = Ceng::FLOAT32(color.g) * scaleNormalizeUNfx10;
		destPtr[2] = Ceng::FLOAT32(color.b) * scaleNormalizeUNfx10;
		destPtr[3] = Ceng::FLOAT32(color.a) * scaleNormalizeUNfx2;
	}

	//*************************************************
	// From UINT_A2_B10_G10_R10

	void VSIN_FLOAT_UINT_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		*destPtr = Ceng::FLOAT32(color.r);
	}

	void VSIN_FLOAT2_UINT_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r);
		destPtr[1] = Ceng::FLOAT32(color.g);
	}

	void VSIN_FLOAT3_UINT_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r);
		destPtr[1] = Ceng::FLOAT32(color.g);
		destPtr[2] = Ceng::FLOAT32(color.b);
	}

	void VSIN_FLOAT4_UINT_A2_B10_G10_R10(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color4_Int32 color = Extract_A2_B10_G10_R10(*sourcePtr);

		destPtr[0] = Ceng::FLOAT32(color.r);
		destPtr[1] = Ceng::FLOAT32(color.g);
		destPtr[2] = Ceng::FLOAT32(color.b);
		destPtr[3] = Ceng::FLOAT32(color.a);
	}

	//*************************************************
	// From UNORM_A8

	void VSIN_FLOAT_UNORM_A8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;

		destPtr[0] = 0.0f;
	}

	void VSIN_FLOAT2_UNORM_A8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;

		destPtr[0] = 0.0f;
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_UNORM_A8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;

		destPtr[0] = 0.0f;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UNORM_A8(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::FLOAT32* sourcePtr = (Ceng::FLOAT32*)source;

		destPtr[0] = 0.0f;
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = sourcePtr[0];
	}

	//*************************************************
	// From UNORM_R1

	void VSIN_FLOAT_UNORM_R1(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = ceilf(Ceng::FLOAT32(*sourcePtr));
	}

	void VSIN_FLOAT2_UNORM_R1(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = ceilf(Ceng::FLOAT32(*sourcePtr));
		destPtr[1] = 0.0f;
	}

	void VSIN_FLOAT3_UNORM_R1(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = ceilf(Ceng::FLOAT32(*sourcePtr));
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
	}

	void VSIN_FLOAT4_UNORM_R1(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = ceilf(Ceng::FLOAT32(*sourcePtr));
		destPtr[1] = 0.0f;
		destPtr[2] = 0.0f;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From FLOAT_B10_G11_R11

	void VSIN_FLOAT_FLOAT_B10_G11_R11(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = Fp10_11_10_ToFloat(*sourcePtr);

		*destPtr = temp.r;
	}

	void VSIN_FLOAT2_FLOAT_B10_G11_R11(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = Fp10_11_10_ToFloat(*sourcePtr);

		destPtr[0] = temp.r;
		destPtr[1] = temp.g;
	}

	void VSIN_FLOAT3_FLOAT_B10_G11_R11(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = Fp10_11_10_ToFloat(*sourcePtr);

		destPtr[0] = temp.r;
		destPtr[1] = temp.g;
		destPtr[2] = temp.b;
	}

	void VSIN_FLOAT4_FLOAT_B10_G11_R11(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = Fp10_11_10_ToFloat(*sourcePtr);

		destPtr[0] = temp.r;
		destPtr[1] = temp.g;
		destPtr[2] = temp.b;
		destPtr[3] = 1.0f;
	}

	//*************************************************
	// From SHAREDEXP_E5_B9_G9_R9

	void VSIN_FLOAT_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = SharedExpToFloat(*sourcePtr);

		*destPtr = temp.r;
	}

	void VSIN_FLOAT2_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = SharedExpToFloat(*sourcePtr);

		destPtr[0] = temp.r;
		destPtr[1] = temp.g;
	}

	void VSIN_FLOAT3_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = SharedExpToFloat(*sourcePtr);

		destPtr[0] = temp.r;
		destPtr[1] = temp.g;
		destPtr[2] = temp.b;
	}

	void VSIN_FLOAT4_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{
		Ceng::FLOAT32* destPtr = (Ceng::FLOAT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		Color3_Float temp = SharedExpToFloat(*sourcePtr);

		destPtr[0] = temp.r;
		destPtr[1] = temp.g;
		destPtr[2] = temp.b;
		destPtr[3] = 1.0f;
	}
};

