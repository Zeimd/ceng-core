/*****************************************************************************
*
* pipeline.h
*
* Created By Jari Korkala 9/10/2014
*
*****************************************************************************/

#ifndef CRENDER_PIPELINE_H
#define CRENDER_PIPELINE_H

#include <atomic>
#include <memory>
#include <vector>

#include <ceng/datatypes/ring-buffer.h>
#include <ceng/datatypes/array-atomic.h>
#include <ceng/datatypes/thread.h>
#include <ceng/interfaces/thread-task.h>

#include <ceng/datatypes/condition-variable.h>

#include "locking-stage.h"

#include "future.h"
#include "SimpleStage.h"
#include "BucketQueue.h"
#include "BucketStage.h"

#include "task-scheduler.h"

namespace Ceng
{
	class RasterizerBatch;
	class Task_PixelShader;

	class DrawBatch;
	class ClipperBatch;
	class TriangleBatch;

	typedef RingBuffer<std::shared_ptr<RasterizerBatch>> RasterizerQueue;

	class Pipeline
	{
	public:

		RingBuffer<std::shared_ptr<DrawBatch>> drawQueue;

		RingBuffer<std::shared_ptr<DrawBatch>> vshaderOutQueue;

		LockingStage clipper;

		LockingStage triangleSetup;

		LockingStage rasterizer;		
			
		LockingStage pixelShader;

		std::atomic<Ceng::UINT32> remainingTasks;
		std::atomic<Ceng::UINT32> activeThreads;

		ConditionVariable *rendererHasWork;

		std::vector<Thread*> renderThreads;
		std::vector<ThreadTask*> renderThreadTasks;

		std::atomic<Ceng::UINT32> runningThreadCount;
		std::atomic<Ceng::UINT32> minThreadCount;
		std::atomic<Ceng::UINT32> maxThreadCount;

	protected:

		const Ceng::CRESULT Local_GetTask(const Ceng::UINT32 threadId,
											std::shared_ptr<RenderTask> &out_task);

	public:

		Pipeline();
		~Pipeline();

		void ResumeThreads();
		void PauseThreads();
		
		void WakeAllThreads();
		void WakeOneThread();

		const CRESULT Configure(const Ceng::UINT32 cacheLine,const Ceng::UINT32 maxScreenBuckets,
									const Ceng::UINT32 renderThreads,std::shared_ptr<ConditionVariable> &cmdWake);

		std::shared_ptr<RenderTask> GetTask(const Ceng::UINT32 threadId);

	};
}

namespace Ceng::Experimental
{
	class RenderThread;
	class RenderTask;

	class Task_PixelShader;
	class Task_Clipper;
	class Task_TriangleSetup;
	class Task_Rasterizer;
	
	struct RenderThreadData
	{
		Thread* thread;
		Experimental::RenderThread* task;
	};

	class Pipeline
	{
	public:

		RingBuffer<std::shared_ptr<DrawBatch>> drawQueue;

		RingBuffer<std::shared_ptr<DrawBatch>> vshaderOutQueue;

		SimpleStage<Experimental::Task_Clipper> clipper;

		SimpleStage<Experimental::Task_TriangleSetup> triangleSetup;

		BucketStage<Experimental::Task_Rasterizer> rasterizer;

		BucketStage<Experimental::Task_PixelShader> pixelShader;

		// Total number of tasks left in the pipeline
		std::atomic<Ceng::UINT32> pendingTasks;

		// Number of tasks currently in flight. Either in worker thread's input queue or executing.
		std::atomic<Ceng::UINT32> runningTasks;

		ConditionVariable* rendererHasWork;

		std::vector<RenderThreadData> renderThreads;

		Thread* scheduler;
		SchedulerTask* schedulerTask;

		std::atomic<Ceng::UINT32> runningThreadCount;
		std::atomic<Ceng::UINT32> minThreadCount;
		std::atomic<Ceng::UINT32> maxThreadCount;

	public:

		Pipeline();
		~Pipeline();

		void ResumeThreads();
		void PauseThreads();

		void WakeAllThreads();
		void WakeOneThread();

		const CRESULT Configure(const Ceng::UINT32 cacheLine, const Ceng::UINT32 maxScreenBuckets,
			const Ceng::UINT32 renderThreads, std::shared_ptr<ConditionVariable>& cmdWake);
	};
}

#endif