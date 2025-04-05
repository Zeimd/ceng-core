#pragma once

#ifndef CENG_SWR_TASK_SCHEDULER_H
#define CENG_SWR_TASK_SCHEDULER_H

#include <ceng/interfaces/thread-task.h>

namespace Ceng::Experimental
{
	class Pipeline;
	class RenderTask;
	
}

namespace Ceng
{	
	class ConditionVariable;
	class CriticalSection;

	class SchedulerTask : public ThreadTask
	{
	protected:

		~SchedulerTask() override;

	public:

		Experimental::Pipeline* pipeline;

		ConditionVariable* wakeCondition;

		CriticalSection* wakeCrit;

	public:

		volatile Ceng::INT32 exitLoop;

		SchedulerTask(Experimental::Pipeline* pipeline, ConditionVariable* wakeCondition);

		const CRESULT Execute() override;

		const CRESULT Exit() override;

		void Release() override;

	protected:

		std::shared_ptr<Experimental::RenderTask> GetTask(Ceng::UINT32 threadId);
		
	};
}

#endif