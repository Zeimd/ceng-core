#pragma once

#ifndef CENG_SWR_EXTERN_PSHADER_INSTANCE_H
#define CENG_SWR_EXTERN_PSHADER_INSTANCE_H

#include <ceng/interfaces/pshader-instance.h>

#include "pshader-context.h"

namespace Ceng
{
	class ExternalPixelShaderContext : public PixelShaderContext
	{
	public:

		PixelShaderInstance* instance;

	public:

		ExternalPixelShaderContext(PixelShaderInstance* instance, std::shared_ptr<PixelShaderContextCommon>& common);

		~ExternalPixelShaderContext() override;

		CRESULT Configure(std::vector<PixelShaderInputDesc>& inputSemantics,
			std::vector<PixelShaderOutputDesc>& renderTargets) override;

		CRESULT ProcessQuads(Task_PixelShader* batch, const Ceng::INT32 threadId) override;

		CRESULT ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId) override;
	};
}

#endif