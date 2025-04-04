#pragma once

#ifndef CENG_SWR_FUTURE_H
#define CENG_SWR_FUTURE_H

#include <memory>

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
}

#endif