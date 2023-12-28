#ifndef CR_DEPTHSTENCIL_STATE_H
#define CR_DEPTHSTENCIL_STATE_H

#include <ceng/interfaces/depth-stencil-state.h>
#include <ceng/interfaces/depth-stencil-desc.h>

namespace Ceng
{
	class CR_DepthStencilState : public DepthStencilState
	{
	public:

		DepthStencilDesc desc;

	protected:
		~CR_DepthStencilState() override;

	public:



		CR_DepthStencilState(const DepthStencilDesc& desc);

		void Release() override;
	};
}

#endif