/*****************************************************************************
*
* locking-task.h
*
* Created By Jari Korkala 10/10/2014
*
*****************************************************************************/

#ifndef CRENDER_LOCKING_TASK_H
#define CRENDER_LOCKING_TASK_H

#include "render-task.h"

namespace Ceng
{
	class CriticalSection;

	class LockingTask : public RenderTask
	{
	public:

		CriticalSection *lock;

		LockingTask();

	public:

		~LockingTask() override;

		const CRESULT Prepare(const Ceng::UINT32 threadId, Pipeline* pipeline) override;

		const CRESULT Execute(const Ceng::UINT32 threadId, Pipeline* pipeline) override;
	};
}

#endif