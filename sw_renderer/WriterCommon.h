#pragma once

#ifndef SWRENDER_WRITER_COMMON_H
#define SWRENDER_WRITER_COMMON_H

#include <ceng/datatypes/basic-types.h>

namespace Ceng
{
	const FLOAT32 colorScale8 = FLOAT32(255.0f);

	const FLOAT32 inverseColorScale8 = FLOAT32(1.0f / 255.0f);

	extern _declspec(align(64)) const Ceng::INT8 coverageTable8[16][4]; 

	extern _declspec(align(64)) const Ceng::INT8 blendWriteMaskTable8_abgr_soa[16][4][4];
}

#endif