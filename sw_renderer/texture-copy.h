#ifndef CENG_SWRENDER_TEXTURE_COPY_H
#define CENG_SWRENDER_TEXTURE_COPY_H

#include "rtarget-data.h"
#include <ceng/datatypes/sub-resource-data.h>
#include <ceng/datatypes/return-val.h>

namespace Ceng
{
	const CRESULT To_unorm_a8_r8_g8_b8(CR_NewTargetData* texture, const SubResourceData* sourceData,
		const Ceng::IMAGE_FORMAT::value sourceFormat);

	const CRESULT To_unorm_a8_b8_g8_r8(CR_NewTargetData* texture, const SubResourceData* sourceData,
		const Ceng::IMAGE_FORMAT::value sourceFormat);

	// Swap 32-bit color, 8 bit per channel. Swap red and blue.
	const CRESULT C32_ARGB_To_ABGR(CR_NewTargetData* texture, const SubResourceData* sourceData,
		const Ceng::IMAGE_FORMAT::value sourceFormat);

	// Convert X channel to alpha.
	const CRESULT C32_XRGB_To_ARGB(CR_NewTargetData* texture, const SubResourceData* sourceData,
		const Ceng::IMAGE_FORMAT::value sourceFormat);

	// Convert X channel to alpha. Swap red and blue.
	const CRESULT C32_XBGR_To_ARGB(CR_NewTargetData* texture, const SubResourceData* sourceData,
		const Ceng::IMAGE_FORMAT::value sourceFormat);

	// Add alpha channel to highest byte
	const CRESULT C32_RGB_To_ARGB(CR_NewTargetData* texture, const SubResourceData* sourceData,
		const Ceng::IMAGE_FORMAT::value sourceFormat);

	// Add alpha channel to highest byte, swap red and blue channels
	const CRESULT C32_RGB_To_ABGR(CR_NewTargetData* texture, const SubResourceData* sourceData,
		const Ceng::IMAGE_FORMAT::value sourceFormat);

}

#endif