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

		std::vector< RenderTargetBlendDesc > targetState;

	protected:

		~CR_BlendState() override;

	public:
		CR_BlendState(const BlendStateDesc& source);

		void Release() override;
	};
}

#endif