/*****************************************************************************
*
* cr-fragment-var.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CR_FRAGMENT_VAR_H
#define _CENG_CR_FRAGMENT_VAR_H

#include <ceng/enums/shader-datatype.h>
#include <ceng/enums/shader-semantic.h>

#include "crender-base.h"

#include <ceng/math/ce-vector.h>

namespace Ceng
{
	class CR_FloatFragment
	{
	public:

		VectorF4 startValue;
		VectorF4 step_dx;
		VectorF4 step_dy;

		CR_FloatFragment()
		{
			startValue = VectorF4(0,0,0,0);
			step_dx = VectorF4(0,0,0,0);
			step_dy = VectorF4(0,0,0,0);
		}
	};

	class CR_FloatPixelStep
	{
	public:
		VectorF4 step_dx; // += dx
		VectorF4 step_ndx_dy; // += dy - dx

		CR_FloatPixelStep()
		{
			step_dx = VectorF4(0,0,0,0);
			step_ndx_dy = VectorF4(0,0,0,0);
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
			startValue = VectorD2(0,0);
			step_dx = VectorD2(0,0);
			step_dy = VectorD2(0,0);
		}
	};

	class CR_DoublePixelStep
	{
	public:
		VectorD2 step_dx; // += dx
		VectorD2 step_ndx_dy; // += dy - dx

		CR_DoublePixelStep()
		{
			step_dx = VectorD2(0,0);
			step_ndx_dy = VectorD2(0,0);
		}
	};

	class CR_FragmentData
	{
	public:
		CR_FloatFragment *floatBlock;
		CR_DoubleFragment *doubleBlock;

		UINT8 *variableStep;

		INT32 *vertexConst;

		CR_FragmentData()
		{
			floatBlock = nullptr;
			doubleBlock = nullptr;

			variableStep = nullptr;
			vertexConst = nullptr;
		}
	};
	
	/**
	 *  Size of each Ceng::SHADER_DATATYPE in bytes.
	 *
	 *  NOTE: Order must correspond to that of Ceng::SHADER_DATATYPE enumeration.
	 */
	const UINT32 CR_SHADER_DATA_TYPE_SIZE[] =
	{
		0 ,  // UNKNOWN

		4 , // FLOAT
		8 , // FLOAT2
		12 , // FLOAT3
		16 , // FLOAT4

		8 , // DOUBLE
		16 , // DOUBLE2
		24 , // DOUBLE3
		32 , // DOUBLE4

		4 , // UINT
		8 , // UINT2
		12 , // UINT3
		16 , // UINT4

		4 , // INT
		8 , // INT2
		12 , // INT3
		16 , // INT4

		4 , // BOOL
		8 , // BOOL2
		12 , // BOOL3
		16 , // BOOL4

		64 , // FLOAT4x4
		36 , // FLOAT3x3
		16 , // FLOAT2x2

		128 , // DOUBLE4x4
		72 , // DOUBLE3x3
		32 , // DOUBLE2x2

		64 , // UINT4x4
		36 , // UINT3x3
		16 , // UINT2x2

		64 , // INT4x4
		36 , // INT3x3
		16 , // INT2x2

		64 , // BOOL4x4
		36 , // BOOL3x3
		16 , // BOOL2x2
	};

	//*********************************************************************************
	// Vertex shader output (fragment) format

	struct CR_FragmentVariable
	{
		/**
		 * Semantic value.
		 */
		Ceng::SHADER_SEMANTIC::value semantic;

		/**
		 * A CR_SHADER_DATA_TYPE value.
		 */
		Ceng::SHADER_DATATYPE::value format;

		/**
		 * Byte offset in the fragment format.
		 */
		UINT32 offset;

		/**
		 * Combination of CR_FRAGMENT_VARIABLE_OPTIONS values.
		 */
		UINT32 options;
	};

};

#endif