/*****************************************************************************
*
* rtarget-data.cpp
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#include <ceng/datatypes/bufferdata-2d.h>

#include "buffer-clear.h"
#include "rtarget-data.h"

#include "CombinedBlendState.h"
#include "cr-blend-state.h"

#include "Writer_unbyte_argb.h"

using namespace Ceng;

CR_NewTargetData::CR_NewTargetData()
{
	baseAddress = NULL;
	
	bytesPerPixel = 0;
	tileYstep = 0;
	tileXstep = 0;

	memset(channels,0,4*sizeof(CR_ChannelData));

	shaderSemantic = 0;
	bufferFormat = Ceng::IMAGE_FORMAT::UNKNOWN;

	dataLayout = Ceng::BUFFER_LAYOUT::AOS;
	tilingMode = Ceng::BUFFER_TILING::SCANLINES;

	//clear_bufferBlock = &Ceng::CLEAR_BUFFER_BLOCK;
	clear_bufferBlock = &Ceng::CLEAR_BUFFER_BLOCK_X86_SSE;
}

CR_NewTargetData::~CR_NewTargetData()
{
	if (baseAddress != NULL)
	{
		AlignedFree((UINT8*)baseAddress);
		baseAddress = NULL;
	}
}

CRESULT CR_NewTargetData::ChangeWindowSize(const Ceng::UINT32 newWidth,
										   const Ceng::UINT32 newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;

	return CE_OK;
}

const CRESULT CR_NewTargetData::UpdateBucketAreas(const Ceng::UINT32 maxBucketCount,
												  const Ceng::UINT32 tileSize)
{
	if (maxBucketCount == 0)
	{
		return CE_ERR_INVALID_PARAM;
	}

	if (tileSize == 0)
	{
		return CE_ERR_INVALID_PARAM;
	}

	// Subdivision for multiple threads

	Ceng::UINT32 visRows = windowHeight / tileSize;

	Ceng::UINT32 buckets;

	buckets = maxBucketCount;
	if (visRows < maxBucketCount)
	{
		buckets = visRows;
	}

	Ceng::UINT32 threadRows = visRows / buckets;
	Ceng::UINT32 remainder = visRows % buckets;

	bucketAreas = std::vector<Rectangle>(buckets);

	Rectangle tempRect;

	tempRect.left = 0;
	tempRect.right = windowWidth-1;
	tempRect.top = 0;
	tempRect.bottom = windowHeight - 1;

	if (buckets > 2)
	{
		for (Ceng::UINT32 k = 0; k < buckets - 2; k++)
		{
			tempRect.top = k*threadRows*tileSize;
			tempRect.bottom = (k + 1)*threadRows*tileSize - 1;

			bucketAreas[k] = tempRect;
		}

		tempRect.top = tempRect.bottom + 1;
		tempRect.bottom = windowHeight - 1;
	}
		
	bucketAreas[buckets-1] = tempRect;

	return CE_OK;
}

CRESULT CR_NewTargetData::GetBufferData2D(Ceng::BufferData2D *destPtr)
{
	destPtr->width = windowWidth;
	destPtr->height = windowHeight;
	destPtr->format = bufferFormat;
	destPtr->bytesPerPixel = channels[0].bytesPerPixel;
	destPtr->pitchBytes = channels[0].tileYstep;
	destPtr->baseAddress = baseAddress;

	return CE_OK;
}

CRESULT CR_NewTargetData::SetDepthStencilState(const Ceng::DepthStencilDesc *state)
{
	memcpy(&dsTest,state,sizeof(Ceng::DepthStencilDesc));
	return CE_OK;
}

POINTER CR_NewTargetData::GetQuadAddress(const Ceng::UINT32 channel,
										 const Ceng::UINT32 x,const Ceng::UINT32 y) const
{
	POINTER temp = baseAddress + channels[channel].bufferOffset;

	switch(tilingMode)
	{
	case Ceng::BUFFER_TILING::SCANLINES:

		temp += x * channels[channel].unitXstep;
		temp += y * channels[channel].unitYstep;
		break;

	case Ceng::BUFFER_TILING::LQUADS:

		temp += (x>>1) * channels[channel].unitXstep;
		temp += (y>>1) * channels[channel].unitYstep;
		break;

	case Ceng::BUFFER_TILING::TILED8_LQUADS:

		temp += (x>>3) * channels[channel].tileXstep;
		
		temp += ((x&7)>>1) * channels[channel].unitXstep;

		temp += (y>>3) * channels[channel].tileYstep;

		temp += ((y&7)>>1) * channels[channel].unitYstep;

		break;
	};

	return temp;
}

POINTER CR_NewTargetData::GetQuadAddress(const Ceng::UINT32 tileSize,const Ceng::UINT32 channel,
										 const Ceng::UINT32 tileX,const Ceng::UINT32 tileY,
										 const Ceng::UINT32 quadX,const Ceng::UINT32 quadY) const
{
	POINTER temp = baseAddress;

	switch(tilingMode)
	{
	case BUFFER_TILING::SCANLINES:

		temp = baseAddress + channels[channel].bufferOffset;

		temp += ( (tileX<<3) + (quadX << 1)) * channels[channel].unitXstep;

		temp += ( (tileY<<3) + (quadY << 1)) * channels[channel].unitYstep;

		return temp;

		break;
	case BUFFER_TILING::LQUADS:

		temp = baseAddress + channels[channel].bufferOffset;

		temp += ((tileX<<2) + quadX) * channels[channel].unitXstep;

		temp += ((tileY<<2) + quadY) * channels[channel].unitYstep;

		return temp;

		break;
	case BUFFER_TILING::TILED8_LQUADS:

		temp = baseAddress + channels[channel].bufferOffset;

		temp += tileX * channels[channel].tileXstep + tileY * channels[channel].tileYstep;

		temp += quadX * channels[channel].unitXstep + quadY * channels[channel].unitYstep;

		return temp;

		break;

	case BUFFER_TILING::TILED16_LQUADS:

		return baseAddress;
		break;
	}

	return baseAddress;
}

POINTER CR_NewTargetData::GetTileAddress(const Ceng::UINT32 tileSize,const Ceng::UINT32 channel,
										 const Ceng::UINT32 tileX,const Ceng::UINT32 tileY) const
{
	POINTER temp;

	switch(tilingMode)
	{
	case BUFFER_TILING::SCANLINES:
		break;
	case BUFFER_TILING::LQUADS:
		break;
	case BUFFER_TILING::TILED8_LQUADS:

		temp = baseAddress + channels[channel].bufferOffset;

		temp += tileX * channels[channel].tileXstep + tileY * channels[channel].tileYstep;
		return temp;

		break;
	case BUFFER_TILING::TILED16_LQUADS:
		break;
	}

	return 0;
}

Pshader::PshaderTargetWriter* CR_NewTargetData::GetWriter(Ceng::UINT32 targetIndex, CombinedBlendState* blendState)
{
	Ceng::RenderTargetBlendDesc* activeBlend = &blendState->state->state.descList[0];

	if (blendState->state->state.independentBlend)
	{
		if (targetIndex < blendState->state->state.targets)
		{
			activeBlend = &blendState->state->state.descList[targetIndex];
		}		
	}

	switch (bufferFormat)
	{
	case IMAGE_FORMAT::D16:
		return nullptr;
	case IMAGE_FORMAT::D16_S8:
		return nullptr;
	case IMAGE_FORMAT::D16_S16:
		return nullptr;
	case IMAGE_FORMAT::D24_S8:
		return nullptr;
	case IMAGE_FORMAT::D24_S16:
		return nullptr;
	case IMAGE_FORMAT::D32F:
		return nullptr;
	case IMAGE_FORMAT::D32F_S8:
		return nullptr;
	case IMAGE_FORMAT::D32F_S16:
		return nullptr;
	case IMAGE_FORMAT::D32F_IW:
		return nullptr;
	case IMAGE_FORMAT::D32F_IW_S8:
		return nullptr;
	case IMAGE_FORMAT::D32F_IW_S16:
		return nullptr;
	case IMAGE_FORMAT::D32F_W:
		return nullptr;
	case IMAGE_FORMAT::D32F_W_S8:
		return nullptr;
	case IMAGE_FORMAT::D32F_W_S16:
		return nullptr;
	case IMAGE_FORMAT::D64F:
		return nullptr;
	case IMAGE_FORMAT::D64F_S8:
		return nullptr;
	case IMAGE_FORMAT::D64F_S16:
		return nullptr;
	case IMAGE_FORMAT::D64F_IW:
		return nullptr;
	case IMAGE_FORMAT::D64F_IW_S8:
		return nullptr;
	case IMAGE_FORMAT::D64F_IW_S16:
		return nullptr;
	case IMAGE_FORMAT::D64F_W:
		return nullptr;
	case IMAGE_FORMAT::D64F_W_S8:
		return nullptr;
	case IMAGE_FORMAT::D64F_W_S16:
		return nullptr;			
	case IMAGE_FORMAT::s8:		
		return nullptr;
	case IMAGE_FORMAT::s16:
		return nullptr;
	case IMAGE_FORMAT::D32:
		return nullptr;
	case IMAGE_FORMAT::D15_S1:
		return nullptr;
	case IMAGE_FORMAT::D24_X8:
		return nullptr;
	case IMAGE_FORMAT::D24_X4_S4:
		return nullptr;
	case IMAGE_FORMAT::D24F_S8:
		return nullptr;
	case IMAGE_FORMAT::unorm_r8:
		return nullptr;
	case IMAGE_FORMAT::uint_r8:
		return nullptr;
	case IMAGE_FORMAT::int_r8:
		return nullptr;
	case IMAGE_FORMAT::unorm_r16:
		return nullptr;
	case IMAGE_FORMAT::uint_r16:
		return nullptr;
	case IMAGE_FORMAT::int_r16:
		return nullptr;
	case IMAGE_FORMAT::fp32_r:
		return nullptr;
	case IMAGE_FORMAT::fp16_r:
		return nullptr;
	case IMAGE_FORMAT::fp16_gray:
		return nullptr;
	case IMAGE_FORMAT::gray_8:
		return nullptr;
	case IMAGE_FORMAT::gray_16:
		return nullptr;
	case IMAGE_FORMAT::gray_24:
		return nullptr;
	case IMAGE_FORMAT::gray_32:
		return nullptr;
	case IMAGE_FORMAT::alpha_8:
		return nullptr;
	case IMAGE_FORMAT::unorm_r8_g8:
		return nullptr;
	case IMAGE_FORMAT::uint_r8_g8:
		return nullptr;
	case IMAGE_FORMAT::int_r8_g8:
		return nullptr;
	case IMAGE_FORMAT::unorm_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::uint_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::int_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::unorm_r16_g16:
		return nullptr;
	case IMAGE_FORMAT::uint_r16_g16:
		return nullptr;
	case IMAGE_FORMAT::int_r16_g16:
		return nullptr;
	case IMAGE_FORMAT::unorm_g16_r16:
		return nullptr;
	case IMAGE_FORMAT::uint_g16_r16:
		return nullptr;
	case IMAGE_FORMAT::int_g16_r16:
		return nullptr;
	case IMAGE_FORMAT::fp32_gr:
		return nullptr;
	case IMAGE_FORMAT::fp32_rg:
		return nullptr;
	case IMAGE_FORMAT::fp16_gr:
		return nullptr;
	case IMAGE_FORMAT::fp16_rg:
		return nullptr;
	case IMAGE_FORMAT::unorm_r8_g8_b8:
		return nullptr;
	case IMAGE_FORMAT::uint_r8_g8_b8:
		return nullptr;
	case IMAGE_FORMAT::int_r8_g8_b8:
		return nullptr;
	case IMAGE_FORMAT::unorm_b8_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::uint_b8_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::int_b8_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::unorm_b32_g32_r32:
		return nullptr;
	case IMAGE_FORMAT::fp32_bgr:
		return nullptr;
	case IMAGE_FORMAT::fp32_rgb:
		return nullptr;
	case IMAGE_FORMAT::unorm_a8_r8_g8_b8:

		if (activeBlend->blendEnable == false)
		{
			return new Writer_unbyte_argb_noblend();
		}
		else
		{
			return new Writer_unbyte_argb(*activeBlend, blendState->factors);
		}

		break;
		
	case IMAGE_FORMAT::uint_a8_r8_g8_b8:
		return nullptr;
	case IMAGE_FORMAT::int_a8_r8_g8_b8:
		return nullptr;
	case IMAGE_FORMAT::unorm_a8_b8_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::uint_a8_b8_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::int_a8_b8_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::unorm_a16_b16_g16_r16:
		return nullptr;
	case IMAGE_FORMAT::uint_a16_b16_g16_r16:
		return nullptr;
	case IMAGE_FORMAT::int_a16_b16_g16_r16:
		return nullptr;
	case IMAGE_FORMAT::unorm_a16_r16_g16_b16:
		return nullptr;
	case IMAGE_FORMAT::unorm_a32_b32_g32_r32:
		return nullptr;
	case IMAGE_FORMAT::fp32_abgr:
		return nullptr;
	case IMAGE_FORMAT::fp32_argb:
		return nullptr;
	case IMAGE_FORMAT::fp16_abgr:
		return nullptr;
	case IMAGE_FORMAT::fp16_argb:
		return nullptr;
	case IMAGE_FORMAT::unorm_r5_g6_b5:
		return nullptr;
	case IMAGE_FORMAT::unorm_b5_g6_r5:
		return nullptr;
	case IMAGE_FORMAT::unorm_a1_r5_g5_b5:
		return nullptr;
	case IMAGE_FORMAT::unorm_a1_b5_g5_r5:
		return nullptr;
	case IMAGE_FORMAT::unorm_a2_r10_g10_b10:
		return nullptr;
	case IMAGE_FORMAT::unorm_a2_b10_g10_r10:
		return nullptr;
	case IMAGE_FORMAT::unorm_r3_g3_b2:
		return nullptr;
	case IMAGE_FORMAT::unorm_b2_g3_r3:
		return nullptr;
	case IMAGE_FORMAT::unorm_x8_r8_g8_b8:
		return nullptr;
	case IMAGE_FORMAT::unorm_x8_b8_g8_r8:
		return nullptr;
	case IMAGE_FORMAT::unorm_x1_r5_g5_b5:
		return nullptr;
	case IMAGE_FORMAT::unorm_a4_r4_g4_b4:
		return nullptr;
	case IMAGE_FORMAT::unorm_a4_b4_g4_r4:
		return nullptr;
	case IMAGE_FORMAT::unorm_x4_r4_g4_b4:
		return nullptr;
	case IMAGE_FORMAT::unorm_x4_b4_g4_r4:
		return nullptr;
	case IMAGE_FORMAT::unorm_a8_r3_g3_b2:
		return nullptr;
	case IMAGE_FORMAT::unorm_a8_b2_g3_r3:
		return nullptr;

	case IMAGE_FORMAT::dxt1:
		return nullptr;
	case IMAGE_FORMAT::dxt2:
		return nullptr;
	case IMAGE_FORMAT::dxt3:
		return nullptr;
	case IMAGE_FORMAT::dxt4:
		return nullptr;
	case IMAGE_FORMAT::dxt5:
		return nullptr;

	case IMAGE_FORMAT::normal_3dc:
		return nullptr;

	case IMAGE_FORMAT::bc7_rgba_unorm:
		return nullptr;
	case IMAGE_FORMAT::bc7_srgb_alpha_unorm:
		return nullptr;

	case IMAGE_FORMAT::bc6_rgb_float:
		return nullptr;
	case IMAGE_FORMAT::bc6_rgb_unsigned_float:
		return nullptr;

	case IMAGE_FORMAT::etc2_rgb8:
		return nullptr;
	case IMAGE_FORMAT::etc2_srgb8:
		return nullptr;

	case IMAGE_FORMAT::etc2_rgb8_a1:
		return nullptr;
	case IMAGE_FORMAT::etc2_srgb8_a1:
		return nullptr;

	case IMAGE_FORMAT::etc2_rgba8:
		return nullptr;
	case IMAGE_FORMAT::etc2_srgb8_a8:
		return nullptr;

	case IMAGE_FORMAT::eac_r11_unsigned:
		return nullptr;
	case IMAGE_FORMAT::eac_r11_signed:
		return nullptr;

	case IMAGE_FORMAT::eac_rg11_unsigned:
		return nullptr;
	case IMAGE_FORMAT::eac_rg11_signed:
		return nullptr;

	case IMAGE_FORMAT::etc1_rgb:
		return nullptr;

	case IMAGE_FORMAT::bc5_rg_unorm:
		return nullptr;
	case IMAGE_FORMAT::bc5_rg_snorm:
		return nullptr;

	case IMAGE_FORMAT::bc4_r_unorm:
		return nullptr;
	case IMAGE_FORMAT::bc4_r_snorm:
		return nullptr;
	}

	return nullptr;
}