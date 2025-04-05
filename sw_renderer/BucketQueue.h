#pragma once

#ifndef CENG_SWR_BUCKET_QUEUE_H
#define CENG_SWR_BUCKET_QUEUE_H

#include <atomic>

#include <ceng/datatypes/ring-buffer.h>

#include "future.h"

namespace Ceng::Experimental
{
	template<class T>
	class BucketQueue
	{
	public:
		RingBuffer<Future<T>> queue;

		// Thread holding the execution lock
		// -1 = none
		Ceng::INT32 threadId;

		// Number of tasks from this bucket issued to thread holding the lock
		std::atomic<Ceng::UINT32> issuedTasks;

		// Number of tasks completed by the locking thread
		std::atomic<Ceng::UINT32> completedTasks;

		BucketQueue()
			: threadId(-1)
		{
			issuedTasks.store(0);
			completedTasks.store(0);
		}

		BucketQueue(const BucketQueue& source)
			: queue(source.queue), threadId(source.threadId)
		{
			issuedTasks.store(source.issuedTasks.load());
			completedTasks.store(source.completedTasks.load());
		}

		BucketQueue& operator = (const BucketQueue& source)
		{
			queue = source.queue;
			threadId = source.threadId;
			issuedTasks.store(source.issuedTasks.load());
			completedTasks.store(source.completedTasks.load());

			return *this;
		}

		BucketQueue(Ceng::UINT32 items, Ceng::UINT32 cacheLineSize)
			: threadId(-1)
		{
			queue = RingBuffer<Future<T>>::Allocate(items, cacheLineSize);
		}

		bool Unlock(Ceng::UINT32 id)
		{
			if (threadId == -1)
			{
				return true;
			}

			if (id == threadId)
			{
				return true;
			}

			if (issuedTasks.load() != completedTasks.load())
			{
				return false;
			}

			issuedTasks.store(0);
			completedTasks.store(0);

			threadId = -1;

			return true;
		}

		// Marks bucket as locked for given thread id.
		// Undefined behavior if bucket is not unlocked before called.
		void Lock(Ceng::UINT32 id)
		{
			threadId = id;
			++issuedTasks;
		}

		void PopEmptyTasks()
		{
			while (queue.IsEmpty() == false)
			{
				auto& front = queue.Front();

				if (front.task == nullptr)
				{
					queue.PopFront();
					continue;
				}

				break;
			}
		}
	};
}

#endif