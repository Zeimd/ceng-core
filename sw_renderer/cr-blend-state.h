#pragma once

#ifndef CR_BLEND_STATE_H
#define CR_BLEND_STATE_H

#include <vector>

#include <ceng/datatypes/blend-state-desc.h>

#include <ceng/interfaces/blend-state.h>

namespace Ceng
{
	class CR_BlendState : public BlendState
	{
	public:

		BlendStateDesc state;

	protected:

		std::vector< RenderTargetBlendDesc > targetState;

		~CR_BlendState() override;

	public:
		CR_BlendState(const BlendStateDesc& source);

		void Release() override;
	};
}

#endif