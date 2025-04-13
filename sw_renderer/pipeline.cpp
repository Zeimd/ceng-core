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

#include "task-clipper.h"
#include "task-rasterizer.h"
#include "task-triangle-setup.h"

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
	totalTasksCompleted.store(0);
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

	scheduler->Resume();
}

void Experimental::Pipeline::PauseThreads()
{
	for (Ceng::UINT32 k = 0; k < renderThreads.size(); k++)
	{
		renderThreads[k].thread->Pause();
	}

	scheduler->Pause();
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

	clipper = SimpleStage<Experimental::Task_Clipper>(64, cacheLineSize, this);

	triangleSetup = SimpleGroupingStage<Experimental::Task_TriangleSetup>(64, cacheLineSize, this);

	pixelShader = BucketStage<Experimental::Task_PixelShader>(maxThreads * maxScreenBuckets, 64, cacheLineSize, this);

	rasterizer = BucketStage<Experimental::Task_Rasterizer>(maxScreenBuckets, 64, cacheLineSize, this);

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

std::shared_ptr<Experimental::RenderTask>  Experimental::Pipeline::GetTask(Ceng::UINT32 threadId)
{
	Ceng::UINT32 maxThreads = renderThreads.size() - 1;

	if (maxThreads < 1)
	{
		maxThreads = 1;
	}

	// TODO: cap number of threads that can execute tasks from pixel shader simultaneously

	for (int k = 0; k < pixelShader.buckets.size(); k++)
	{
		auto& bucket = pixelShader.buckets[k];

		bucket.PopDiscardedTasks();

		if (bucket.queue.IsEmpty())
		{
			continue;
		}

		auto& front = bucket.queue.Front();

		if (front.IsReady() == false)
		{
			continue;
		}

		if (bucket.Unlock(threadId) == false)
		{
			continue;
		}

		bucket.Lock(threadId);

		std::shared_ptr<Experimental::RenderTask> task = front.result;

		task->bucketCompletedTasks = &bucket.completedTasks;

		bucket.queue.PopFront();

		PendingToRunning();

		return task;
	}

	for (int k = 0; k < rasterizer.buckets.size(); k++)
	{
		auto& bucket = rasterizer.buckets[k];

		bucket.PopDiscardedTasks();

		if (bucket.queue.IsEmpty())
		{
			continue;
		}

		auto& front = bucket.queue.Front();

		if (front.IsReady() == false)
		{
			continue;
		}

		if (bucket.Unlock(threadId) == false)
		{
			continue;
		}

		if (pixelShader.CheckSpaceAll() == false)
		{
			continue;
		}

		bucket.Lock(threadId);

		std::shared_ptr<Experimental::Task_Rasterizer> task = front.result;

		task->bucketCompletedTasks = &bucket.completedTasks;

		// Allocate futures from queues

		for (int j = 0; j < renderThreads.size(); j++)
		{
			Ceng::UINT32 bucket = renderThreads.size() * k + j;

			Experimental::Future<std::shared_ptr<Experimental::Task_PixelShader>> future;

			pixelShader.buckets[bucket].queue.PushBack(future);

			Experimental::Future<std::shared_ptr<Experimental::Task_PixelShader>>* ptr;

			pixelShader.buckets[bucket].queue.BackPtr(&ptr);

			task->futures.push_back(ptr);
		}

		AddPendingTasks(renderThreads.size());

		bucket.queue.PopFront();

		PendingToRunning();

		return task;
	}

	triangleSetup.PopDiscardedTasks();

	auto& triangleQueue = triangleSetup.queue;

	if (triangleQueue.IsEmpty() == false)
	{
		auto& front = triangleQueue.Front();

		if (front.IsReady() == true)
		{
			if (front.result.IsComplete())
			{
				triangleQueue.PopFront();
			}
			else
			{
				for (int k = 0; k < front.result.tasks.size(); k++)
				{
					auto& entry = front.result.tasks[k];

					if (entry.issued)
					{
						continue;
					}

					// Check that there is enough space for future in every rasterizer bucket queue

					if (rasterizer.CheckSpaceAll())
					{
						// Allocate futures from queues		

						std::shared_ptr<Experimental::Task_TriangleSetup> task = entry.task;

						for (int j = 0; j < rasterizer.buckets.size(); j++)
						{
							Experimental::Future<std::shared_ptr<Experimental::Task_Rasterizer>> future;

							rasterizer.buckets[j].queue.PushBack(future);

							Experimental::Future<std::shared_ptr<Experimental::Task_Rasterizer>>* ptr;

							rasterizer.buckets[j].queue.BackPtr(&ptr);

							task->futures.push_back(ptr);
						}

						AddPendingTasks(rasterizer.buckets.size());

						triangleQueue.PopFront();

						PendingToRunning();

						return task;
					}
				

				}
			}
		}
	}

	clipper.PopDiscardedTasks();

	auto& clipperQueue = clipper.queue;

	if (clipperQueue.IsEmpty() == false)
	{
		auto& front = clipperQueue.Front();

		if (front.IsReady() == true)
		{
			// Check that there is enough space for future in every pixel shader bucket queue

			if (triangleSetup.queue.IsFull() == false)
			{
				// Allocate futures from queues

				std::shared_ptr<Experimental::Task_Clipper> task = front.result;

				Experimental::SimpleGroupingStage<Experimental::Task_TriangleSetup>::ItemType future;

				triangleSetup.queue.PushBack(future);

				Experimental::SimpleGroupingStage<Experimental::Task_TriangleSetup>::ItemType* ptr;

				triangleSetup.queue.BackPtr(&ptr);

				task->future = ptr;

				AddPendingTasks(1);

				clipperQueue.PopFront();

				PendingToRunning();

				return task;
			}
		}
	}

	return nullptr;
}


bool Experimental::Pipeline::IsEmpty()
{
	return pendingTasks.load() == 0 && runningTasks.load() == 0;

	// old way. Can theoretically return zero also when pendingTasks = -runningTasks.
	//return (pendingTasks.load() + runningTasks.load() == 0);
}

void Experimental::Pipeline::WaitForEmpty()
{
	while (IsEmpty() == false)
	{

	}
}

void Experimental::Pipeline::ClearCounters()
{
	totalTasksCompleted = 0;

	pixelShader.totalTasksCompleted = 0;
	rasterizer.totalTasksCompleted = 0;
	triangleSetup.totalTasksCompleted = 0;
	clipper.totalTasksCompleted = 0;
}

void Experimental::Pipeline::AddPendingTasks(Ceng::UINT32 count)
{
	pendingTasks += count;
}

void Experimental::Pipeline::PendingToRunning()
{
	++runningTasks;
	--pendingTasks;	
}

void Experimental::Pipeline::PendingToRunning(Ceng::UINT32 count)
{
	runningTasks += count;
	pendingTasks -= count;	
}

void Experimental::Pipeline::CompleteTasks(Ceng::UINT32 count)
{
	runningTasks -= count;
}

void Experimental::Pipeline::DiscardPending()
{
	--pendingTasks;
}

void Experimental::Pipeline::DiscardPending(Ceng::UINT32 count)
{
	pendingTasks -= count;
}

