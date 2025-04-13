#pragma once

#ifndef CENG_SWR_SIMPLE_GROUPING_STAGE_H
#define CENG_SWR_SIMPLE_GROUPING_STAGE_H

#include <atomic>

#include <ceng/datatypes/ring-buffer.h>

#include "future.h"

#include "TaskGroup.h"

namespace Ceng::Experimental
{
	class Pipeline;	

	template<class T>
	class SimpleGroupingStage
	{
	public:

		using ItemType = Future<TaskGroup<T>>;

		RingBuffer<ItemType> queue;

		Experimental::Pipeline* pipeline;

		std::atomic<Ceng::UINT32> numThreads;

		std::atomic<Ceng::UINT32> totalTasksCompleted;

		SimpleGroupingStage()
			: pipeline(nullptr)
		{
			numThreads.store(0);
			totalTasksCompleted.store(0);
		}

		SimpleGroupingStage(const SimpleGroupingStage& source)
			: queue(source.queue), pipeline(source.pipeline)
		{
			numThreads.store(source.numThreads.load());
		}

		SimpleGroupingStage& operator = (const SimpleGroupingStage& source)
		{
			queue = source.queue;
			numThreads.store(source.numThreads.load());
			pipeline = source.pipeline;

			return *this;
		}

		SimpleGroupingStage(Ceng::UINT32 items, Ceng::UINT32 cacheLineSize, Experimental::Pipeline* pipeline)
			: pipeline(pipeline)
		{
			numThreads.store(0);
			queue = RingBuffer<ItemType>::Allocate(items, cacheLineSize);
		}

		void PopDiscardedTasks()
		{
			Ceng::UINT32 n = 0;

			while (queue.IsEmpty() == false)
			{
				auto& front = queue.Front();

				if (front.IsDiscarded())
				{
					queue.PopFront();
					++n;
					continue;
				}

				break;
			}

			pipeline->DiscardPending(n);
		}
	};

}


#endif