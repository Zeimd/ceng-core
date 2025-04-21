#pragma once

#ifndef CENG_SWR_TASK_VSHADER_H
#define CENG_SWR_TASK_VSHADER_H

#include <memory>

#include "SimpleStage.h"

#include "render-task.h"

#include "draw-batch.h"

#include "future.h"

namespace Ceng
{
	class Task_Clipper;

	class Task_VertexShader : public Experimental::RenderTask
	{
	protected:

		std::shared_ptr<DrawBatch> batch;

		Task_VertexShader();
	public:

		Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future;

		Task_VertexShader(std::shared_ptr<DrawBatch>& batch);

		~Task_VertexShader() override;

		const CRESULT Prepare(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
		const CRESULT Execute(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
	};
}

#endif