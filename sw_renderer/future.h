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

		enum class Status
		{
			pending,
			complete
		};

		std::atomic<Status> status;
		std::shared_ptr<T> task;

		Future()
			: task(nullptr)
		{
			status.store(Status::pending);
		}

		Future(const Future& source)
			: task(task)
		{
			status.store(source.status.load());
		}

		Future& operator = (const Future& source)
		{
			status.store(source.status.load());
			task = source.task;

			return *this;
		}

		bool IsReady()
		{
			return status.load() == Status::complete;
		}

		void Discard()
		{
			status.store(Status::complete);
		}

		void Complete(const std::shared_ptr<T>& source)
		{
			task = source;
			status.store(Status::complete);
		}
	};
}

#endif