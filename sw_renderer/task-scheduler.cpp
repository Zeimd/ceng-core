#include <ceng/platform.h>

#include "task-scheduler.h"

#include "pipeline.h"
#include "render-thread.h"

#include "task-pshader.h"
#include "task-clipper.h"
#include "task-rasterizer.h"
#include "task-triangle-setup.h"

#include <ceng/datatypes/condition-variable.h>
#include <ceng/datatypes/critical-section.h>

using namespace Ceng;

SchedulerTask::SchedulerTask(Experimental::Pipeline* pipeline, ConditionVariable* wakeCondition)
	: pipeline(pipeline), exitLoop(0), wakeCondition(wakeCondition)
{
	Ceng_CreateCriticalSection(&wakeCrit);
}

SchedulerTask::~SchedulerTask()
{
	if (wakeCrit != nullptr)
	{
		wakeCrit->Release();
	}	
}

std::shared_ptr<Experimental::RenderTask> SchedulerTask::GetTask(Ceng::UINT32 threadId)
{
	Ceng::UINT32 maxThreads = pipeline->renderThreads.size()-1;

	if (maxThreads < 1)
	{
		maxThreads = 1;
	}

	// TODO: cap number of threads that can execute tasks from pixel shader simultaneously

	for (int k = 0; k < pipeline->pixelShader.buckets.size(); k++)
	{
		auto& bucket = pipeline->pixelShader.buckets[k];

		bucket.PopEmptyTasks();

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

		std::shared_ptr<Experimental::RenderTask> task = front.task;

		task->bucketCompletedTasks = &bucket.completedTasks;

		pipeline->pixelShader.buckets[k].queue.PopFront();

		return task;
	}

	for (int k = 0; k < pipeline->rasterizer.buckets.size(); k++)
	{
		auto& bucket = pipeline->rasterizer.buckets[k];

		bucket.PopEmptyTasks();

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

		if (pipeline->pixelShader.CheckSpaceAll() == false)
		{
			continue;
		}

		bucket.Lock(threadId);

		std::shared_ptr<Experimental::Task_Rasterizer> task = front.task;

		task->bucketCompletedTasks = &bucket.completedTasks;

		// Allocate futures from queues

		for (int j = 0; j < pipeline->pixelShader.buckets.size(); j++)
		{
			Experimental::Future<Experimental::Task_PixelShader> future(nullptr);

			pipeline->pixelShader.buckets[j].queue.PushBack(future);

			Experimental::Future<Experimental::Task_PixelShader>* ptr;

			pipeline->pixelShader.buckets[j].queue.FrontPtr(&ptr);

			task->futures.push_back(ptr);
		}

		bucket.queue.PopFront();

		return task;
	}

	auto& triangleQueue = pipeline->triangleSetup.queue;

	if (triangleQueue.IsEmpty() == false)
	{
		auto& front = triangleQueue.Front();

		if (front.IsReady() == true)
		{
			// Check that there is enough space for future in every rasterizer bucket queue

			bool valid = pipeline->rasterizer.CheckSpaceAll();

			if (valid)
			{
				// Allocate futures from queues

				auto& task = front.task;

				for (int j = 0; j < pipeline->rasterizer.buckets.size(); j++)
				{
					Experimental::Future<Experimental::Task_Rasterizer> future(nullptr);

					pipeline->rasterizer.buckets[j].queue.PushBack(future);

					Experimental::Future<Experimental::Task_Rasterizer>* ptr;

					pipeline->rasterizer.buckets[j].queue.FrontPtr(&ptr);

					task->futures.push_back(ptr);
				}

				triangleQueue.PopFront();

				return task;
			}
		}
	}

	auto& clipperQueue = pipeline->clipper.queue;

	if (clipperQueue.IsEmpty() == false)
	{
		auto& front = clipperQueue.Front();

		if (front.IsReady() == true)
		{
			// Check that there is enough space for future in every pixel shader bucket queue

			if (pipeline->triangleSetup.queue.IsFull() == false)
			{
				// Allocate futures from queues

				auto& task = front.task;

				Experimental::Future<Experimental::Task_TriangleSetup> future(nullptr);

				pipeline->triangleSetup.queue.PushBack(future);

				Experimental::Future<Experimental::Task_TriangleSetup>* ptr;

				pipeline->triangleSetup.queue.FrontPtr(&ptr);

				task->future = ptr;

				clipperQueue.PopFront();

				return task;
			}
		}
	}
	

	return nullptr;

}

const CRESULT SchedulerTask::Execute()
{
	wakeCrit->Lock();

	while (exitLoop == 0)
	{
		for (int k = 0; k < pipeline->renderThreads.size(); ++k)
		{
			if (pipeline->renderThreads[k].task->inputQueue.IsFull())
			{
				continue;
			}

			std::shared_ptr<Experimental::RenderTask> task = GetTask(k);

			if (task != nullptr)
			{
				pipeline->renderThreads[k].task->inputQueue.PushBack(task);
			}
		}

		// TODO: if no work
		//wakeCondition->Wait(wakeCrit);
	}

	wakeCrit->Unlock();

	return CE_OK;
}

const CRESULT SchedulerTask::Exit()
{
	exitLoop = 1;
	return CE_OK;
}