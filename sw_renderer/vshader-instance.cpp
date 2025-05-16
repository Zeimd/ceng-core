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

#include "vshader-input.h"
#include "vshader-output.h"

#include "draw-batch.h"

#include "fragment-format.h"

#include "vshader-input-semantic.h"

#include "cr-vertex-shader.h"

#include <ceng/math/ce-matrix.h>

#include "clipper-batch.h"
#include "task-clipper.h"

#include "locking-stage.h"

#include "pipeline.h"

using namespace Ceng;

CR_VertexShaderInstance::CR_VertexShaderInstance(std::shared_ptr<VertexShaderInstanceCommon>& common)
{
	this->common = common;

	outputBaseAddress = 0;

	IN_POSITION = &common->shader->nullInput;

	IN_NORMAL = &common->shader->nullInput;
	IN_TANGENT = &common->shader->nullInput;
	IN_BINORMAL = &common->shader->nullInput;

	IN_COLOR0 = &common->shader->nullInput;
	IN_COLOR1 = &common->shader->nullInput;

	IN_TEXCOORD0 = &common->shader->nullInput;
	IN_TEXCOORD1 = &common->shader->nullInput;
	IN_TEXCOORD2 = &common->shader->nullInput;
	IN_TEXCOORD3 = &common->shader->nullInput;
	IN_TEXCOORD4 = &common->shader->nullInput;
	IN_TEXCOORD5 = &common->shader->nullInput;
	IN_TEXCOORD6 = &common->shader->nullInput;
	IN_TEXCOORD7 = &common->shader->nullInput;

	OUT_POSITION = &common->shader->nullOutput;

	OUT_NORMAL = &common->shader->nullOutput;
	OUT_BINORMAL = &common->shader->nullOutput;
	OUT_TANGENT = &common->shader->nullOutput;

	OUT_COLOR0 = &common->shader->nullOutput;
	OUT_COLOR1 = &common->shader->nullOutput;

	OUT_TEXCOORD0 = &common->shader->nullOutput;
	OUT_TEXCOORD1 = &common->shader->nullOutput;
	OUT_TEXCOORD2 = &common->shader->nullOutput;
	OUT_TEXCOORD3 = &common->shader->nullOutput;
	OUT_TEXCOORD4 = &common->shader->nullOutput;
	OUT_TEXCOORD5 = &common->shader->nullOutput;
	OUT_TEXCOORD6 = &common->shader->nullOutput;
	OUT_TEXCOORD7 = &common->shader->nullOutput;
	
}

CR_VertexShaderInstance::~CR_VertexShaderInstance()
{
}

const CRESULT CR_VertexShaderInstance::ConfigureInput(const std::vector<CR_vsInputSemantic> &inputSemantics)
{
	// TODO: Provide as input parameter

	UINT32 k;

	inputRegisters = AlignedBuffer<CR_vsInputRegister>(inputSemantics.size(),common->shader->cacheLine);

	// Set up references to input variables
	for(k=0;k<inputSemantics.size();k++)
	{
	
		switch(inputSemantics[k].semantic)
		{
		case Ceng::SHADER_SEMANTIC::POSITION:
			IN_POSITION = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::NORMAL:
			IN_NORMAL = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::BINORMAL:
			IN_BINORMAL = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TANGENT:
			IN_TANGENT = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::COLOR_0:
			IN_COLOR0 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::COLOR_1:
			IN_COLOR1 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_0:
			IN_TEXCOORD0 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_1:
			IN_TEXCOORD1 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_2:
			IN_TEXCOORD2 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_3:
			IN_TEXCOORD3 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_4:
			IN_TEXCOORD4 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_5:
			IN_TEXCOORD5 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_6:
			IN_TEXCOORD6 = &inputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_7:
			IN_TEXCOORD7 = &inputRegisters[k];
			break;
		default:
			break;
		}
	}

	for (k = 0; k < inputRegisters.GetElements(); k++)
	{
		Ceng::UINT32 source = common->sourceIndex[k];

		inputRegisters[k].sourceFormat = common->vertexFormat->variables[source].dataType;
	}
	
	return CE_OK;
}

const CRESULT CR_VertexShaderInstance::SetFragmentFormat()
{
	// Set up references to output blocks

	outputRegisters = AlignedBuffer<CR_vsOutputRegister>(
		common->fragmentFormat->variables.size(),common->shader->cacheLine);

	for(size_t k=0;k<common->fragmentFormat->variables.size();k++)
	{
		outputRegisters[k].destAddress = &outputBaseAddress;
		outputRegisters[k].destFormat = common->fragmentFormat->variables[k].format;
		outputRegisters[k].destOffset = common->fragmentFormat->variables[k].offset;
	}

	for(size_t k=0;k<common->fragmentFormat->variables.size();k++)
	{
		switch(common->fragmentFormat->variables[k].semantic)
		{
		case Ceng::SHADER_SEMANTIC::POSITION:
			OUT_POSITION = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::NORMAL:
			OUT_NORMAL = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::BINORMAL:
			OUT_BINORMAL = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TANGENT:
			OUT_TANGENT = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::COLOR_0:
			OUT_COLOR0 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::COLOR_1:
			OUT_COLOR1 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_0:
			OUT_TEXCOORD0 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_1:
			OUT_TEXCOORD1 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_2:
			OUT_TEXCOORD2 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_3:
			OUT_TEXCOORD3 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_4:
			OUT_TEXCOORD4 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_5:
			OUT_TEXCOORD5 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_6:
			OUT_TEXCOORD6 = &outputRegisters[k];
			break;
		case Ceng::SHADER_SEMANTIC::TEXCOORD_7:
			OUT_TEXCOORD7 = &outputRegisters[k];
			break;
		default:
			break;
		}
	}

	return CE_OK;
}

const CRESULT CR_VertexShaderInstance::ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
														  LockingStage *outputQueue)
{	
//	return CE_OK;

	INT32 inputCount = inputRegisters.GetElements();
	INT32 outputCount = common->fragmentFormat->variables.size();

	outputBaseAddress = (POINTER)& (*(batch->fragmentCache))[0];

	for(Ceng::UINT32 k=0;k<batch->vertexCount;k++)
	{
		Ceng::UINT32 index = batch->fragmentIndex[k].tag;

		// Move input pointers to correct position

		for(Ceng::INT32 i=0;i<inputCount;i++)
		{
			inputRegisters[i].sourceAddress = common->inputBaseAddress[i]
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

	INT32 inputCount = inputRegisters.GetElements();
	INT32 outputCount = common->fragmentFormat->variables.size();

	outputBaseAddress = (POINTER) & (*(batch->fragmentCache))[0];

	for (Ceng::UINT32 k = 0; k < batch->vertexCount; k++)
	{
		Ceng::UINT32 index = batch->fragmentIndex[k].tag;

		// Move input pointers to correct position

		for (Ceng::INT32 i = 0; i < inputCount; i++)
		{
			inputRegisters[i].sourceAddress = common->inputBaseAddress[i]
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

	// ***** Constant setup

	const Matrix4 *transform = (Matrix4*)common->uniformPtr[0];

	// ***** Local variables

	_declspec(align(16)) VectorF4 temp;
	_declspec(align(16)) VectorF4 positionTemp;

	// NOTE: Use IN_SEMANTIC pointers to obtain
	//       correct variable from input stream

	positionTemp = *IN_POSITION;
	positionTemp.w = FLOAT32(1.0f);
	
	positionTemp = (*transform) * positionTemp;
	
	*OUT_POSITION = positionTemp;

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

	v2Temp = *IN_TEXCOORD0;
	*OUT_TEXCOORD0 = v2Temp;
	
	
	v2Temp = *IN_TEXCOORD1;
	*OUT_TEXCOORD1 = v2Temp;

	/*
	tempFloat = *IN_TEXCOORD2;
	*OUT_TEXCOORD2 = tempFloat;
	*/
}


