#pragma once

#ifndef CENG_SWR_TASK_SCHEDULER_H
#define CENG_SWR_TASK_SCHEDULER_H

#include <atomic>
#include <memory>

#include <ceng/interfaces/thread-task.h>
#include <ceng/datatypes/condition-variable.h>

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

		std::shared_ptr<ConditionVariable> cmdWake;

		std::atomic<Ceng::UINT32> waiting;

		std::atomic<Ceng::UINT32> totalWakeups;

	public:

		volatile Ceng::INT32 exitLoop;

		SchedulerTask(Experimental::Pipeline* pipeline, ConditionVariable* wakeCondition,
			std::shared_ptr<ConditionVariable>& cmdWake);

		const CRESULT Execute() override;

		const CRESULT Exit() override;

		void Release() override;

	protected:

		
		
	};
}

#endif