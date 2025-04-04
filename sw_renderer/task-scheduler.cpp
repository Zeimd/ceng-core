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

std::shared_ptr<Experimental::RenderTask> SchedulerTask::GetTask()
{
	Ceng::UINT32 maxThreads = pipeline->renderThreads.size()-1;

	if (maxThreads < 1)
	{
		maxThreads = 1;
	}

	// TODO: cap number of threads that can execute tasks from pixel shader simultaneously

	std::shared_ptr<Experimental::RenderTask> task = nullptr;

	for (int k = 0; k < pipeline->pixelShader.buckets.size(); k++)
	{
		auto& bucket = pipeline->pixelShader.buckets[k];

		// Remove unused placeholder futures from queue

		while (bucket.queue.IsEmpty() == false)
		{
			auto& front = bucket.queue.Front();

			if (front.task == nullptr)
			{
				bucket.queue.PopFront();
				continue;
			}

			break;
		}

		if (bucket.queue.IsEmpty())
		{
			continue;
		}

		auto& front = bucket.queue.Front();

		if (front.IsReady() == false)
		{
			continue;
		}

		std::shared_ptr<Experimental::RenderTask> task = front.task;

		pipeline->pixelShader.buckets[k].queue.PopFront();

		return task;
	}

	for (int k = 0; k < pipeline->rasterizer.buckets.size(); k++)
	{
		auto& bucket = pipeline->rasterizer.buckets[k];

		// Remove unused placeholder futures from queue

		while (bucket.queue.IsEmpty() == false)
		{
			auto& front = bucket.queue.Front();

			if (front.task == nullptr)
			{
				bucket.queue.PopFront();
				continue;
			}

			break;
		}

		if (bucket.queue.IsEmpty())
		{
			continue;
		}

		auto& front = bucket.queue.Front();

		if (front.IsReady() == false)
		{
			continue;
		}

		// Check that there is enough space for future in every pixel shader bucket queue

		bool valid = true;

		for (int j = 0; j < pipeline->pixelShader.buckets.size(); j++)
		{
			if (pipeline->pixelShader.buckets[j].queue.IsFull())
			{
				valid = false;
				break;
			}
		}

		if (valid == false)
		{
			continue;
		}

		// Allocate futures from queues

		auto& task = front.task;

		for (int j = 0; j < pipeline->pixelShader.buckets.size(); j++)
		{
			std::shared_ptr<Experimental::Task_PixelShader> output = std::make_shared<Experimental::Task_PixelShader>();

			Experimental::Future<Experimental::Task_PixelShader> future(output);

			pipeline->pixelShader.buckets[j].queue.PushBack(future);

			Experimental::Future<Experimental::Task_PixelShader>* ptr;

			pipeline->pixelShader.buckets[j].queue.FrontPtr(&ptr);

			task->futures.push_back(ptr);
		}

		bucket.queue.PopFront();

		return task;
	}

	auto& queue = pipeline->triangleSetup.queue;

	if (queue.IsEmpty() == false)
	{
		auto& front = queue.Front();

		if (front.IsReady() == true)
		{
			// Check that there is enough space for future in every pixel shader bucket queue

			bool valid = true;

			for (int j = 0; j < pipeline->rasterizer.buckets.size(); j++)
			{
				if (pipeline->rasterizer.buckets[j].queue.IsFull())
				{
					valid = false;
					break;
				}
			}

			if (valid)
			{
				// Allocate futures from queues

				auto& task = front.task;

				for (int j = 0; j < pipeline->rasterizer.buckets.size(); j++)
				{
					std::shared_ptr<Experimental::Task_Rasterizer> output = std::make_shared<Experimental::Task_Rasterizer>();

					Experimental::Future<Experimental::Task_Rasterizer> future(output);

					pipeline->rasterizer.buckets[j].queue.PushBack(future);

					Experimental::Future<Experimental::Task_Rasterizer>* ptr;

					pipeline->rasterizer.buckets[j].queue.FrontPtr(&ptr);

					task->futures.push_back(ptr);
				}

				queue.PopFront();

				return task;
			}
		}
	}
	

	return task;

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

			std::shared_ptr<Experimental::RenderTask> task = GetTask();

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