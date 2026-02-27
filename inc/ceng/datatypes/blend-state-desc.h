/*****************************************************************************
*
* blend-state-desc.h
*
* Created By Jari Korkala 10/11/2015
*
*****************************************************************************/

#ifndef CENG_BLEND_STATE_DESC_H
#define CENG_BLEND_STATE_DESC_H

#include "boolean.h"

namespace Ceng
{
	namespace ColorBlendFactor
	{
		enum value
		{
			// blend factor = (0,0,0,0)
			zero = 1,

			// blend factor = (1,1,1,1)
			one = 2 ,

			// blend factor = (sourceA, sourceB, sourceG, sourceR)
			source_color = 3 ,

			// blend factor = (1 - sourceA, 1 - sourceB, 1 - sourceG, 1 - sourceR)
			invert_source_color = 4 ,

			// blend factor = (sourceA, sourceA, sourceA, sourceA)
			source_alpha = 5 ,

			// blend factor = (1 - sourceA, 1 - sourceA, 1 - sourceA, 1 - sourceA)
			invert_source_alpha = 6 ,

			// blend factor = (destA, destA, destA, destA)
			dest_alpha = 7 ,

			// blend factor = (1 - destA, 1 - destA, 1 - destA, 1 - destA)
			invert_dest_alpha = 8 ,

			// blend factor = (destA, destB, destG, destR)
			dest_color = 9 ,

			// blend factor = (1 - destA, 1 - destB, 1 - destG, 1 - destR)
			invert_dest_color = 10  ,

			// blend factor = (1, f, f, f), f = min(sourceA, 1 - destA). Data clamped to [0,1]
			source_alpha_saturate = 11 ,

			// blend factor set via API function SetBlendState()
			blend_factor = 12 ,

			// blend factor set via API function SetBlendState(), but inverted 1-x.
			invert_blend_factor = 13 ,

			// blend factor = (secA, secB, secG, secR)
			second_source_color = 14,

			// blend factor = (1 - secA, 1 - secB, 1 - secG, 1 - secR)
			invert_second_source_color = 15,

			// blend factor = (secA, secA, secA, secA)
			second_source_alpha = 16,

			// blend factor = (1 - secA, 1 - secA, 1 - secA, 1 - secA)
			invert_second_source_alpha = 17,
		};
	}

	namespace AlphaBlendFactor
	{
		enum value
		{
			// blend factor = (0,0,0,0)
			zero = 1,

			// blend factor = (1,1,1,1)
			one = 2,

			// blend factor = (sourceA, sourceA, sourceA, sourceA)
			source_alpha = 3,

			// blend factor = (1 - sourceA, 1 - sourceA, 1 - sourceA, 1 - sourceA)
			invert_source_alpha = 4,

			// blend factor = (destA, destA, destA, destA)
			dest_alpha = 5,

			// blend factor = (1 - destA, 1 - destA, 1 - destA, 1 - destA)
			invert_dest_alpha = 6,

			// blend factor = (1, f, f, f), f = min(sourceA, 1 - destA). Data clamped to [0,1]
			source_alpha_saturate = 7,

			// blend factor set via API function SetBlendState()
			blend_factor = 8,

			// blend factor set via API function SetBlendState(), but inverted 1-x.
			invert_blend_factor = 9,

			// blend factor = (secA, secA, secA, secA)
			second_source_alpha = 10,

			// blend factor = (1 - secA, 1 - secA, 1 - secA, 1 - secA)
			invert_second_source_alpha = 11,
		};
	}

	namespace BlendOp
	{
		enum value
		{
			// source1 + source2
			add = 1 ,

			// source1 - source2
			subtract = 2 ,

			// source2 - source1
			reverse_subtract = 3 ,

			// min(source1,source2). Invalid when using second source blend modes.
			min = 4 ,

			// max(source1, source2). Invalid when using second source blend modes.
			max = 5 ,
		};
	}

	namespace ColorWriteMask
	{
		enum value
		{
			red = 1,
			green = 2,
			blue = 4,
			alpha = 8,
			all = red | green | blue | alpha,
		};
	}

	class RenderTargetBlendDesc
	{
	public:
		Ceng::BOOL blendEnable;
		
		/**
		 * Operation done on the color value written by pixel shader.
		 */
		Ceng::ColorBlendFactor::value sourceBlend;

		/**
		 * Operation done on the color value read from render target.
		 */
		Ceng::ColorBlendFactor::value destBlend;

		/**
		 * How to combine source color and destination color.
		 */
		Ceng::BlendOp::value blendOp;

		/**
		 * Operation done on the alpha value written by pixel shader.
		 */
		Ceng::AlphaBlendFactor::value sourceBlendAlpha;

		/**
		* Operation done on the alpha value read from render target.
		*/
		Ceng::AlphaBlendFactor::value destBlendAlpha;

		/**
		* How to combine source alpha and destination alpha.
		*/
		Ceng::BlendOp::value blendAlphaOp;

		// Combination of ColorWriteMask flags
		Ceng::UINT8 writeMask;
	};

	class BlendStateDesc
	{
	public:

		/**
		 * Enabled alpha to coverage multisampling technique.
		 */
		Ceng::BOOL alphaToCoverage;

		/**
		 * Enables independent blend mode for each render target.
		 */
		Ceng::BOOL independentBlend;

		Ceng::UINT32 targets;
		RenderTargetBlendDesc *descList;
	};
	
}

#endif