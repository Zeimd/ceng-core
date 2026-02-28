#pragma once

#ifndef CENG_SWRENDER_CONVERSION_UTIL_H
#define CENG_SWRENDER_CONVERSION_UTIL_H

#include <limits>
#include <math.h>

#include <ceng/datatypes/basic-types.h>

namespace Ceng
{
	const Ceng::FLOAT32 scaleNormalizeUNfx2 = 1.0f / 3.0f;
	const Ceng::FLOAT32 scaleNormalizeUNfx4 = 1.0f / 15.0f;
	const Ceng::FLOAT32 scaleNormalizeUNfx5 = 1.0f / 31.0f;
	const Ceng::FLOAT32 scaleNormalizeUNfx6 = 1.0f / 63.0f;
	const Ceng::FLOAT32 scaleNormalizeUNfx8 = 1.0f / 255.0f;
	const Ceng::FLOAT32 scaleNormalizeUNfx9 = 1.0f / 511.0f;
	const Ceng::FLOAT32 scaleNormalizeUNfx10 = 1.0f / 1023.0f;

	const Ceng::FLOAT32 scaleNormalizeUint8 = 1.0f / 255.0f;
	const Ceng::FLOAT32 scaleNormalizeInt8 = 1.0f / 128.0f;

	const Ceng::FLOAT32 scaleNormalizeUint16 = 1.0f / 65535.0f;
	const Ceng::FLOAT32 scaleNormalizeInt16 = 1.0f / 32768.0f;

	struct Color3_Int32
	{
		Ceng::UINT32 r;
		Ceng::UINT32 g;
		Ceng::UINT32 b;
	};

	struct Color3_Float
	{
		Ceng::FLOAT32 r;
		Ceng::FLOAT32 g;
		Ceng::FLOAT32 b;
	};

	struct Color4_Int32
	{
		Ceng::UINT32 r;
		Ceng::UINT32 g;
		Ceng::UINT32 b;
		Ceng::UINT32 a;
	};

	const Ceng::FLOAT32  srgbSmallDivisor = 1.0f / 12.92f;
	const Ceng::FLOAT32  srgbLargeDivisor = 1.0f / 1.055f;
	const Ceng::FLOAT32  srgbReverseExp = 1.0f / 2.4f;

	inline Ceng::FLOAT32 SrgbToLinear(Ceng::FLOAT32 source)
	{
		if (source <= 0.04045f)
		{
			return source * srgbSmallDivisor;
		}

		Ceng::FLOAT32 x = (source + 0.055f) * srgbLargeDivisor;

		return powf(x, 2.4f);
	}

	inline Ceng::FLOAT32 LinearToSrgb(Ceng::FLOAT32 source)
	{
		if (source <= 0.0031308f)
		{
			return source * 12.92f;
		}

		return 1.055f * powf(source, srgbReverseExp) - 0.055f;
	}

	const Ceng::FLOAT32 fp16_subnormal_pow = powf(2.0f, -14.0f);
	const Ceng::FLOAT32 fp16_mantissa_scale = 1.0f / powf(2.0f, 11.0f);

	inline Ceng::FLOAT32 HalfToFloat(Ceng::UINT16 source)
	{
		Ceng::UINT32 mantissa = source & ((1 << 11) - 1);
		Ceng::INT32 expField = (source >> 10) & 31;
		Ceng::INT32 sign = source >> 15;

		if (expField == 0)
		{
			if (mantissa == 0)
			{
				Ceng::FLOAT32 output = 0.0f;

				Ceng::UINT32* ptr = (Ceng::UINT32*)&output;

				*ptr |= (sign << 31);

				return output;
			}
			else
			{
				// subnormal number

				Ceng::FLOAT32 output = fp16_subnormal_pow * Ceng::FLOAT32(mantissa) * fp16_mantissa_scale;

				Ceng::UINT32* ptr = (Ceng::UINT32*)&output;

				*ptr |= (sign << 31);

				return output;
			}			
		}
		else if (expField == 15)
		{
			if (mantissa == 0)
			{
				Ceng::FLOAT32 output = std::numeric_limits<Ceng::FLOAT32>::infinity();

				Ceng::UINT32* ptr = (Ceng::UINT32*)&output;

				*ptr |= (sign << 31);

				return output;
			}
			else
			{
				Ceng::UINT32 signal = mantissa >> 9;

				if (signal)
				{
					return std::numeric_limits<Ceng::FLOAT32>::signaling_NaN();
				}
				else
				{
					return std::numeric_limits<Ceng::FLOAT32>::quiet_NaN();
				}
			}
		}

		// normal number

		Ceng::FLOAT32 output;

		Ceng::UINT32* ptr = (Ceng::UINT32*)&output;

		*ptr = (sign << 31);

		Ceng::INT32 exponent = expField - 15;

		exponent += 127;

		*ptr |= (exponent << 23);

		*ptr |= (mantissa << 13);

		return output;
	}

	inline Ceng::UINT16 FloatToHalf(Ceng::FLOAT32 source)
	{
		return 0;
	}

	inline Color3_Float Fp10_11_10_ToFloat(Ceng::UINT32 source)
	{
		return Color3_Float();
	}

	inline Color3_Float SharedExpToFloat(Ceng::UINT32 source)
	{
		return Color3_Float();
	}

	inline Color3_Int32 Extract_B5_G6_R5(Ceng::UINT16 source)
	{
		return Color3_Int32{ Ceng::UINT32(source & 31),
			Ceng::UINT32((source >> 5) & 63),
			Ceng::UINT32(source >> 10)
		};
	}

	inline Color3_Int32 Extract_R5_G6_B5(Ceng::UINT16 source)
	{
		return Color3_Int32{ Ceng::UINT32(source >> 10) ,
			Ceng::UINT32((source >> 5) & 63),
			Ceng::UINT32(source & 31)
		};
	}

	inline Color4_Int32 Extract_A1_R5_G5_B5(Ceng::UINT16 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32((source >> 9) & 63),
			Ceng::UINT32((source >> 5) & 31),
			Ceng::UINT32((source & 31)),
			Ceng::UINT32((source >> 14)),
		};
	}

	inline Color4_Int32 Extract_A1_B5_G5_R5(Ceng::UINT16 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32((source & 31)),
			Ceng::UINT32((source >> 5) & 31),
			Ceng::UINT32((source >> 9) & 63),			
			Ceng::UINT32((source >> 14)),
		};
	}

	inline Color3_Int32 Extract_R5_G5_B5(Ceng::UINT16 source)
	{
		return Color3_Int32
		{
			Ceng::UINT32((source >> 9) & 63),
			Ceng::UINT32((source >> 5) & 31),
			Ceng::UINT32((source & 31))			
		};
	}

	inline Color3_Int32 Extract_B5_G5_R5(Ceng::UINT16 source)
	{
		return Color3_Int32
		{
			Ceng::UINT32((source & 31)),
			Ceng::UINT32((source >> 5) & 31),			
			Ceng::UINT32((source >> 9) & 63),
		};
	}

	inline Color4_Int32 Extract_A4_R4_G4_B4(Ceng::UINT16 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32((source >> 8) & 15),
			Ceng::UINT32((source >> 4) & 15),
			Ceng::UINT32(source & 15),
			Ceng::UINT32((source >> 12))
		};
	}

	inline Color4_Int32 Extract_A4_B4_G4_R4(Ceng::UINT16 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32(source & 15),			
			Ceng::UINT32((source >> 4) & 15),
			Ceng::UINT32((source >> 8) & 15),
			Ceng::UINT32((source >> 12))
		};
	}

	inline Color4_Int32 Extract_A6_R6_G6_B6(Ceng::UINT32 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32( (source >> 12) & 63),
			Ceng::UINT32( (source >> 6) & 63),
			Ceng::UINT32( (source & 63) ),
			Ceng::UINT32( (source >> 18))
		};
	}

	inline Color4_Int32 Extract_A6_B6_G6_R6(Ceng::UINT32 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32((source & 63)),
			Ceng::UINT32((source >> 6) & 63),
			Ceng::UINT32((source >> 12) & 63),			
			Ceng::UINT32((source >> 18))
		};
	}

	inline Color3_Int32 Extract_X6_R6_G6_B6(Ceng::UINT32 source)
	{
		return Color3_Int32
		{
			Ceng::UINT32((source >> 12) & 63),
			Ceng::UINT32((source >> 6) & 63),
			Ceng::UINT32((source & 63))			
		};
	}

	inline Color3_Int32 Extract_X6_B6_G6_R6(Ceng::UINT32 source)
	{
		return Color3_Int32
		{
			Ceng::UINT32((source & 63)),
			Ceng::UINT32((source >> 6) & 63),
			Ceng::UINT32((source >> 12) & 63),			
		};
	}

	inline Color4_Int32 Extract_A8_R8_G8_B8(Ceng::UINT32 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32((source >> 16) & 255),
			Ceng::UINT32((source >> 8) & 255),
			Ceng::UINT32((source >> 0) & 255),
			Ceng::UINT32((source >> 24)),
		};
	}

	inline Color4_Int32 Extract_A8_B8_G8_R8(Ceng::UINT32 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32((source >> 0) & 255),
			Ceng::UINT32((source >> 8) & 255),
			Ceng::UINT32((source >> 16) & 255),			
			Ceng::UINT32((source >> 24)),
		};
	}
	
	inline Color3_Int32 Extract_X8_B8_G8_R8(Ceng::UINT32 source)
	{
		return Color3_Int32
		{
			Ceng::UINT32((source >> 0) & 255),
			Ceng::UINT32((source >> 8) & 255),
			Ceng::UINT32((source >> 16) & 255),			
		};
	}

	inline Color3_Int32 Extract_X8_R8_G8_B8(Ceng::UINT32 source)
	{
		return Color3_Int32
		{
			Ceng::UINT32((source >> 16) & 255),
			Ceng::UINT32((source >> 8) & 255),
			Ceng::UINT32((source >> 0) & 255),			
		};
	}

	inline Color4_Int32 Extract_A2_B10_G10_R10(Ceng::UINT32 source)
	{
		return Color4_Int32
		{
			Ceng::UINT32((source >> 0) & 1023),
			Ceng::UINT32((source >> 10) & 1023),
			Ceng::UINT32((source >> 20) & 1023),
			Ceng::UINT32((source >> 30)),
		};
	}
}

#endif