#include "extern-pshader.h"

using namespace Ceng;

ExternalPixelShader::ExternalPixelShader()
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

	temp->nextInstance = std::make_shared< Ceng::PixelShaderInstanceCommon>(temp);

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

	*out = temp;

	return CE_OK;
}

ExternalPixelShader::~ExternalPixelShader()
{

}

CRESULT ExternalPixelShader::GetInstances(std::vector<std::shared_ptr<PixelShaderInstance>>& instances,
	const Ceng::UINT32 renderThreads)
{
	return CE_ERR_UNIMPLEMENTED;
}