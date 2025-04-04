/*****************************************************************************
*
* task-clipper.h
*
* Created By Jari Korkala 2/2015
*
*****************************************************************************/

#ifndef CENG_TASK_CLIPPER_H
#define CENG_TASK_CLIPPER_H

#include <memory>
#include "locking-task.h"

#include "future.h"

namespace Ceng
{
	class ClipperBatch;

	class Task_Clipper : public LockingTask
	{
	protected:

		std::shared_ptr<ClipperBatch> clipperBatch;

		Task_Clipper();
	public:

		Task_Clipper(std::shared_ptr<ClipperBatch> &clipperBatch);

		virtual ~Task_Clipper();

		virtual const CRESULT Prepare(const Ceng::UINT32 threadId,Pipeline *pipeline) override;
		virtual const CRESULT Execute(const Ceng::UINT32 threadId,Pipeline *pipeline) override;
	};
}

namespace Ceng::Experimental
{
	class Task_TriangleSetup;

	class Task_Clipper : public Experimental::RenderTask
	{
	protected:

		std::shared_ptr<ClipperBatch> clipperBatch;

		Task_Clipper();
	public:

		Future<Experimental::Task_TriangleSetup>* future;

		Task_Clipper(std::shared_ptr<ClipperBatch>& clipperBatch);

		virtual ~Task_Clipper();

		const CRESULT Prepare(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
		const CRESULT Execute(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
	};
}

#endif