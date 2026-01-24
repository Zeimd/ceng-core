#include "extern-pshader-context.h"

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
	std::vector<PixelShaderOutputDesc>& renderTargets)
{
	CRESULT cresult;

	cresult = instance->ConfigureInput(&inputSemantics[0], inputSemantics.size());

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = instance->ConfigureOutput(&renderTargets[0], renderTargets.size());

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = instance->SetFragmentFormat(&inputSemantics[0], inputSemantics.size(),
		&renderTargets[0], renderTargets.size());

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = instance->SetRenderTargets(&renderTargets[0], renderTargets.size());

	if (cresult != CE_OK)
	{
		return cresult;
	}

	cresult = instance->ConfigureLocals();

	if (cresult != CE_OK)
	{
		return cresult;
	}

	return CE_OK;
}

CRESULT ExternalPixelShaderContext::ProcessQuads(Task_PixelShader* batch, const Ceng::INT32 threadId)
{
	return CE_OK;
}

CRESULT ExternalPixelShaderContext::ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId)
{
	return CE_OK;
}
