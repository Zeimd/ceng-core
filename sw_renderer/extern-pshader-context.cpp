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

CRESULT ExternalPixelShaderContext::ConfigureInput(std::vector<PixelShaderInputDesc>& inputSemantics)
{
	return instance->ConfigureInput(&inputSemantics[0], inputSemantics.size());
}

CRESULT ExternalPixelShaderContext::ConfigureOutput(std::vector<PixelShaderOutputDesc>& renderTargets)
{
	return instance->ConfigureOutput(&renderTargets[0], renderTargets.size());
}

CRESULT ExternalPixelShaderContext::ConfigureLocals()
{
	return instance->ConfigureLocals();
}

CRESULT ExternalPixelShaderContext::SetFragmentFormat(const std::vector<PixelShaderInputDesc>& inputSemantics,
	const std::vector<PixelShaderOutputDesc>& targetSemantics)
{
	return instance->SetFragmentFormat(&inputSemantics[0], inputSemantics.size(),
		&targetSemantics[0], targetSemantics.size());
}

CRESULT ExternalPixelShaderContext::SetRenderTargets(const std::vector<PixelShaderOutputDesc>& targetSemantics)
{
	return instance->SetRenderTargets(&targetSemantics[0], targetSemantics.size());
}

CRESULT ExternalPixelShaderContext::ProcessQuads(Task_PixelShader* batch, const Ceng::INT32 threadId)
{
	return CE_OK;
}

CRESULT ExternalPixelShaderContext::ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId)
{
	return CE_OK;
}
