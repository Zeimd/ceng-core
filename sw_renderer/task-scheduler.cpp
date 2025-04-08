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

void SchedulerTask::Release()
{
	delete this;
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

			std::shared_ptr<Experimental::RenderTask> task = pipeline->GetTask(k);

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