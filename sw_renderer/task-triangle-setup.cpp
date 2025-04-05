/*****************************************************************************
*
* task-triangle-setup.cpp
*
* Created By Jari Korkala 2/2015
*
*****************************************************************************/

#include "task-triangle-setup.h"

#include "pipeline.h"
#include "triangle-batch.h"
#include "rasterizer-cr.h"

using namespace Ceng;

Task_TriangleSetup::Task_TriangleSetup()
{
}

Task_TriangleSetup::~Task_TriangleSetup()
{
}

Task_TriangleSetup::Task_TriangleSetup(std::shared_ptr<TriangleBatch> &triangleBatch)
	: triangleBatch(triangleBatch)
{
}

const CRESULT Task_TriangleSetup::Execute(const Ceng::UINT32 threadId,Pipeline *pipeline)
{
	CRESULT cresult = CE_OK;

	cresult = triangleBatch->renderState->rasterizer->TriangleSetup(triangleBatch,pipeline->rasterizer);

	--pipeline->triangleSetup.activeThreads;
	--pipeline->activeThreads;

	pipeline->WakeAllThreads();

	return cresult;
}

const CRESULT Task_TriangleSetup::Prepare(const Ceng::UINT32 threadId,Pipeline *pipeline)
{
	return CE_OK;
}

//***************************************************************************************
// Experimental new version

Experimental::Task_TriangleSetup::Task_TriangleSetup()
{
}

Experimental::Task_TriangleSetup::~Task_TriangleSetup()
{
}

Experimental::Task_TriangleSetup::Task_TriangleSetup(std::shared_ptr<TriangleBatch>& triangleBatch)
	: triangleBatch(triangleBatch)
{
}

const CRESULT Experimental::Task_TriangleSetup::Execute(const Ceng::UINT32 threadId, Pipeline* pipeline)
{
	CRESULT cresult = CE_OK;

	cresult = triangleBatch->renderState->rasterizer->TriangleSetup(triangleBatch, futures, pipeline->rasterizer.buckets.size());

	--pipeline->triangleSetup.numThreads;
	--pipeline->runningTasks;

	pipeline->WakeAllThreads();

	return cresult;
}

const CRESULT Experimental::Task_TriangleSetup::Prepare(const Ceng::UINT32 threadId, Pipeline* pipeline)
{
	return CE_OK;
}