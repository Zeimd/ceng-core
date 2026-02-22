/*****************************************************************************
*
* vshader-instance.cpp
*
* Created By Jari Korkala 8/2014
*
* - CR_VertexShader split into static and state-dependent parts.
*
*****************************************************************************/

#include "vshader-instance.h"

#include "cr-vertex-format.h"

#include "vshader-types.h"
#include "vshader-util.h"

#include "draw-batch.h"

#include "fragment-format.h"

#include <ceng/datatypes/vshader-input-desc.h>

#include "cr-vertex-shader.h"

#include <ceng/math/ce-matrix.h>

#include "clipper-batch.h"
#include "task-clipper.h"

#include "locking-stage.h"

#include "pipeline.h"

#include "VertexShaderInstanceCommon.h"

using namespace Ceng;

CR_VertexShaderInstance::CR_VertexShaderInstance(std::shared_ptr<VertexShaderInstanceCommon>& common)
{
	this->common = common;

	outputBaseAddress = 0;

	inputRegisters[0].variable = &inPosition;
	inputRegisters[1].variable = &inNormal;
	inputRegisters[2].variable = &inTangent;
	inputRegisters[3].variable = &inTexCoord0;
	inputRegisters[4].variable = &inTexCoord1;

	for (int k = 0; k < outputRegisters.size(); ++k)
	{
		inputRegisters[k].variable->sourceFormat = common->shader->nullInput.sourceFormat;
		inputRegisters[k].variable->sourceAddress = common->shader->nullInput.sourceAddress;
	}

	outputRegisters[0].variable = &outPosition;
	outputRegisters[1].variable = &outNormal;
	outputRegisters[2].variable = &outTangent;
	outputRegisters[3].variable = &outTexCoord0;
	outputRegisters[4].variable = &outTexCoord1;

	for (int k = 0; k < outputRegisters.size(); ++k)
	{
		outputRegisters[k].variable->destAddress = common->shader->nullOutput.destAddress;
		outputRegisters[k].variable->destOffset = common->shader->nullOutput.destOffset;
	}

	uniforms[0].variable = &fullVertexTransform;
}

CR_VertexShaderInstance::~CR_VertexShaderInstance()
{
}

CRESULT CR_VertexShaderInstance::Configure(const std::vector<VertexShaderInputDesc>& inputSemantics)
{
	for (size_t k = 0; k < inputRegisters.size(); ++k)
	{
		Ceng::UINT32 source = common->sourceIndex[k];

		inputRegisters[k].variable->sourceFormat = common->vertexFormat->variables[source].dataType;
	}

	// Set up references to output blocks

	for (size_t k = 0; k < outputRegisters.size(); ++k)
	{
		for (size_t j = 0; j < common->fragmentFormat->variables.size(); ++j)
		{
			if (common->shader->inputSemantics[k].semantic == common->fragmentFormat->variables[j].semantic)
			{
				outputRegisters[k].variable->destAddress = &outputBaseAddress;
				outputRegisters[k].variable->destOffset = common->fragmentFormat->variables[k].offset;
			}
		}
	}

	for (Ceng::UINT32 k = 0; k < uniforms.size(); ++k)
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

const CRESULT CR_VertexShaderInstance::ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
														  LockingStage *outputQueue)
{	

	INT32 inputCount = inputRegisters.size();
	INT32 outputCount = common->fragmentFormat->variables.size();

	outputBaseAddress = (POINTER)& (*(batch->fragmentCache))[0];

	for(Ceng::UINT32 k=0;k<batch->vertexCount;k++)
	{
		Ceng::UINT32 index = batch->fragmentIndex[k].tag;

		// Move input pointers to correct position

		for(Ceng::INT32 i=0;i<inputCount;i++)
		{
			inputRegisters[i].variable->sourceAddress = common->inputBaseAddress[i]
				+ index*common->inputSteps[i];
		}

		ShaderFunction();
	
		outputBaseAddress += common->fragmentSizeBytes;
	}

	auto out_batch = std::shared_ptr<ClipperBatch>(new ClipperBatch(batch));

	auto out_task = std::shared_ptr<LockingTask>(new Task_Clipper(out_batch));

	outputQueue->AddTask(0,out_task);

	return CE_OK;
}

const CRESULT CR_VertexShaderInstance::ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
	Ceng::UINT32 threadId,
	Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future)
{
	//	return CE_OK;

	INT32 inputCount = inputRegisters.size();
	INT32 outputCount = common->fragmentFormat->variables.size();

	outputBaseAddress = (POINTER) & (*(batch->fragmentCache))[0];

	for (Ceng::UINT32 k = 0; k < batch->vertexCount; k++)
	{
		Ceng::UINT32 index = batch->fragmentIndex[k].tag;

		// Move input pointers to correct position

		for (Ceng::INT32 i = 0; i < inputCount; i++)
		{
			inputRegisters[i].variable->sourceAddress = common->inputBaseAddress[i]
				+ index * common->inputSteps[i];
		}

		ShaderFunction();

		outputBaseAddress += common->fragmentSizeBytes;
	}

	auto out_batch = std::make_shared<ClipperBatch>(batch);

	future->Complete(std::make_shared<Experimental::Task_Clipper>(out_batch));

	return CE_OK;
}

void CR_VertexShaderInstance::ShaderFunction()
{
	_declspec(align(16)) VectorF4 temp;
	_declspec(align(16)) VectorF4 positionTemp;

	// NOTE: Use IN_SEMANTIC pointers to obtain
	//       correct variable from input stream

	positionTemp = inPosition;
	positionTemp.w = FLOAT32(1.0f);
	
	positionTemp = fullVertexTransform * positionTemp;
	
	outPosition = positionTemp;

	// NOTE: Can't transfer directly from input to output
	//       because the temporary Vector4 won't be
	//       aligned in memory

	/*
	temp = *IN_NORMAL;
	*OUT_NORMAL = temp;
	
	
	temp = *IN_COLOR0;
	*OUT_COLOR0 = temp;
	*/
	
	_declspec(align(16)) VectorF2 v2Temp;

	v2Temp = inTexCoord0;
	outTexCoord0 = v2Temp;
	
	
	v2Temp = inTexCoord1;
	outTexCoord1 = v2Temp;

	/*
	tempFloat = *IN_TEXCOORD2;
	*OUT_TEXCOORD2 = tempFloat;
	*/
}


