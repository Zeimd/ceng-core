#pragma once

#ifndef CENG_SWR_BUCKET_STAGE_H
#define CENG_SWR_BUCKET_STAGE_H

#include <vector>
#include <atomic>

#include "BucketQueue.h"

namespace Ceng::Experimental
{
	template<class T>
	class BucketStage
	{
	public:
		std::vector<BucketQueue<T>> buckets;
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
}

#endif