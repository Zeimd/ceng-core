#include "task-vshader.h"
#include "pipeline.h"

#include "vshader-instance.h"

using namespace Ceng;

Task_VertexShader::Task_VertexShader()
	: future(nullptr)
{

}

Task_VertexShader::Task_VertexShader(std::shared_ptr<DrawBatch>& batch)
	: batch(batch), future(nullptr)
{

}

Task_VertexShader::~Task_VertexShader()
{

}

const CRESULT Task_VertexShader::Prepare(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline)
{
	return CE_OK;
}

const CRESULT Task_VertexShader::Execute(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline)
{
	CRESULT cresult = CE_OK;

	cresult = batch->renderState->vshaderInstance[threadId]->ProcessVertexBatch(batch, threadId, future);

	--pipeline->triangleSetup.numThreads;
	--pipeline->runningTasks;
	++pipeline->totalTasksCompleted;

	++pipeline->triangleSetup.totalTasksCompleted;

	//pipeline->WakeAllThreads();

	return cresult;

	return CE_OK;
}