#ifndef CR_TARGET_TEX_2D_H
#define CR_TARGET_TEX_2D_H

#include <memory>

#include "cr-rendertargetview.h"

#include "rtarget-data.h"

namespace Ceng
{
	class CR_Texture2D;

	class CR_TargetTexture2D : public CR_RenderTargetView
	{
	public:

		std::shared_ptr<CR_NewTargetData> bufferObject;

	public:
		CR_TargetTexture2D();

		~CR_TargetTexture2D() override;

		void Release() override;

		std::shared_ptr<CR_NewTargetData> GetTargetData() override;

		CR_NewTargetData* GetDataPtr() override;
	};
}

#endif