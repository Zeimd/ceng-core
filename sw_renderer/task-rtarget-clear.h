#pragma once

#ifndef CENG_SWR_TASK_RTARGET_CLEAR_H
#define CENG_SWR_TASK_RTARGET_CLEAR_H

#include "render-task.h"

#include "rtarget-data.h"

namespace Ceng
{
	class Task_RenderTargetClear : public Experimental::RenderTask
	{
	public:

		CR_NewTargetData* target;

		CE_Color& color;

		Rectangle* activeRect;

		Ceng::INT32 startY;
		Ceng::INT32 height;

	public:

		Task_RenderTargetClear(CR_NewTargetData* target, CE_Color& color, Rectangle* activeRect, Ceng::INT32 startY, Ceng::INT32 height);

		~Task_RenderTargetClear() override;

		const CRESULT Prepare(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
		const CRESULT Execute(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
	};
}

#endif