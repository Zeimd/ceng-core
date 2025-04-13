#pragma once

#ifndef CENG_SWRENDER_TASK_GROUP_H
#define CENG_SWRENDER_TASK_GROUP_H

#include <vector>
#include <memory>

namespace Ceng::Experimental
{
	template<class T>
	class TaskData
	{
	public:
		bool issued;
		std::shared_ptr<T> task;

		TaskData(const std::shared_ptr<T>& source)
			: task(source), issued(false)
		{

		}

		TaskData(const TaskData& source)
			: issued(source.issued), task(source.task)
		{

		}

		TaskData& operator = (const TaskData& source)
		{
			issued = source.issued;
			task = source.task;

			return *this;
		}
	};

	template<class T>
	class TaskGroup
	{
	public:

		std::vector<TaskData<T>> tasks;

		Ceng::UINT32 issuedCount;

		TaskGroup()
			: issuedCount(0)
		{

		}

		bool IsComplete()
		{
			return tasks.size() == issuedCount;
		}
	};
}

#endif