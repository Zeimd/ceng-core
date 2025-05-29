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
	return CE_OK;
}

CRESULT ExternalPixelShaderContext::ConfigureOutput(std::vector<PixelShaderOutputDesc>& renderTargets)
{
	return CE_OK;
}

CRESULT ExternalPixelShaderContext::ConfigureLocals()
{
	return CE_OK;
}

CRESULT ExternalPixelShaderContext::SetFragmentFormat(const std::vector<PixelShaderInputDesc>& inputSemantics,
	const std::vector<PixelShaderOutputDesc>& targetSemantics)
{
	return CE_OK;
}

CRESULT ExternalPixelShaderContext::SetRenderTargets(const std::vector<PixelShaderOutputDesc>& targetSemantics)
{
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
