#include <ceng/interfaces/vshader-instance.h>

#include "extern-vshader-context.h"

#include "VertexShaderInstanceCommon.h"

#include "vshader-input-reader.h"

#include "cr-vertex-format.h"
#include "fragment-format.h"
#include "cr-vertex-shader.h"

#include "draw-batch.h"
#include "clipper-batch.h"
#include "task-clipper.h"
#include "locking-task.h"
#include "locking-stage.h"

using namespace Ceng;

ExternalVertexShaderContext::ExternalVertexShaderContext(VertexShaderInstance* instance, 
	std::shared_ptr<VertexShaderInstanceCommon>& common)
	: instance(instance)
{
	this->common = common;
}

ExternalVertexShaderContext::~ExternalVertexShaderContext()
{
	instance->Release();
}

CRESULT ExternalVertexShaderContext::Configure()
{
	instance->BasicConfig(common->fragmentSizeBytes, &common->inputBaseAddress[0], &common->inputSteps[0]);

	Vshader::VertexShaderInputRegister* inputRegisters = instance->GetInputs();
	Ceng::UINT32 inputSize = instance->InputSize();

	Vshader::VertexShaderOutputRegister* outputRegisters = instance->GetOutputs();
	Ceng::UINT32 outputSize = instance->OutputSize();

	Vshader::VertexShaderUniform* uniforms = instance->GetUniforms();
	Ceng::UINT32 uniformSize = instance->UniformSize();

	POINTER* outputBaseAddress = instance->OutputBaseAddress();

	for (size_t k = 0; k < inputSize; ++k)
	{
		Ceng::UINT32 source = common->sourceIndex[k];

		inputRegisters[k].variable->callBack = Vshader::GetReadCallback(inputRegisters[k].type,
			common->vertexFormat->variables[source].dataType);
	}

	// Set up references to output blocks

	for (size_t k = 0; k < outputSize; ++k)
	{
		for (size_t j = 0; j < common->fragmentFormat->variables.size(); ++j)
		{
			if (common->shader->inputSemantics[k].semantic == common->fragmentFormat->variables[j].semantic)
			{
				outputRegisters[k].variable->destAddress = outputBaseAddress;
				outputRegisters[k].variable->destOffset = common->fragmentFormat->variables[k].offset;
			}
		}
	}

	for (Ceng::UINT32 k = 0; k < uniformSize; ++k)
	{
		uniforms[k].variable->dataPtr = (void*)common->uniformBuffer.uniformPtr[k];

		/*
		switch (common->shader->uniformList[k].dataType)
		{
		case SHADER_DATATYPE::sampler2d:
			Pshader::UniformSampler2d* ptr_sampler2d = (Pshader::UniformSampler2d*)uniforms[k].variable;

			Ceng::UINT32* unitIndex = (Ceng::UINT32*)uniforms[k].variable->dataPtr;

			ptr_sampler2d->sampler = (*(common->textureUnits))[*unitIndex].samplerObject;
			break;
		}
		*/
	}

	return CE_OK;
}

CRESULT ExternalVertexShaderContext::ProcessVertexBatch(std::shared_ptr<DrawBatch> batch, LockingStage* outputQueue)
{
	instance->ProcessVertexBatch(batch->vertexCount, &batch->fragmentIndex[0], &(*(batch->fragmentCache))[0], 0);

	auto out_batch = std::shared_ptr<ClipperBatch>(new ClipperBatch(batch));

	auto out_task = std::shared_ptr<LockingTask>(new Task_Clipper(out_batch));

	outputQueue->AddTask(0, out_task);

	return CE_OK;
}

CRESULT ExternalVertexShaderContext::ProcessVertexBatch(std::shared_ptr<DrawBatch> batch, Ceng::UINT32 threadId,
	Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future)
{
	instance->ProcessVertexBatch(batch->vertexCount, &batch->fragmentIndex[0], &(*(batch->fragmentCache))[0], threadId);

	auto out_batch = std::make_shared<ClipperBatch>(batch);

	future->Complete(std::make_shared<Experimental::Task_Clipper>(out_batch));

	return CE_OK;
}