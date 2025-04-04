/*****************************************************************************
*
* task-triangle-setup.h
*
* Created By Jari Korkala 2/2015
*
*****************************************************************************/

#ifndef CENG_TASK_TRIANGLE_SETUP_H
#define CENG_TASK_TRIANGLE_SETUP_H

#include <memory>
#include <vector>

#include "locking-task.h"

#include "future.h"

namespace Ceng
{
	class TriangleBatch;
	class Pipeline;

	class Task_TriangleSetup : public LockingTask
	{
	protected:

		std::shared_ptr<TriangleBatch> triangleBatch;

	protected:

		Task_TriangleSetup();
	
	public:

		Task_TriangleSetup(std::shared_ptr<TriangleBatch> &triangleBatch);

		virtual ~Task_TriangleSetup();

		virtual const CRESULT Prepare(const Ceng::UINT32 threadId,Pipeline *pipeline) override;
		virtual const CRESULT Execute(const Ceng::UINT32 threadId,Pipeline *pipeline) override;
	};
}

namespace Ceng::Experimental
{
	class Pipeline;
	class Task_PixelShader;

	class Task_TriangleSetup : public Experimental::RenderTask
	{
	public:

		std::shared_ptr<TriangleBatch> triangleBatch;

		std::vector< Future<Experimental::Task_Rasterizer>* > futures;

	protected:

	public:

		Task_TriangleSetup();

		Task_TriangleSetup(std::shared_ptr<TriangleBatch>& triangleBatch);

		~Task_TriangleSetup() override;

		const CRESULT Prepare(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
		const CRESULT Execute(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
	};
}

#endif