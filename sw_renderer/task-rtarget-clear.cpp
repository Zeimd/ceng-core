#include "task-rtarget-clear.h"

#include "pipeline.h"

using namespace Ceng;

Task_RenderTargetClear::Task_RenderTargetClear(CR_NewTargetData* target, const CE_Color& color, Rectangle* activeRect,
	Ceng::INT32 startY, Ceng::INT32 height)
	: target(target), color(color), activeRect(activeRect), startY(startY), height(height)
{

}

Task_RenderTargetClear::~Task_RenderTargetClear()
{

}

const CRESULT Task_RenderTargetClear::Prepare(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline)
{
	return CE_OK;
}

const CRESULT Task_RenderTargetClear::Execute(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline)
{
	CRESULT cresult = target->ClearTarget(color, activeRect, startY, height);

	--pipeline->pixelShader.numThreads;
	--pipeline->runningTasks;
	++pipeline->totalTasksCompleted;

	++pipeline->triangleSetup.totalTasksCompleted;

	return cresult;
}