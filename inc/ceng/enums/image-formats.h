/*****************************************************************************
*
* image-formats.h
*
* By Jari Korkala 4/2013
*
* File created as part of project refactoring.
*
*****************************************************************************/

#ifndef _CENG_IMAGE_FORMATS_H
#define _CENG_IMAGE_FORMATS_H

namespace Ceng
{
	namespace IMAGE_FORMAT
	{ 
		enum value
		{
			UNKNOWN = 0 , // User defined data
		
			//***************************
			// Depth-stencil formats
		
			D16 = 1 , // Pseudo-depth as 0.16 fixed point
			D16_S8 = 2 , // With 8-bit stencil
			D16_S16 = 3 , // With 16-bit stencil
		
			D24_S8 = 4 , // With 8-bit stencil
			D24_S16 = 5 , // With 16-bit stencil
		
			D32F = 6 , // Pseudo-depth as FLOAT32 [0,1]
			D32F_S8 = 7 , // With 8-bit stencil
			D32F_S16 = 8 , // With 16-bit stencil
		
			D32F_IW = 9 , // 1/W -buffer as FLOAT32
			D32F_IW_S8 = 10 , // With 8-bit stencil
			D32F_IW_S16 = 11 , // With 16-bit stencil
		
			D32F_W = 12 , // W-buffer as FLOAT32
			D32F_W_S8 = 13 , // With 8-bit integer stencil
			D32F_W_S16 = 14 , // With 8-bit integer stencil
		
			D64F = 15 , // Pseudo-depth as FLOAT64 [0,1]
			D64F_S8 = 16 , // With 8-bit stencil
			D64F_S16 = 17 , // With 16-bit stencil
		
			D64F_IW = 18 , // 1/W -buffer as FLOAT64
			D64F_IW_S8 = 19 , // With 8-bit stencil
			D64F_IW_S16 = 20 , // With 16-bit stencil
		
			D64F_W = 21 , // W-buffer as FLOAT64
			D64F_W_S8 = 22 , // With 8-bit integer stencil
			D64F_W_S16 = 23 , // With 8-bit integer stencil

			// 8-bit stencil, no depth
			s8 = 24,

			// 16-bit stencil, no depth
			s16 = 25,

			// 32-bit integer depth buffer
			D32 = 26,

			// 16-bit (stencil=1,depth=15) little endian
			D15_S1 = 27,

			// 32-bit (empty=8,depth=24) little endian
			D24_X8 = 28,

			// 32-bit format (stencil=4,empty=4,depth=24) little endian
			D24_X4_S4 = 29,

			// 32-bit format (stencil=8,float depth=24) little endian
			D24F_S8 = 30,

			//**********************************
			// Color formats (input & output)

			//---------------------------
			// Simple 1 channel formats
			
			// 8-bit red
			// Unsigned fixed point in [0,1] range
			unorm_r8 = 31,

			// 8-bit red
			// Unsigned integer in [0,255] range
			uint_r8 = 32,

			// 8-bit red
			// Signed integer in [-128,127] range
			int_r8 = 33,

			// 16-bit red
			// Unsigned fixed point in [0,1] range
			unorm_r16 = 34,

			// 8-bit red
			// Unsigned integer in [0,65535] range
			uint_r16 = 35,

			// 8-bit red
			// Signed integer in [-32768,32767] range
			int_r16 = 36,

			// Single precision float, R
			fp32_r = 37,

			// Half-precision float, R
			fp16_r = 38,

			// Half-precision float, grayscale
			fp16_gray = 39,

			// 8-bit grayscale
			// Unsigned fixed point in [0,1] range
			gray_8 = 40,

			// 16-bit grayscale
			// Unsigned fixed point in [0,1] range
			gray_16 = 41,

			// 16-bit grayscale
			// Unsigned fixed point in [0,1] range
			gray_24 = 42,

			// 32-bit grayscale
			// Unsigned fixed point in [0,1] range
			gray_32 = 43,

			// 8-bit format (alpha=8)
			// Unsigned fixed point in [0,1] range
			alpha_8 = 44,

			//---------------------------
			// Simple 2 channel formats

			// 16-bit format, 8 bits per channel
			// Unsigned fixed point in [0,1] range
			unorm_r8_g8 = 45,

			// 16-bit format, 8 bits per channel
			// Unsigned integer in [0,255] range
			uint_r8_g8 = 46,

			// 16-bit format, 8 bits per channel
			// Signed integer in [-128,127] range
			int_r8_g8 = 47,

			// 16-bit format, 8 bits per channel
			// Unsigned fixed point in [0,1] range
			unorm_g8_r8 = 48,

			// 16-bit format, 8 bits per channel
			// Unsigned integer in [0,255] range
			uint_g8_r8 = 49,

			// 16-bit format, 8 bits per channel
			// Signed integer in [-128,127] range
			int_g8_r8 = 50,

			// 32-bit format, 16 bits per channel
			// Unsigned fixed point in [0,1] range
			unorm_r16_g16 = 51,

			// 32-bit format, 16 bits per channel
			// Unsigned integer in [0,65535] range
			uint_r16_g16 = 52,

			// 32-bit format, 16 bits per channel
			// Signed integer in [-32768,32767] range
			int_r16_g16 = 53,

			// 32-bit format, 16 bits per channel
			// Unsigned fixed point in [0,1] range
			unorm_g16_r16 = 54,

			// 32-bit format, 16 bits per channel
			// Unsigned integer in [0,65535] range
			uint_g16_r16 = 55,

			// 32-bit format, 16 bits per channel
			// Signed integer in [-32768,32767] range
			int_g16_r16 = 56,

			// Single precision float, GR, little endian
			fp32_gr = 57,

			// Single precision float, RG, little endian
			fp32_rg = 58,

			// Half-precision float, GR, little endian
			fp16_gr = 59,

			// Half-precision float, RG, little endian
			fp16_rg = 60,

			//---------------------------
			// Simple 3 channel formats

			// Expanded to (alpha=255,red,green,blue)
			// Unsigned fixed point in [0,1] range
			unorm_r8_g8_b8 = 61,

			// Expanded to (alpha=255,red,green,blue)
			// Unsigned integer in [0,255] range
			uint_r8_g8_b8 = 62,

			// Expanded to (alpha=255,red,green,blue)
			// Signed integer in [-128,127] range
			int_r8_g8_b8 = 63,

			// Expanded to (alpha=255,blue,green,red)
			// Unsigned fixed point in [0,1] range
			unorm_b8_g8_r8 = 64,

			// Expanded to (alpha=255,red,green,blue)
			// Unsigned integer in [0,255] range
			uint_b8_g8_r8 = 65,

			// Expanded to (alpha=255,red,green,blue)
			// Signed integer in [-128,127] range
			int_b8_g8_r8 = 66,

			// 96 bit format, 32 bits per channel
			unorm_b32_g32_r32 = 126,

			// Single precision float, BGR, little endian
			fp32_bgr = 67,

			// Single precision float, RGB, little endian
			fp32_rgb = 68,

			//---------------------------
			// Simple 4 channel formats

			// 32-bit format (alpha=8,red=8,green=8,blue=8) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a8_r8_g8_b8 = 69,

			// 32-bit format (alpha=8,red=8,green=8,blue=8) little endian
			// Unsigned integer in [0,255] range
			uint_a8_r8_g8_b8 = 70,

			// 32-bit format (alpha=8,red=8,green=8,blue=8) little endian
			// Signed integer in [-128,127] range
			int_a8_r8_g8_b8 = 71,

			// 32-bit format (alpha=8,blue=8,green=8,red=8) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a8_b8_g8_r8 = 72,

			// 32-bit format (alpha=8,red=8,green=8,blue=8) little endian
			// Unsigned integer in [0,255] range
			uint_a8_b8_g8_r8 = 73,

			// 32-bit format (alpha=8,red=8,green=8,blue=8) little endian
			// Signed integer in [-128,127] range
			int_a8_b8_g8_r8 = 74,

			// 64-bit format (alpha=16,blue=16,green=16,red=16) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a16_b16_g16_r16 = 75,

			// 64-bit format (alpha=16,blue=16,green=16,red=16) little endian
			// Unsigned integer in [0,65535] range
			uint_a16_b16_g16_r16 = 76,

			// 64-bit format (alpha=16,blue=16,green=16,red=16) little endian
			// Signed integer in [-32768,32767] range
			int_a16_b16_g16_r16 = 77,

			// 64-bit format (alpha=16,red=16,green=16,blue=16) little endian
			// Unsigned integer in [0,65535] range
			unorm_a16_r16_g16_b16 = 78,

			// 128-bit format (alpha=32,blue=32,green=32,red=32) little endian
			// Signed integer in [-32768,32767] range
			unorm_a32_b32_g32_r32 = 79,

			// Single precision float (alpha,blue,green,red), little endian
			fp32_abgr = 80,

			// Single precision float (alpha,red,green,blue), little endian
			fp32_argb = 81,

			// Half-precision float, ABGR little endian
			fp16_abgr = 82,

			// Half-precision float, ARGB, little endian 
			fp16_argb = 83,

			//---------------------------
			// Complicated formats

			// 16-bit color (red=5,green=6,blue=5) little endian
			// Unsigned fixed point in [0,1] range
			unorm_r5_g6_b5 = 84,

			// 16-bit color (blue=5,green=6,red=5) little endian
			// Unsigned fixed point in [0,1] range
			unorm_b5_g6_r5 = 85,

			// 16-bit format (alpha=1,red=5,green=5,blue=5) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a1_r5_g5_b5 = 86 ,

			// 16-bit format (alpha=1,red=5,green=5,blue=5) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a1_b5_g5_r5 = 87,
			
			// 32-bit format (alpha=2,red=10,green=10,blue=10) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a2_r10_g10_b10 = 88 ,

			// 32-bit format (alpha=2,blue=10,green=10,red=10) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a2_b10_g10_r10 = 89,		

			// 8-bit format (red=3,green=3,blue=2) little endian
			// Unsigned fixed point in [0,1] range
			unorm_r3_g3_b2 = 90,

			// 8-bit format (red=3,green=3,blue=2) little endian
			// Unsigned fixed point in [0,1] range
			unorm_b2_g3_r3 = 91,

			// 32-bit format (empty,red,green,blue) little endian
			// Unsigned fixed point in [0,1] range
			unorm_x8_r8_g8_b8 = 92,

			// 32-bit format (empty,blue,green,red) little endian
			// Unsigned fixed point in [0,1] range
			unorm_x8_b8_g8_r8 = 93,

			// 16-bit format (empty=1,red=5,green=5,blue=5) little endian
			// Unsigned fixed point in [0,1] range
			unorm_x1_r5_g5_b5 = 94 ,

			// 16-bit format (alpha=4,red=4,green=4,blue=4) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a4_r4_g4_b4 = 95 ,

			// 16-bit format (alpha=4,blue=4,green=4,red=4) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a4_b4_g4_r4 = 96,

			// 16-bit format (empty=4,red=4,green=4,blue=4) little endian
			// Unsigned fixed point in [0,1] range
			unorm_x4_r4_g4_b4 = 97,

			// 16-bit format (empty=4,blue=4,green=4,red=4) little endian
			// Unsigned fixed point in [0,1] range
			unorm_x4_b4_g4_r4 = 98,

			// 16-bit format (alpha=8,red=3,green=3,blue=2) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a8_r3_g3_b2 = 99 ,

			// 16-bit format (alpha=8,red=3,green=3,blue=2) little endian
			// Unsigned fixed point in [0,1] range
			unorm_a8_b2_g3_r3 = 100,

			//*******************************
			// Compressed textures, input only

			dxt1 = 101,
			dxt2 = 102,
			dxt3 = 103,
			dxt4 = 104,
			dxt5 = 105,

			normal_3dc = 106,

			bc7_rgba_unorm = 107,
			bc7_srgb_alpha_unorm = 108,
			
			bc6_rgb_float = 109,
			bc6_rgb_unsigned_float = 110,

			etc2_rgb8 = 111,
			etc2_srgb8 = 112,

			etc2_rgb8_a1 = 113,
			etc2_srgb8_a1 = 114,

			etc2_rgba8 = 115,
			etc2_srgb8_a8 = 116,

			eac_r11_unsigned = 117,
			eac_r11_signed = 118,

			eac_rg11_unsigned = 119,
			eac_rg11_signed = 120,

			etc1_rgb = 121,

			bc5_rg_unorm = 122,
			bc5_rg_snorm = 123,

			bc4_r_unorm = 124,
			bc4_r_snorm = 125,		

			FORCE_32B = 1 << 30 ,
		}; // enum

	}; // namespace IMAGE_FORMAT

}; // namespace Ceng

#endif