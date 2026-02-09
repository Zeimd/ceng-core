#pragma once

#ifndef SWRENDER_COMBINED_BLEND_STATE_H
#define SWRENDER_COMBINED_BLEND_STATE_H

#include <array>

namespace Ceng
{
	class CR_BlendState;

	struct CombinedBlendState
	{
		CR_BlendState* state;
		std::array<Ceng::FLOAT32, 4> factors;
		Ceng::UINT32 sampleMask;
	};
}

#endif