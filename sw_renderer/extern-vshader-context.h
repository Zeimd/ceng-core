#pragma once

#ifndef CENG_SWRENDER_EXTERN_VSHADER_CONTEXT_H
#define CENG_SWRENDER_EXTERN_VSHADER_CONTEXT_H

#include "vshader-context.h"

namespace Ceng
{
	class VertexShaderInstance;
	class VertexShaderInstanceCommon;

	class ExternalVertexShaderContext : public VertexShaderContext
	{
	public:

		VertexShaderInstance* instance;

	public:

		ExternalVertexShaderContext(VertexShaderInstance* instance, std::shared_ptr<VertexShaderInstanceCommon>& common);

		~ExternalVertexShaderContext() override;

		CRESULT Configure() override;

		CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
			LockingStage* outputQueue) override;

		CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch, Ceng::UINT32 threadId,
			Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future) override;

	};
}

#endif