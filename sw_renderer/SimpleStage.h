#pragma once

#ifndef CENG_SWR_SIMPLE_STAGE_H
#define CENG_SWR_SIMPLE_STAGE_H

#include <atomic>

#include <ceng/datatypes/ring-buffer.h>

#include "future.h"

namespace Ceng::Experimental
{
	class Pipeline;

	template<class T>
	class SimpleStage
	{
	public:
		RingBuffer<Future<T>> queue;

		Experimental::Pipeline* pipeline;

		std::atomic<Ceng::UINT32> numThreads;

		SimpleStage()
		{
			numThreads.store(0);
		}

		SimpleStage(const SimpleStage& source)
			: queue(source.queue)
		{
			numThreads.store(source.numThreads.load());
		}

		SimpleStage& operator = (const SimpleStage& source)
		{
			queue = source.queue;
			numThreads.store(source.numThreads.load());

			return *this;
		}

		SimpleStage(Ceng::UINT32 items, Ceng::UINT32 cacheLineSize, Experimental::Pipeline* pipeline)
			: pipeline(pipeline)
		{
			numThreads.store(0);
			queue = RingBuffer<Future<T>>::Allocate(items, cacheLineSize);
		}
	};

}


#endif