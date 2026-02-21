#include <memory>

#include <ceng/interfaces/pshader-instance.h>

#include "PixelShaderContextCommon.h"
#include "ShaderLinkInstance.h"
#include "shader-link.h"

#include "extern-pshader-context.h"

#include "cr-pixel-shader.h"

#include "rtarget-data.h"

#include "task-pshader.h"
#include "rasterizer-batch.h"

using namespace Ceng;

ExternalPixelShaderContext::ExternalPixelShaderContext(PixelShaderInstance* instance, std::shared_ptr<PixelShaderContextCommon>& common)
	: instance(instance)
{
	this->common = common;
}

ExternalPixelShaderContext::~ExternalPixelShaderContext()
{
	instance->Release();
}

CRESULT ExternalPixelShaderContext::Configure(std::vector<PixelShaderInputDesc>& inputSemantics,
	std::vector<PixelShaderOutputDesc>& renderTargets,
	UniformManager& uniformManager)
{
	instance->BasicConfig(common->link->quadSize, common->shader->cacheLine,
		common->link->link->quadFormat.floatStart,
		common->link->link->quadFormat.doubleStart,
		common->link->link->quadFormat.targetStart,
		common->link->link->quadFormat.floatBlocks,
		common->link->link->quadFormat.doubleBlocks,
		(Ceng::Pshader::RenderTargetService*)common->renderTargetService);

	Pshader::PixelShaderInputRegister* inputRegisters = instance->GetInputs();
	Ceng::UINT32 inputSize = instance->InputSize();

	Pshader::PixelShaderOutputRegister* outputRegisters = instance->GetOutputs();
	Ceng::UINT32 outputSize = instance->OutputSize();

	Pshader::PixelShaderUniform* uniforms = instance->GetUniforms();
	Ceng::UINT32 uniformSize = instance->UniformSize();

	POINTER* stepBufferPtr = instance->StepBufferPtr();
	void* perspectiveTemp = instance->PerpectiveTemp();
	Ceng::UINT32* coverageAddress = instance->CoverageAddress();

	UINT8* quadBuffer = instance->QuadBuffer();

	// Set up input register offsets within the quad format

	for (Ceng::UINT32 k = 0; k < inputSize; k++)
	{
		inputRegisters[k].variable->perspective = (void*)perspectiveTemp;

		for (Ceng::UINT32 j = 0; j < common->link->link->quadFormat.variables.size(); j++)
		{
			// Link all input registers to the variable
			// with a matching semantic

			// NOTE: Multiple registers can map to one semantic

			if (inputSemantics[k].semantic == common->link->link->quadFormat.variables[j].semantic)
			{
				inputRegisters[k].variable->stepBuffer = stepBufferPtr;

				inputRegisters[k].variable->inputAddress = (POINTER)quadBuffer +
					common->link->link->quadFormat.variables[j].quadOffset;

				// TODO: Set staticly
				//inputRegisters[k].variable->inputFormat = common->link->link->quadFormat.variables[j].format;

				inputRegisters[k].variable->variableStep = common->link->link->quadFormat.variables[j].gradientOffset;
			}
		}
	}

	// Set up render target address locations within the quad format

	for (Ceng::UINT32 k = 2; k < outputSize; k++)
	{
		outputRegisters[k].variable->coverageMask = coverageAddress;

		outputRegisters[k].variable->inputAddress = (POINTER)((UINT8*)quadBuffer) +
			common->link->link->quadFormat.targetStart + outputRegisters[k].target * sizeof(POINTER);

		Ceng::UINT32 j;

		for (j = 2; j < common->activeRenderTargets; j++)
		{
			if (outputRegisters[k].target == common->targetHandles[j]->shaderSemantic)
			{
				outputRegisters[k].variable->writer = common->targetWriters[j].writer;
				outputRegisters[k].variable->quadWriteStep = common->targetHandles[k]->bytesPerPixel * 4;

				/*
				if (common->targetHandles[j]->baseAddress == NULL)
				{
					// TODO: set null writer
				}
				else
				{
					// TODO: set normal output writer
				}
				*/

				break;
			}
		}

		if (j == common->activeRenderTargets)
		{
			// TODO: attach null writer

			// No match found
			//outputRegisters[k].variable->bufferFormat = Ceng::IMAGE_FORMAT::UNKNOWN;
		}
	}

	for (Ceng::UINT32 k = 0; k < uniformSize; ++k)
	{
		uniforms[k].variable->dataPtr = (void*)common->uniformBuffer.uniformPtr[k];

		switch (common->shader->uniformList[k].dataType)
		{
		case SHADER_DATATYPE::sampler2d:
			Pshader::UniformSampler2d* ptr_sampler2d = (Pshader::UniformSampler2d*)uniforms[k].variable;

			Ceng::UINT32* unitIndex = (Ceng::UINT32*)uniforms[k].variable->dataPtr;

			ptr_sampler2d->sampler = (*(common->textureUnits))[*unitIndex].samplerObject;
			break;
		}
	}

	return CE_OK;
}

CRESULT ExternalPixelShaderContext::ProcessQuads(Task_PixelShader* batch, const Ceng::INT32 threadId)
{
	CR_TriangleData* triangle = batch->rasterizerBatch->triangle.get();

	Ceng::UINT32 fullLeafCount = batch->quadList.FullLeafCount();

	Ceng::UINT32 fullLeafSize = batch->quadList.LeafCapacity();

	for (int k = 0; k < fullLeafCount; ++k)
	{
		auto& leaf = batch->quadList.GetLeaf(k);

		instance->ProcessQuads(&leaf[0], fullLeafSize, &triangle->pshaderData, threadId);
	}

	Ceng::UINT32 remainderCount = batch->quadList.BackIndex();

	if (remainderCount)
	{
		auto& leaf = batch->quadList.GetBackLeaf();

		instance->ProcessQuads(&leaf[0], remainderCount, &triangle->pshaderData, threadId);
	}
	
	return CE_OK;
}

CRESULT ExternalPixelShaderContext::ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId)
{
	CR_TriangleData* triangle = batch->rasterizerBatch->triangle.get();

	Ceng::UINT32 fullLeafCount = batch->quadList.FullLeafCount();

	Ceng::UINT32 fullLeafSize = batch->quadList.LeafCapacity();

	for (int k = 0; k < fullLeafCount; ++k)
	{
		auto& leaf = batch->quadList.GetLeaf(k);

		instance->ProcessQuads(&leaf[0], fullLeafSize, &triangle->pshaderData, threadId);
	}

	Ceng::UINT32 remainderCount = batch->quadList.BackIndex();

	if (remainderCount)
	{
		auto& leaf = batch->quadList.GetBackLeaf();

		instance->ProcessQuads(&leaf[0], remainderCount, &triangle->pshaderData, threadId);
	}	

	return CE_OK;
}
