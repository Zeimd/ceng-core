#include "extern-pshader.h"
#include "extern-pshader-context.h"

using namespace Ceng;

ExternalPixelShader::ExternalPixelShader()
	: desc(nullptr)
{

}

CRESULT ExternalPixelShader::Create(PixelShaderDescriptor* desc, ExternalPixelShader** out)
{
	if (out == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (desc == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	PixelShaderInputDesc* inputSource = desc->InputArray();

	if (inputSource == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (desc->InputAmount() == 0)
	{
		return CE_ERR_INVALID_PARAM;
	}

	PixelShaderOutputDesc* outputSource = desc->OutputArray();

	if (outputSource == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	if (desc->OutputAmount() == 0)
	{
		return CE_ERR_INVALID_PARAM;
	}

	ExternalPixelShader* temp = new ExternalPixelShader();

	temp->wrapper.shader = temp;
	temp->cacheLine = 64;

	temp->nextInstance = std::make_shared< Ceng::PixelShaderContextCommon>(temp);

	// Set up a NULL input and output registers 
	// to guard against exceptions from use
	// of undefined semantic links

	//nullInput.semantic = Ceng::SHADER_SEMANTIC::POSITION;
	temp->nullInput.inputFormat = Ceng::SHADER_DATATYPE::UNKNOWN;

	//nullOutput.target = CR_SHADER_TARGET0;
	temp->nullOutput.bufferFormat = Ceng::IMAGE_FORMAT::UNKNOWN;

	temp->desc = desc;

	for (auto k = 0; k < desc->InputAmount(); ++k)
	{
		temp->inputSemantics.push_back(inputSource[k]);
	}
	
	for (auto k = 0; k < desc->OutputAmount(); ++k)
	{
		temp->renderTargets.push_back(outputSource[k]);
	}

	if (desc->UniformArray() != nullptr)
	{
		for (auto k = 0; k < desc->UniformAmount(); ++k)
		{
			temp->uniformList.push_back(desc->UniformArray()[k]);
		}
	}

	CRESULT cresult = temp->ConfigureConstants();

	if (cresult != Ceng::CE_OK)
	{
		temp->Release();
		return cresult;
	}

	*out = temp;

	return CE_OK;
}

ExternalPixelShader::~ExternalPixelShader()
{

}

CRESULT ExternalPixelShader::GetInstances(std::vector<std::shared_ptr<PixelShaderContext>>& instances,
	const Ceng::UINT32 renderThreads)
{
	currentInstance = nextInstance;

	nextInstance = std::make_shared<PixelShaderContextCommon>(*currentInstance);

	instances = std::vector<std::shared_ptr<PixelShaderContext>>(renderThreads);

	for (Ceng::UINT32 k = 0; k < instances.size(); k++)
	{
		//CRESULT cresult = ExternalPixelShaderContext::GetInstance(currentInstance, instances[k]);

		PixelShaderInstance* instance = desc->GetInstance();

		if (instance == nullptr)
		{
			instances.clear();
			return CE_ERR_FAIL;
		}

		std::shared_ptr<ExternalPixelShaderContext> context =
			std::make_shared<ExternalPixelShaderContext>(instance, currentInstance);

		CRESULT cresult = context->Configure(currentInstance->shader->inputSemantics,
			currentInstance->shader->renderTargets);

		if (cresult != CE_OK)
		{
			return cresult;
		}

		instances.push_back(context);
	}
	
	return CE_OK;
}