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
	template<class T>
	class Future
	{
	public:
		std::atomic<Ceng::UINT32> ready;
		std::shared_ptr<T> task;

		Future()
			: task(nullptr)
		{
			ready.store(0);
		}

		Future(const Future& source)
			: task(task)
		{
			ready.store(source.ready);
		}

		Future(std::shared_ptr<T>& source)
			: task(source)
		{
			ready.store(0);
		}

		bool IsReady()
		{
			return ready.load() == 1;
		}
	};

	class SimpleQueue
	{
	public:
		RingBuffer<Future<RenderTask>> queue;
		Ceng::UINT32 numThreads;

		SimpleQueue()
			: numThreads(0)
		{
		}

		SimpleQueue(Ceng::UINT32 items, Ceng::UINT32 cacheLineSize)
			: numThreads(0)
		{
			queue = RingBuffer<Future<RenderTask>>::Allocate(items, cacheLineSize);
		}
	};

	class BucketQueue
	{
	public:
		std::vector<SimpleQueue> queues;
		Ceng::UINT32 numThreads;

		BucketQueue()
			: numThreads(0)
		{

		}

		BucketQueue(Ceng::UINT32 buckets, Ceng::UINT32 items, Ceng::UINT32 cacheLineSize)
			: numThreads(0)
		{
			for (int k = 0; k < buckets; ++k)
			{
				queues.emplace_back(items, cacheLineSize);
			}
		}
	};

	class Pipeline
	{
	public:

		RingBuffer<std::shared_ptr<DrawBatch>> drawQueue;

		RingBuffer<std::shared_ptr<DrawBatch>> vshaderOutQueue;

		SimpleQueue clipper;

		SimpleQueue triangleSetup;

		BucketQueue rasterizer;

		BucketQueue pixelShader;

		std::atomic<Ceng::UINT32> remainingTasks;
		std::atomic<Ceng::UINT32> activeThreads;

		ConditionVariable* rendererHasWork;

		std::vector<Thread*> renderThreads;
		std::vector<ThreadTask*> renderThreadTasks;

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