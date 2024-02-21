#include "texture-copy.h"

using namespace Ceng;

const CRESULT Ceng::To_unorm_a8_r8_g8_b8(CR_NewTargetData* texture, const SubResourceData* sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	switch (sourceFormat)
	{
	case IMAGE_FORMAT::unorm_r8_g8_b8:
		return C32_RGB_To_ARGB(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_b8_g8_r8:
		return C32_RGB_To_ABGR(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_a8_b8_g8_r8:
		return C32_ARGB_To_ABGR(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_x8_r8_g8_b8:
		return C32_XRGB_To_ARGB(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_x8_b8_g8_r8:
		return C32_XBGR_To_ARGB(texture, sourceData, sourceFormat);
	default:
		break;
	}

	return CE_ERR_INCOMPATIBLE_FORMAT;
}

const CRESULT Ceng::To_unorm_a8_b8_g8_r8(CR_NewTargetData* texture, const SubResourceData* sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	switch (sourceFormat)
	{
	case IMAGE_FORMAT::unorm_r8_g8_b8:
		return C32_RGB_To_ABGR(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_b8_g8_r8:
		return C32_RGB_To_ARGB(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_a8_r8_g8_b8:
		return C32_ARGB_To_ABGR(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_x8_r8_g8_b8:
		return C32_XBGR_To_ARGB(texture, sourceData, sourceFormat);
	case IMAGE_FORMAT::unorm_x8_b8_g8_r8:
		return C32_XRGB_To_ARGB(texture, sourceData, sourceFormat);
	default:
		break;
	}

	return CE_ERR_INCOMPATIBLE_FORMAT;
}

const CRESULT Ceng::C32_XRGB_To_ARGB(CR_NewTargetData* texture, const SubResourceData* sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	Ceng::UINT8* destAddress = (Ceng::UINT8*)texture->baseAddress;
	Ceng::UINT8* sourceAddress = (Ceng::UINT8*)sourceData->sourcePtr;

	Ceng::UINT32 rowBytes = sourceData->rowPitch;

	for (Ceng::UINT32 k = 0; k < texture->bufferHeight; ++k)
	{
		Ceng::UINT8* tempSource = sourceAddress;
		Ceng::UINT8* tempDest = destAddress;

		for (Ceng::UINT32 j = 0; j < texture->bufferWidth; ++j)
		{
			tempDest[0] = tempSource[0];
			tempDest[1] = tempSource[1];
			tempDest[2] = tempSource[2];
			tempDest[3] = 255;

			tempSource += 4;
			tempDest += texture->channels[0].bytesPerPixel;
		}

		destAddress += texture->channels[0].tileYstep;
		sourceAddress += rowBytes;
	}

	return Ceng::CE_OK;
}

const CRESULT Ceng::C32_XBGR_To_ARGB(CR_NewTargetData* texture, const SubResourceData* sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	Ceng::UINT8* destAddress = (Ceng::UINT8*)texture->baseAddress;
	Ceng::UINT8* sourceAddress = (Ceng::UINT8*)sourceData->sourcePtr;

	Ceng::UINT32 rowBytes = sourceData->rowPitch;

	for (Ceng::UINT32 k = 0; k < texture->bufferHeight; ++k)
	{
		Ceng::UINT8* tempSource = sourceAddress;
		Ceng::UINT8* tempDest = destAddress;

		for (Ceng::UINT32 j = 0; j < texture->bufferWidth; ++j)
		{
			tempDest[0] = tempSource[2];
			tempDest[1] = tempSource[1];
			tempDest[2] = tempSource[0];
			tempDest[3] = 255;

			tempSource += 4;
			tempDest += texture->channels[0].bytesPerPixel;
		}

		destAddress += texture->channels[0].tileYstep;
		sourceAddress += rowBytes;
	}

	return Ceng::CE_OK;
}

const CRESULT Ceng::C32_ARGB_To_ABGR(CR_NewTargetData* texture, const SubResourceData* sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	Ceng::UINT8* destAddress = (Ceng::UINT8*)texture->baseAddress;
	Ceng::UINT8* sourceAddress = (Ceng::UINT8*)sourceData->sourcePtr;

	Ceng::UINT32 rowBytes = sourceData->rowPitch;

	for (Ceng::UINT32 k = 0; k < texture->bufferHeight; ++k)
	{
		Ceng::UINT8* tempSource = sourceAddress;
		Ceng::UINT8* tempDest = destAddress;

		for (Ceng::UINT32 j = 0; j < texture->bufferWidth; ++j)
		{
			tempDest[0] = tempSource[2];
			tempDest[1] = tempSource[1];
			tempDest[2] = tempSource[0];
			tempDest[3] = tempSource[3];

			tempSource += 4;
			tempDest += texture->channels[0].bytesPerPixel;
		}

		destAddress += texture->channels[0].tileYstep;
		sourceAddress += rowBytes;
	}

	return Ceng::CE_OK;
}


const CRESULT Ceng::C32_RGB_To_ARGB(CR_NewTargetData* texture, const SubResourceData* sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	Ceng::UINT8* destAddress = (Ceng::UINT8*)texture->baseAddress;
	Ceng::UINT8* sourceAddress = (Ceng::UINT8*)sourceData->sourcePtr;

	Ceng::UINT32 rowBytes = sourceData->rowPitch;

	for (Ceng::UINT32 k = 0; k < texture->bufferHeight; ++k)
	{
		Ceng::UINT8* tempSource = sourceAddress;
		Ceng::UINT8* tempDest = destAddress;

		for (Ceng::UINT32 j = 0; j < texture->bufferWidth; ++j)
		{
			tempDest[0] = tempSource[0];
			tempDest[1] = tempSource[1];
			tempDest[2] = tempSource[2];
			tempDest[3] = 255;

			tempSource += 3;
			tempDest += texture->channels[0].bytesPerPixel;
		}

		destAddress += texture->channels[0].tileYstep;
		sourceAddress += rowBytes;
	}

	return CE_OK;
}

const CRESULT Ceng::C32_RGB_To_ABGR(CR_NewTargetData* texture, const SubResourceData* sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	Ceng::UINT8* destAddress = (Ceng::UINT8*)texture->baseAddress;
	Ceng::UINT8* sourceAddress = (Ceng::UINT8*)sourceData->sourcePtr;

	Ceng::UINT32 rowBytes = sourceData->rowPitch;

	for (Ceng::UINT32 k = 0; k < texture->bufferHeight; ++k)
	{
		Ceng::UINT8* tempSource = sourceAddress;
		Ceng::UINT8* tempDest = destAddress;

		for (Ceng::UINT32 j = 0; j < texture->bufferWidth; ++j)
		{
			tempDest[0] = tempSource[2];
			tempDest[1] = tempSource[1];
			tempDest[2] = tempSource[0];
			tempDest[3] = 255;

			tempSource += 3;
			tempDest += texture->channels[0].bytesPerPixel;
		}

		destAddress += texture->channels[0].tileYstep;
		sourceAddress += rowBytes;
	}

	return CE_OK;
}
