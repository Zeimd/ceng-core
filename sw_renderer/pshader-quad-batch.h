#pragma once

#ifndef CENG_SWR_PSHADER_QUAD_BATCH_H
#define CENG_SWR_PSHADER_QUAD_BATCH_H

#include <ceng/datatypes/basic-types.h>

namespace Ceng::SWRender
{
	/**
	 * Quad format's fixed header.
	 *
	 * NOTE: Struct size must be divisible by 16
	 */
	struct alignas(16) PixelShaderQuadBatch
	{
		/**
		 * How many continuous horizontal quads.
		 */
		UINT32 chainLength;

		/**
		 * Screen location of the top-left corner.
		 * Must be 8-byte aligned.
		 */
		UINT32 screenX;
		UINT32 screenY;

		UINT32 padding;

		/**
		 * Coverage values for up to 32 quads.
		 */
		UINT32 coverageMask[4];
	};
}

#endif