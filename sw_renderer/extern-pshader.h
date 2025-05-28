#pragma once

#ifndef CENG_SWR_EXTERN_PSHADER_H
#define CENG_SWR_EXTERN_PSHADER_H

#include <memory>

#include <ceng/interfaces/pixel-shader.h>

#include <ceng/datatypes/pshader-input-desc.h>
#include <ceng/datatypes/pshader-output-desc.h>
#include <ceng/datatypes/shader-uniform-desc.h>

#include <ceng/interfaces/pshader-descriptor.h>

#include "crender-base.h"

#include "triangle-data.h"

#include "cr-shader-const.h"

#include "pshader-input.h"
#include "pshader-output.h"

#include "pshader-instance.h"

#include "pshader-wrapper.h"

#include "texture-unit.h"

#include "PixelShaderInstanceCommon.h"

#include "cr-pixel-shader.h"

namespace Ceng
{
	class CR_NewTargetData;

	struct CR_QuadHeader;

	class ExternalPixelShader : public CR_PixelShader
	{
	public:

		PixelShaderDescriptor* desc;

	protected:

		BOOL compiled;

	public:
		ExternalPixelShader();

		static CRESULT Create(PixelShaderDescriptor* desc, ExternalPixelShader** out);

		~ExternalPixelShader() override;

	public:

		CRESULT GetInstances(std::vector<std::shared_ptr<PixelShaderInstance>>& instances,
			const Ceng::UINT32 renderThreads) override;

	};
}

#endif