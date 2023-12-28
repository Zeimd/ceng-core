#ifndef CR_RENDERTARGETVIEW_H
#define CR_RENDERTARGETVIEW_H

#include <memory>

#include <ceng/interfaces/render-target-view.h>

namespace Ceng
{
	class CR_NewTargetData;

	class CR_RenderTargetView : public RenderTargetView
	{
	public:
		CR_RenderTargetView()
		{
		}

		~CR_RenderTargetView() override
		{
		}

		virtual std::shared_ptr<CR_NewTargetData> GetTargetData() = 0;

		virtual CR_NewTargetData* GetDataPtr() = 0;
	};
}

#endif
