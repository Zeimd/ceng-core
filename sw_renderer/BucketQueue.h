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
			queue = RingBuffer<Future<T>>::Allocate(items, cacheLineSize);
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