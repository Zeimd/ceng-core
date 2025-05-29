#pragma once

#ifndef CENG_SWR_INTERNAL_PSHADER_H
#define CENG_SWR_INTERNAL_PSHADER_H

#include "cr-pixel-shader.h"

namespace Ceng
{
	class InternalPixelShader : public CR_PixelShader
	{
	public:

		InternalPixelShader()
			: CR_PixelShader()
		{

		}

		~InternalPixelShader() override
		{

		}

		CRESULT GetInstances(std::vector<std::shared_ptr<PixelShaderContext>>& instances,
			const Ceng::UINT32 renderThreads) override;
	};
}

#endif