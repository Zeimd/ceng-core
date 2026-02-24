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
#include "vshader-input.h"

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
	void VSIN_FLOAT_UNORM_X6_B6_G6_R7(void* dest, void* source);
		
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
	void VSIN_FLOAT2_UNORM_X6_B6_G6_R7(void* dest, void* source);

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
	void VSIN_FLOAT3_UNORM_X6_B6_G6_R7(void* dest, void* source);

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
	void VSIN_FLOAT4_UNORM_X6_B6_G6_R7(void* dest, void* source);

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
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R7:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_X6_B6_G6_R7;

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

	case Ceng::VTX_DATATYPE::UNORM_G8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_G8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_B8_G8_R8_G8:
		return &Ceng::Vshader::VSIN_FLOAT_UNORM_B8_G8_R8_G8;
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
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R7:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_X6_B6_G6_R7;

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

	case Ceng::VTX_DATATYPE::UNORM_G8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_G8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_B8_G8_R8_G8:
		return &Ceng::Vshader::VSIN_FLOAT2_UNORM_B8_G8_R8_G8;
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
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R7:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_X6_B6_G6_R7;

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

	case Ceng::VTX_DATATYPE::UNORM_G8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_G8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_B8_G8_R8_G8:
		return &Ceng::Vshader::VSIN_FLOAT3_UNORM_B8_G8_R8_G8;
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
	case Ceng::VTX_DATATYPE::UNORM_X6_B6_G6_R7:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_X6_B6_G6_R7;

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

	case Ceng::VTX_DATATYPE::UNORM_G8_B8_G8_R8:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_G8_B8_G8_R8;
	case Ceng::VTX_DATATYPE::UNORM_B8_G8_R8_G8:
		return &Ceng::Vshader::VSIN_FLOAT4_UNORM_B8_G8_R8_G8;
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

/*
void (*InFloat::call_ToFloat[128])(void*,void*) =
	{
		// Indexed by source format

		NULL , // UNKNOWN

		&VSIN_FLOAT_FLOAT_X86 , // FLOAT
		NULL , // FLOAT2
		NULL , // FLOAT3
		NULL , // FLOAT4

		NULL , // DOUBLE
		NULL , // DOUBLE2
		NULL , // DOUBLE3
		NULL , // DOUBLE4

		NULL , // FP16_2
		NULL , // FP16_4
	};
*/

/*
void (*InFloat2::call_ToFloat2[128])(void*,void*) =
	{
		// Indexed by source format

		NULL , // UNKNOWN

		NULL , // FLOAT
		&VSIN_FLOAT2_FLOAT2_X86_SSE2 , // FLOAT2
		NULL , // FLOAT3
		NULL , // FLOAT4

		NULL , // DOUBLE
		NULL , // DOUBLE2
		NULL , // DOUBLE3
		NULL , // DOUBLE4

		NULL , // FP16_2
		NULL , // FP16_4
	};
*/

/*
void (*InFloat3::call_ToFloat3[128])(void*, void*) =
{
	// Indexed by source format

	NULL , // UNKNOWN

	NULL , // FLOAT
	NULL , // FLOAT2
	&VSIN_FLOAT3_FLOAT3_X86 , // FLOAT3
	NULL , // FLOAT4

	NULL , // DOUBLE
	NULL , // DOUBLE2
	NULL , // DOUBLE3
	NULL , // DOUBLE4

	NULL , // FP16_2
	NULL , // FP16_4
};
*/

/*
void (*InFloat4::call_ToFloat4[128])(void*,void*) =
	{
		// Indexed by source format

		NULL , // UNKNOWN

		NULL , // FLOAT
		NULL , // FLOAT2
		NULL , // FLOAT3
		&VSIN_FLOAT4_FLOAT4_X86_SSE , // FLOAT4

		NULL , // DOUBLE
		NULL , // DOUBLE2
		NULL , // DOUBLE3
		NULL , // DOUBLE4

		NULL , // FP16_2
		NULL , // FP16_4
	};
*/

namespace Ceng::Vshader
{
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

	//*************************************************
	// Destination is float

	void VSIN_FLOAT_FLOAT(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		*destPtr = *sourcePtr;
	}

	void VSIN_FLOAT_FLOAT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_FLOAT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_FLOAT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_DOUBLE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_DOUBLE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_DOUBLE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_DOUBLE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_FP16(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_FP16_2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_FP16_3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_FP16_4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_INT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_INT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_INT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_INT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UINT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UINT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UINT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UINT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_SHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_SHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_SHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_SHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_USHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_USHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_USHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_USHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_NSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_NSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_NSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_NSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_BYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_BYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_BYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_BYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_B5_G6_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_R5_G6_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_X6_B6_G6_R7(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UINT_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_A8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_R1(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_FLOAT_B10_G11_R11(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_G8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT_UNORM_B8_G8_R8_G8(void* dest, void* source)
	{

	}

	//*************************************************
	// Destination is float2

	void VSIN_FLOAT2_FLOAT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_FLOAT2(void* dest, void* source)
	{
		__m128d temp = _mm_load_sd((double*)source);

		_mm_store_sd((double*)dest, temp);
	}

	void VSIN_FLOAT2_FLOAT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_FLOAT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_DOUBLE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_DOUBLE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_DOUBLE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_DOUBLE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_FP16(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_FP16_2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_FP16_3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_FP16_4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_INT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_INT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_INT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_INT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UINT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UINT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UINT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UINT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_SHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_SHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_SHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_SHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_USHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_USHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_USHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_USHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_NSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_NSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_NSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_NSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_BYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_BYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_BYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_BYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_B5_G6_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_R5_G6_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_X6_B6_G6_R7(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UINT_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_A8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_R1(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_FLOAT_B10_G11_R11(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_G8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT2_UNORM_B8_G8_R8_G8(void* dest, void* source)
	{

	}

	//*************************************************
	// Destination is float3

	void VSIN_FLOAT3_FLOAT(void* dest, void* source) 
	{

	}

	void VSIN_FLOAT3_FLOAT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_FLOAT3(void* dest, void* source)
	{
		Ceng::UINT32* destPtr = (Ceng::UINT32*)dest;
		Ceng::UINT32* sourcePtr = (Ceng::UINT32*)source;

		destPtr[0] = sourcePtr[0];
		destPtr[1] = sourcePtr[1];
		destPtr[2] = sourcePtr[2];
	}
	void VSIN_FLOAT3_FLOAT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_DOUBLE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_DOUBLE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_DOUBLE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_DOUBLE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_FP16(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_FP16_2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_FP16_3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_FP16_4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_INT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_INT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_INT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_INT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UINT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UINT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UINT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UINT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_SHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_SHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_SHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_SHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_USHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_USHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_USHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_USHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_NSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_NSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_NSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_NSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_BYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_BYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_BYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_BYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_R5_G6_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_B5_G6_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_X6_B6_G6_R7(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UINT_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_A8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_R1(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_FLOAT_B10_G11_R11(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_G8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT3_UNORM_B8_G8_R8_G8(void* dest, void* source)
	{

	}

	//*************************************************
	// Destination is float4

	void VSIN_FLOAT4_FLOAT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FLOAT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FLOAT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FLOAT4(void* dest, void* source) 
	{
		__m128 temp = _mm_load_ps((float*)source);

		_mm_store_ps((float*)dest, temp);
	}

	void VSIN_FLOAT4_DOUBLE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_DOUBLE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_DOUBLE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_DOUBLE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FP16(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FP16_2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FP16_3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FP16_4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_INT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_INT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_INT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_INT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UINT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UINT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UINT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UINT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_SHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_SHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_SHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_SHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_USHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_USHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_USHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_USHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_NSHORT(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_NSHORT2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_NSHORT3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_NSHORT4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_BYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_BYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_BYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_BYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNBYTE(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNBYTE2(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNBYTE3(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNBYTE4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_R5_G6_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_B5_G6_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A1_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A1_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_R5_G5_B5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_B5_G5_R5(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A4_R4_G4_B4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A4_B4_G4_R4(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A6_B6_G6_R6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_X6_R6_G6_B6(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_X6_B6_G6_R7(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_SRGB_A8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_SRGB_A8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_SRGB_X8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_SRGB_X8_R8_G8_B8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UINT_A2_B10_G10_R10(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_A8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_R1(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_FLOAT_B10_G11_R11(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_SHAREDEXP_E5_B9_G9_R9(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_G8_B8_G8_R8(void* dest, void* source)
	{

	}

	void VSIN_FLOAT4_UNORM_B8_G8_R8_G8(void* dest, void* source)
	{

	}

};

