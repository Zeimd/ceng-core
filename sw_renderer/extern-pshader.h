#pragma once

#ifndef CENG_SWR_EXTERN_PSHADER_H
#define CENG_SWR_EXTERN_PSHADER_H

#include <memory>
#include <vector>

#include "cr-pixel-shader.h"

namespace Ceng
{
	class CR_NewTargetData;

	class PixelShaderDescriptor;

	class PixelShaderContext;

	struct CR_QuadHeader;

	class ExternalPixelShader : public CR_PixelShader
	{
	public:

		// Pointer to externally controlled descriptor
		PixelShaderDescriptor* desc;

	public:
		ExternalPixelShader();

		static CRESULT Create(PixelShaderDescriptor* desc, ExternalPixelShader** out);

		~ExternalPixelShader() override;

	public:

		CRESULT GetInstances(std::vector<std::shared_ptr<PixelShaderContext>>& instances,
			const Ceng::UINT32 renderThreads) override;

	};
}

#endif