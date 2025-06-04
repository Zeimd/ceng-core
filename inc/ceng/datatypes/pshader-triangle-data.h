#pragma once

#ifndef CENG_SWR_PSHADER_TRIANGLE_DATA_H
#define CENG_SWR_PSHADER_TRIANGLE_DATA_H

#include "../math/ce-vector.h"

namespace Ceng::SWRender
{
	class CR_FloatFragment
	{
	public:

		VectorF4 startValue;
		VectorF4 step_dx;
		VectorF4 step_dy;

		CR_FloatFragment()
		{
			startValue = VectorF4(0, 0, 0, 0);
			step_dx = VectorF4(0, 0, 0, 0);
			step_dy = VectorF4(0, 0, 0, 0);
		}
	};

	class CR_FloatPixelStep
	{
	public:
		VectorF4 step_dx; // += dx
		VectorF4 step_ndx_dy; // += dy - dx

		CR_FloatPixelStep()
		{
			step_dx = VectorF4(0, 0, 0, 0);
			step_ndx_dy = VectorF4(0, 0, 0, 0);
		}
	};

	class CR_DoubleFragment
	{
	public:
		VectorD2 startValue;
		VectorD2 step_dx;
		VectorD2 step_dy;

		CR_DoubleFragment()
		{
			startValue = VectorD2(0, 0);
			step_dx = VectorD2(0, 0);
			step_dy = VectorD2(0, 0);
		}
	};

	class CR_DoublePixelStep
	{
	public:
		VectorD2 step_dx; // += dx
		VectorD2 step_ndx_dy; // += dy - dx

		CR_DoublePixelStep()
		{
			step_dx = VectorD2(0, 0);
			step_ndx_dy = VectorD2(0, 0);
		}
	};

	class CR_FragmentData
	{
	public:
		CR_FloatFragment* floatBlock;
		CR_DoubleFragment* doubleBlock;

		UINT8* variableStep;

		INT32* vertexConst;

		CR_FragmentData()
		{
			floatBlock = nullptr;
			doubleBlock = nullptr;

			variableStep = nullptr;
			vertexConst = nullptr;
		}
	};

	struct alignas(16) PixelShaderTriangleData
	{
		VectorF4 packedZ;
		VectorF4 packedZ_dx;
		VectorF4 packedZ_dy;
		VectorF4 packedZ_quad_dx;
		VectorF4 packedZ_quad_dy;

		VectorF4 packedW;
		VectorF4 packedW_dx;
		VectorF4 packedW_dy;
		VectorF4 packedW_quad_dx;
		VectorF4 packedW_quad_dy;

		FLOAT32 gradientDiv;

		CR_FragmentData fragment;
	};
}

#endif