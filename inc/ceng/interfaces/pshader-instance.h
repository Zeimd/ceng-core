#pragma once

#ifndef CENG_PSHADER_INSTANCE_H
#define CENG_PSHADER_INSTANCE_H

#include "../datatypes/return-val.h"

#include "base-interface.h"

#include "../datatypes/pshader-input-desc.h"
#include "../datatypes/pshader-output-desc.h"

namespace Ceng
{
	class QuadData;

	class PixelShaderInstance : public BASE_INTERFACE
	{
	protected:

		~PixelShaderInstance() override
		{

		}

	public:

		virtual CRESULT ConfigureInput(PixelShaderInputDesc* inputs, Ceng::UINT32 amount) = 0;

		virtual CRESULT ConfigureOutput(PixelShaderOutputDesc* outputs, Ceng::UINT32 amount) = 0;

		virtual CRESULT ConfigureLocals() = 0;

		virtual CRESULT SetFragmentFormat(const PixelShaderInputDesc* inputs, Ceng::UINT32 inputAmount,
			const PixelShaderOutputDesc* outputs, Ceng::UINT32 outputAmount) = 0;

		virtual CRESULT SetRenderTargets(const PixelShaderOutputDesc* outputs, Ceng::UINT32 amount) = 0;

		virtual CRESULT ProcessQuads(QuadData* quads, Ceng::UINT32 amount) = 0;
	};
}

#endif