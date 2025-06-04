/*****************************************************************************
*
* cr-quad-format.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CR_QUAD_FORMAT_H
#define _CENG_CR_QUAD_FORMAT_H

#include <vector>

#include <ceng/enums/shader-datatype.h>
#include <ceng/enums/shader-semantic.h>

#include "crender-base.h"

#include "quad-variable.h"

namespace Ceng
{
	namespace SWRender
	{
		class CR_FloatFragment;
		class CR_DoubleFragment;
	}

	struct CR_TriangleData;

	class CR_FragmentFormat;

	class CR_QuadFormat
	{
	public:

		// Size of the quad without render targets.
		UINT32 baseSize;

		/**
		 * Amount of 16-byte FLOAT blocks.
		 */
		UINT32 floatBlocks;

		/**
		 * Offset of first FLOAT block within
		 * the format.
		 */
		POINTER floatStart;

		/**
		 * Amount of 16-byte DOUBLE blocks.
		 */
		UINT32 doubleBlocks;

		/**
		 * Offset of first DOUBLE block within
		 * the format.
		 */
		POINTER doubleStart;

		/**
		 * Size of the buffer for variable stepping in pixel shader.
		 */
		UINT32 gradientBufferSize;

		/**
		 * Amount of 4 x POINTER32 or
		 * 2 x POINTER64 render target blocks.
		 */
		//UINT32 targetBlocks;

		/**
		 * Offset of first render target
		 * address block.
		 */
		POINTER targetStart;

		std::vector<CR_QuadVariable> variables;

	public:
		CR_QuadFormat();
		~CR_QuadFormat();

		CRESULT Configure(CR_FragmentFormat *fragmentFormat);

		/**
		 * Converts a vertex shader output fragment into a format optimal for
		 * pixel shader.
		 */
		CRESULT TranslateFragment(UINT8 *fragmentIn[3],
										 FLOAT32 *positionW[3],
										 FLOAT32 *vdy10,FLOAT32 *vdy21,
										 FLOAT32 *vdx10,FLOAT32 *vdx21,
										 FLOAT32 *gradientDiv,
										 FLOAT32 *initialStepX,FLOAT32 *initialStepY,
										 SWRender::CR_FloatFragment *floatVariables,
										 SWRender::CR_DoubleFragment *doubleVariables,
										 UINT8 *variableStep);

		
	};

};


#endif