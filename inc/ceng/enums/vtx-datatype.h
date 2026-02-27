/*****************************************************************************
*
* vtx-datatype.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_VTX_DATATYPE_H
#define _CENG_VTX_DATATYPE_H

namespace Ceng
{
	namespace VTX_DATATYPE 
	{
		enum value
		{
			UNKNOWN = 0 ,

			// Single precision floating point
			FLOAT = 1 ,

			// 2 x Single precision floating point
			FLOAT2 = 2 ,

			// 3 x Single precision floating point
			FLOAT3 = 3 ,

			// 4 x Single precision floating point
			FLOAT4 = 4 ,

			// Double precision floating point
			DOUBLE = 5 ,

			// 2 x Single precision floating point
			DOUBLE2 = 6 ,

			// 3 x Single precision floating point
			DOUBLE3 = 7 ,

			// 4 x Single precision floating point
			DOUBLE4 = 8 ,

			// **** Half-precision floats
		
			// 1 x 16-bit floating point
			FP16 = 9 ,      

			// 2 x 16-bit floating point
			FP16_2 = 10 , 

			// 3 x 16-bit floating point
			FP16_3 = 11 ,  

			// 4 x 16-bit floating point
			FP16_4 = 12 , 
				
			// 32-bit signed integer
			INT = 13 , 

			// 2 x 32-bit signed integer
			INT2 = 14 ,

			// 3 x 32-bit signed integer
			INT3 = 15 ,

			// 4 x 32-bit signed integer
			INT4 = 16 ,

			// 32-bit unsigned signed integer
			UINT = 17, 

			// 2 x 32-bit unsigned signed integer
			UINT2 = 18,

			// 3 x 32-bit unsigned signed integer
			UINT3 = 19,

			// 4 x 32-bit unsigned signed integer
			UINT4 = 20,

			// 16-bit signed integer
			SHORT = 21,

			// 2 x 16-bit signed integer
			SHORT2 = 22 ,

			// 3 x 16-bit signed integer
			SHORT3 = 23 ,

			// 4 x 16-bit signed integer
			SHORT4 = 24 , 			

			// 16-bit signed integer, normalized to (-1,1) float
			NSHORT = 25 ,

			// 2 x 16-bit signed integer, normalized to (-1,1) float
			NSHORT2 = 26 ,

			// 3 x 16-bit signed integer, normalized to (-1,1) float
			NSHORT3 = 27 ,

			// 4 x 16-bit signed integer, normalized to (-1,1) float
			NSHORT4 = 28 ,

			// 16-bit unsigned integer
			USHORT = 29 ,

			// 2 x 16-bit unsigned integer
			USHORT2 = 30 ,

			// 3 x 16-bit unsigned integer
			USHORT3 = 31 , 

			// 4 x 16-bit unsigned integer
			USHORT4 = 32 ,

			// 16-bit unsigned integer, normalized to (0,1) float
			UNSHORT = 33 ,

			// 2 x 16-bit unsigned integer, normalized to (0,1) float
			UNSHORT2 = 34 ,

			// 3 x 16-bit unsigned integer, normalized to (0,1) float
			UNSHORT3 = 35 ,

			// 4 x 16-bit unsigned integer, normalized to (0,1) float
			UNSHORT4 = 36 , 

			// 8-bit signed integer
			BYTE = 37 ,

			// 2 x 8-bit signed integer
			BYTE2 = 38 ,

			// 3 x 8-bit signed integer
			BYTE3 = 39 ,

			// 4 x 8-bit signed integer
			BYTE4 = 40 , 

			// 8-bit unsigned integer
			UBYTE = 41 , 

			// 2 x 8-bit unsigned integer
			UBYTE2 = 42, 

			// 3 x 8-bit unsigned integer
			UBYTE3 = 43, 

			// 4 x 8-bit unsigned integer
			UBYTE4 = 44,

			// 8-bit unsigned integer, normalized to (0,1) float
			UNBYTE = 45,

			// 2 x 8-bit unsigned integer, normalized to (0,1) float
			UNBYTE2 = 46,

			// 3 x 8-bit unsigned integer, normalized to (0,1) float
			UNBYTE3 = 47,

			// 4 x 8-bit unsigned integer, normalized to (0,1) float
			UNBYTE4 = 48,
		
			// **** Color formats
		
			// normalized to (0,1) float
			UNORM_R5_G6_B5 = 49 , 

			// 16-bit B5_G6_B5 (OpenGL)
			UNORM_B5_G6_R5 = 50 , 

			// 16-bit A1_R5_G5_B5 (Direct3D)
			UNORM_A1_R5_G5_B5 = 51 , 

			// 16-bit A1_B5_G5_R5 (OpenGL)
			UNORM_A1_B5_G5_R5 = 52 , 

			// 16-bit R5_G5_B5 (Direct3D)
			UNORM_R5_G5_B5 = 53 , 

			// 16-bit B5_G5_R5 (OpenGL)
			UNORM_B5_G5_R5 = 54 , 

			// 16-bit A4_R4_G4_B4 (Direct3D)
			UNORM_A4_R4_G4_B4 = 55 , 
			
			// 16-bit A4_B4_G4_R4 (OpenGL)
			UNORM_A4_B4_G4_R4 = 56 , 

			// 18-bit color with alpha (stored in 32 bits)
			// normalized to (0,1) float
			UNORM_A6_R6_G6_B6 = 57 , 

			// 18-bit color with alpha (stored in 32 bits)
			// normalized to (0,1) float
			UNORM_A6_B6_G6_R6 = 58 ,

			// 18-bit color, no alpha (stored in 32 bits)
			// normalized to (0,1) float
			UNORM_X6_R6_G6_B6 = 59 , 

			// 18-bit color, no alpha (stored in 32 bits)
			// normalized to (0,1) float
			UNORM_X6_B6_G6_R6 = 60 , 

			// Blue in least significant byte (Direct3D)
			UNORM_SRGB_A8_R8_G8_B8 = 61,

			// Red in least significant byte (OpenGL)
			UNORM_SRGB_A8_B8_G8_R8 = 62,

			// 24-bit color, no alpha. Red in least significant byte.
			// normalized to (0,1) float
			UNORM_SRGB_X8_B8_G8_R8 = 63,

			// 24-bit color, no alpha. Blue in least significant byte.
			// normalized to (0,1) float
			UNORM_SRGB_X8_R8_G8_B8 = 64,

			// 10 bits for each color, 2 bit alpha.
			// normalized to (0,1) float 
			UNORM_A2_B10_G10_R10 = 65 ,

			// 10 bits for each color, 2 bit alpha.
			// normalized to (0,1) float 
			UINT_A2_B10_G10_R10 = 66 ,

			// 8-bit alpha value only
			// normalized to (0,1) float 
			UNORM_A8 = 67,

			// 1-bit red channel (stored in 8 bits)
			// normalized to (0,1) float 
			UNORM_R1 = 68,

			// Unsigned mini floating point values. Each field has 5 bit biased exponent.
			// 6-bit mantissa for red and green, 5 bits for blue.
			FLOAT_B10_G11_R11 = 69,

			// 3 unsigned mini floating point values. All fields share the same 5 bit biased exponent.
			// Each channel has unique 9 bit mantissa.
			SHAREDEXP_E5_B9_G9_R9 = 70,

			// Gives two color values that share red and blue channels.
			// normalized to (0,1) float 
			UNORM_G8_B8_G8_R8 = 71,

			// Gives two color values that share red and blue channels.
			// normalized to (0,1) float 
			UNORM_B8_G8_R8_G8 = 72,
		
			FORMAT_END = 1 << 30,
		};
	};
	
};

#endif