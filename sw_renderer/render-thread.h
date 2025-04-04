/*****************************************************************************
*
* render-thread.h
*
* Created By Jari Korkala 9/10/2014
*
*****************************************************************************/

#ifndef CENG_RENDER_THREAD_H
#define CENG_RENDER_THREAD_H

#include <atomic>
#include <memory>

#include <ceng/datatypes/ring-buffer.h>

#include <ceng/interfaces/thread-task.h>
#include <ceng/datatypes/condition-variable.h>
#include <ceng/datatypes/critical-section.h>

namespace Ceng
{
	class Pipeline;

	class RenderThread : public ThreadTask
	{
	protected:

		Ceng::UINT32 threadId;
		Pipeline *pipeline;

		std::atomic<Ceng::UINT32> *runningThreadCount;
		std::atomic<Ceng::UINT32> *minThreads;
		std::atomic<Ceng::UINT32> *maxThreads;

		ConditionVariable *wakeCondition;

		CriticalSection *wakeCrit;
		std::shared_ptr<ConditionVariable> cmdWake;

	public:

		volatile Ceng::INT32 exitLoop;

		RenderThread();
		virtual ~RenderThread();

		RenderThread(const Ceng::UINT32 threadId,ConditionVariable *wakeCondition,
						std::shared_ptr<ConditionVariable> &cmdWake,
						std::atomic<Ceng::UINT32> *runningThreadCount,
						std::atomic<Ceng::UINT32> *minThreads,
						std::atomic<Ceng::UINT32> *maxThreads,Pipeline *pipeline);

		virtual void Release() override;

		virtual const CRESULT Execute() override;
		virtual const CRESULT Exit() override;
	};
}

namespace Ceng::Experimental
{
	class Pipeline;
	class RenderTask;

	class RenderThread : public ThreadTask
	{
	public:

		Ceng::UINT32 threadId;
		
		Pipeline* pipeline;

		RingBuffer<std::shared_ptr<Experimental::RenderTask>> inputQueue;

		std::atomic<Ceng::UINT32>* runningThreadCount;
		std::atomic<Ceng::UINT32>* minThreads;
		std::atomic<Ceng::UINT32>* maxThreads;

		ConditionVariable* wakeCondition;

		CriticalSection* wakeCrit;
		std::shared_ptr<ConditionVariable> cmdWake;

	public:

		volatile Ceng::INT32 exitLoop;

		RenderThread();
		~RenderThread() override;

		RenderThread(const Ceng::UINT32 threadId, ConditionVariable* wakeCondition,
			std::shared_ptr<ConditionVariable>& cmdWake,
			std::atomic<Ceng::UINT32>* runningThreadCount,
			std::atomic<Ceng::UINT32>* minThreads,
			std::atomic<Ceng::UINT32>* maxThreads, Pipeline* pipeline, Ceng::UINT32 inputLength, Ceng::UINT32 cacheLineSize);

		void Release() override;

		const CRESULT Execute() override;
		const CRESULT Exit() override;
	};
}

#endif