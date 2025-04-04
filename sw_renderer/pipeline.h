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
	class RenderThread;
	class RenderTask;

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

		Future& operator = (const Future& source)
		{
			ready.store(source.ready.load());
			task = source.task;

			return *this;
		}

		Future(const std::shared_ptr<T>& source)
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
		RingBuffer<Future<Experimental::RenderTask>> queue;
		std::atomic<Ceng::UINT32> numThreads;

		SimpleQueue()
		{
			numThreads.store(0);
		}

		SimpleQueue(const SimpleQueue& source)
			: queue(source.queue)
		{
			numThreads.store(source.numThreads.load());
		}

		SimpleQueue& operator = (const SimpleQueue& source)
		{
			queue = source.queue;
			numThreads.store(source.numThreads.load());

			return *this;
		}

		SimpleQueue(Ceng::UINT32 items, Ceng::UINT32 cacheLineSize)	
		{
			numThreads.store(0);
			queue = RingBuffer<Future<Experimental::RenderTask>>::Allocate(items, cacheLineSize);
		}
	};

	class BucketQueue
	{
	public:
		RingBuffer<Future<Experimental::RenderTask>> queue;

		// Indicates if something is executing in the bucket
		std::atomic<Ceng::UINT32> lock;

		// Thread holding the execution lock
		// -1 = none
		Ceng::INT32 threadId;

		BucketQueue()		
			: threadId(-1)
		{
			lock.store(0);
		}

		BucketQueue(const BucketQueue& source)
			: queue(source.queue), threadId(source.threadId)
		{
			lock.store(source.lock.load());
		}

		BucketQueue& operator = (const BucketQueue& source)
		{
			queue = source.queue;
			threadId = source.threadId;
			lock.store(source.lock.load());

			return *this;
		}

		BucketQueue(Ceng::UINT32 items, Ceng::UINT32 cacheLineSize)
			: threadId(-1)
		{
			queue = RingBuffer<Future<Experimental::RenderTask>>::Allocate(items, cacheLineSize);
		}
	};

	class BucketStage
	{
	public:
		std::vector<BucketQueue> buckets;
		std::atomic<Ceng::UINT32> numThreads;

		BucketStage()		
		{
			numThreads.store(0);
		}

		BucketStage& operator = (const BucketStage& source)
		{
			buckets = source.buckets;
			numThreads.store(source.numThreads.load());
			return *this;
		}

		BucketStage(Ceng::UINT32 amount, Ceng::UINT32 items, Ceng::UINT32 cacheLineSize)			
		{
			numThreads.store(0);

			for (auto k = 0; k < amount; ++k)
			{
				buckets.emplace_back(items, cacheLineSize);
			}
		}
	};

	struct ThreadData
	{
		Thread* thread;
		Experimental::RenderThread* task;
	};

	class Pipeline
	{
	public:

		RingBuffer<std::shared_ptr<DrawBatch>> drawQueue;

		RingBuffer<std::shared_ptr<DrawBatch>> vshaderOutQueue;

		SimpleQueue clipper;

		SimpleQueue triangleSetup;

		BucketStage rasterizer;

		BucketStage pixelShader;

		std::atomic<Ceng::UINT32> remainingTasks;
		std::atomic<Ceng::UINT32> activeThreads;

		ConditionVariable* rendererHasWork;

		std::vector<ThreadData> renderThreads;

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