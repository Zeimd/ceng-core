/*****************************************************************************
*
* pipeline.cpp
*
* Created By Jari Korkala 9/10/2014
*
*****************************************************************************/

#include "pipeline.h"
#include "task-pshader.h"

#include <ceng/platform.h>

#include "render-thread.h"

using namespace Ceng;

Pipeline::Pipeline() : rendererHasWork(nullptr)
{
	runningThreadCount.store(0);
	minThreadCount.store(0);
	maxThreadCount.store(0);

	activeThreads.store(0);
	remainingTasks.store(0);
}

Pipeline::~Pipeline()
{
	for(Ceng::UINT32 k=0;k<renderThreads.size();k++)
	{
		renderThreads[k]->Exit();
	}

	minThreadCount.store(0);
	maxThreadCount.store(0);
	rendererHasWork->WakeAll();

	for(Ceng::UINT32 k=0;k<renderThreads.size();k++)
	{
		renderThreads[k]->Release();
		renderThreadTasks[k]->Release();
	}

	if (rendererHasWork != nullptr)
	{
		rendererHasWork->Release();
	}
}

void Pipeline::ResumeThreads()
{
	for(Ceng::UINT32 k=0;k<renderThreads.size();k++)
	{
		renderThreads[k]->Resume();
	}
}

void Pipeline::PauseThreads()
{
	for(Ceng::UINT32 k=0;k<renderThreads.size();k++)
	{
		renderThreads[k]->Pause();
	}
}

void Pipeline::WakeOneThread()
{
	rendererHasWork->WakeOne();
}

void Pipeline::WakeAllThreads()
{
	rendererHasWork->WakeAll();
}

const CRESULT Pipeline::Configure(const Ceng::UINT32 cacheLineSize,const Ceng::UINT32 maxScreenBuckets,
								  const Ceng::UINT32 maxThreads,std::shared_ptr<ConditionVariable> &cmdWake)
{
	remainingTasks.store(0);
	activeThreads.store(0);

	runningThreadCount.store(0);
	minThreadCount.store(0);
	maxThreadCount.store(0);

	drawQueue = RingBuffer<std::shared_ptr<DrawBatch>>::Allocate(32,cacheLineSize);

	vshaderOutQueue = RingBuffer<std::shared_ptr<DrawBatch>>::Allocate(32,cacheLineSize);

	clipper = std::move(LockingStage(1,64,this,cacheLineSize));

	triangleSetup = std::move(LockingStage(1,64,this,cacheLineSize));

	pixelShader = std::move(LockingStage(maxThreads*maxScreenBuckets, 64, this, cacheLineSize));

	rasterizer = std::move(LockingStage(maxScreenBuckets,64,this,cacheLineSize));

	// Signal for render threads that there is work to do
	Ceng_CreateConditionVar(&rendererHasWork);

	renderThreads = std::vector<Thread*>(maxThreads);
	renderThreadTasks = std::vector<ThreadTask*>(maxThreads);

	for(Ceng::UINT32 k=0;k<maxThreads;k++)
	{
		renderThreadTasks[k] = new RenderThread(k,rendererHasWork,cmdWake,
												&runningThreadCount,
												&minThreadCount,&maxThreadCount,this);

		Ceng::CRESULT cresult = Ceng_CreateThread(renderThreadTasks[k],true,&renderThreads[k]);
	}

	return CE_OK;
}

std::shared_ptr<RenderTask> Pipeline::GetTask(const Ceng::UINT32 threadId)
{
	CRESULT cresult;
	std::shared_ptr<RenderTask> task;

	cresult = Local_GetTask(threadId,task);

	if (task != nullptr)
	{
		++activeThreads;
		--remainingTasks;
	}

	return task;
}

const Ceng::CRESULT Pipeline::Local_GetTask(const Ceng::UINT32 threadId,
													std::shared_ptr<RenderTask> &out_task)
{
	CRESULT cresult;

	cresult = pixelShader.GetTask(threadId,this,out_task);

	if (out_task != nullptr) 
	{
		return cresult;
	}

	cresult = rasterizer.GetTask(threadId,this,out_task);

	if (out_task != nullptr) 
	{
		return cresult;
	}

	cresult = triangleSetup.GetTask(threadId,this,out_task);

	if (out_task != nullptr) 
	{
		return cresult;
	}

	cresult = clipper.GetTask(threadId,this,out_task);

	if (out_task != nullptr) 
	{
		return cresult;
	}

	return cresult;
}

//*****************************************************************************
// Experimental new pipeline

Experimental::Pipeline::Pipeline() : rendererHasWork(nullptr)
{
	runningThreadCount.store(0);
	minThreadCount.store(0);
	maxThreadCount.store(0);

	runningTasks.store(0);
	pendingTasks.store(0);
}

Experimental::Pipeline::~Pipeline()
{
	for (Ceng::UINT32 k = 0; k < renderThreads.size(); k++)
	{
		renderThreads[k].thread->Exit();
	}

	scheduler->Exit();

	minThreadCount.store(0);
	maxThreadCount.store(0);
	rendererHasWork->WakeAll();

	for (Ceng::UINT32 k = 0; k < renderThreads.size(); k++)
	{
		renderThreads[k].thread->Release();
		renderThreads[k].task->Release();
	}

	scheduler->Release();
	schedulerTask->Release();

	if (rendererHasWork != nullptr)
	{
		rendererHasWork->Release();
	}
}

void Experimental::Pipeline::ResumeThreads()
{
	for (Ceng::UINT32 k = 0; k < renderThreads.size(); k++)
	{
		renderThreads[k].thread->Resume();
	}
}

void Experimental::Pipeline::PauseThreads()
{
	for (Ceng::UINT32 k = 0; k < renderThreads.size(); k++)
	{
		renderThreads[k].thread->Pause();
	}
}

void Experimental::Pipeline::WakeOneThread()
{
	rendererHasWork->WakeOne();
}

void Experimental::Pipeline::WakeAllThreads()
{
	rendererHasWork->WakeAll();
}

const CRESULT Experimental::Pipeline::Configure(const Ceng::UINT32 cacheLineSize, const Ceng::UINT32 maxScreenBuckets,
	const Ceng::UINT32 maxThreads, std::shared_ptr<ConditionVariable>& cmdWake)
{
	pendingTasks.store(0);
	runningTasks.store(0);

	runningThreadCount.store(0);
	minThreadCount.store(0);
	maxThreadCount.store(0);

	drawQueue = RingBuffer<std::shared_ptr<DrawBatch>>::Allocate(32, cacheLineSize);

	vshaderOutQueue = RingBuffer<std::shared_ptr<DrawBatch>>::Allocate(32, cacheLineSize);

	clipper = SimpleStage<Experimental::Task_Clipper>(64, cacheLineSize);

	triangleSetup = SimpleStage<Experimental::Task_TriangleSetup>(64, cacheLineSize);

	pixelShader = BucketStage<Experimental::Task_PixelShader>(maxThreads * maxScreenBuckets, 64, cacheLineSize);

	rasterizer = BucketStage<Experimental::Task_Rasterizer>(maxScreenBuckets, 64, cacheLineSize);

	// Signal for render threads that there is work to do
	Ceng_CreateConditionVar(&rendererHasWork);

	renderThreads = std::vector<RenderThreadData>(maxThreads);

	for (Ceng::UINT32 k = 0; k < maxThreads; k++)
	{
		renderThreads[k].task = new Experimental::RenderThread(k, rendererHasWork, cmdWake,
			&runningThreadCount,
			&minThreadCount, &maxThreadCount, this, 2, cacheLineSize);

		Ceng::CRESULT cresult = Ceng_CreateThread(renderThreads[k].task, true, &renderThreads[k].thread);
	}

	schedulerTask = new SchedulerTask(this, rendererHasWork);

	Ceng::CRESULT cresult = Ceng_CreateThread(schedulerTask, true, &scheduler);

	return CE_OK;
}

/*
std::shared_ptr<RenderTask> Experimental::Pipeline::GetTask(const Ceng::UINT32 threadId)
{
	CRESULT cresult;
	std::shared_ptr<RenderTask> task;

	cresult = Local_GetTask(threadId, task);

	if (task != nullptr)
	{
		++activeThreads;
		--remainingTasks;
	}

	return task;
}
*/

/*
const Ceng::CRESULT Experimental::Pipeline::Local_GetTask(const Ceng::UINT32 threadId,
	std::shared_ptr<RenderTask>& out_task)
{
	CRESULT cresult;

	cresult = pixelShader.GetTask(threadId, this, out_task);

	if (out_task != nullptr)
	{
		return cresult;
	}

	cresult = rasterizer.GetTask(threadId, this, out_task);

	if (out_task != nullptr)
	{
		return cresult;
	}

	cresult = triangleSetup.GetTask(threadId, this, out_task);

	if (out_task != nullptr)
	{
		return cresult;
	}

	cresult = clipper.GetTask(threadId, this, out_task);

	if (out_task != nullptr)
	{
		return cresult;
	}

	return cresult;
}
*/