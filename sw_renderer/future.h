#pragma once

#ifndef CENG_SWR_FUTURE_H
#define CENG_SWR_FUTURE_H

#include <memory>
#include <atomic>

namespace Ceng::Experimental
{
	template<class T>
	class Future
	{
	public:

		enum class Status
		{
			pending,
			complete,
			discarded
		};

		std::atomic<Status> status;
		T result;

		Future()		
		{
			status.store(Status::pending);
		}

		Future(const Future& source)
			: result(source.result)
		{
			status.store(source.status.load());
		}

		Future& operator = (const Future& source)
		{
			status.store(source.status.load());
			result = source.result;

			return *this;
		}

		bool IsReady()
		{
			return status.load() == Status::complete;
		}

		void Discard()
		{
			status.store(Status::discarded);
		}

		bool IsDiscarded()
		{
			return status.load() == Status::discarded;
		}

		void Complete(const T& source)
		{
			result = source;
			status.store(Status::complete);
		}
	};
}

#endif