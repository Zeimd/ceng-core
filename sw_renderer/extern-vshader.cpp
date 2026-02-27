#include "extern-vshader.h"

#include "VertexShaderInstanceCommon.h"
#include "extern-vshader-context.h"

using namespace Ceng;

ExternalVertexShader::ExternalVertexShader()
	: desc(nullptr)
{

}

CRESULT ExternalVertexShader::Create(VertexShaderDescriptor* desc, ExternalVertexShader** out)
{
	if (out == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (desc == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	const VertexShaderInputDesc* inputSource = desc->InputArray();

	if (inputSource == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (desc->InputAmount() == 0)
	{
		return CE_ERR_INVALID_PARAM;
	}

	const VertexShaderOutputDesc* outputSource = desc->OutputArray();

	if (outputSource == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (desc->OutputAmount() == 0)
	{
		return CE_ERR_INVALID_PARAM;
	}

	ExternalVertexShader* temp = new ExternalVertexShader();

	temp->wrapper.shader = temp;
	temp->cacheLine = 64;

	temp->nextInstance = std::make_shared< Ceng::VertexShaderInstanceCommon>(temp);

	temp->desc = desc;

	for (auto k = 0; k < desc->InputAmount(); ++k)
	{
		temp->inputSemantics.push_back(inputSource[k]);
	}

	if (desc->UniformArray() != nullptr)
	{
		for (auto k = 0; k < desc->UniformAmount(); ++k)
		{
			temp->uniformList.push_back(desc->UniformArray()[k]);
		}
	}

	for (auto k = 0; k < desc->OutputAmount(); ++k)
	{
		temp->outputSemantics.push_back(outputSource[k]);
	}

	CRESULT cresult;

	cresult = temp->ConfigureInput();
	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = temp->ConfigureConstants();
	if (cresult != CE_OK)
	{
		return cresult;
	}

	*out = temp;

	return CE_OK;
}

ExternalVertexShader::~ExternalVertexShader()
{

}

CRESULT ExternalVertexShader::GetInstances(std::vector<std::shared_ptr<VertexShaderContext>>& instances,
	const Ceng::UINT32 renderThreads)
{
	nextInstance->ConfigureInput(inputSemantics);

	currentInstance = nextInstance;

	nextInstance = std::make_shared<VertexShaderInstanceCommon>(*currentInstance);

	instances = std::vector<std::shared_ptr<VertexShaderContext>>();

	for (Ceng::UINT32 k = 0; k < renderThreads; k++)
	{
		VertexShaderInstance* instance = desc->GetInstance(currentInstance->shader->cacheLine,
			&currentInstance->shader->nullInput,
			&currentInstance->shader->nullOutput);

		if (instance == nullptr)
		{
			instances.clear();
			return CE_ERR_FAIL;
		}

		std::shared_ptr<ExternalVertexShaderContext> context =
			std::make_shared<ExternalVertexShaderContext>(instance, currentInstance);

		CRESULT cresult = context->Configure();

		if (cresult != CE_OK)
		{
			return cresult;
		}

		instances.push_back(context);
	}

	return CE_OK;
}