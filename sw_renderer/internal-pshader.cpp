#include "internal-pshader.h"

#include "internal-pshader-context.h"

using namespace Ceng;

CRESULT InternalPixelShader::GetInstances(std::vector<std::shared_ptr<PixelShaderContext>>& instances,
	const Ceng::UINT32 renderThreads)
{
	// Create an instance using *nextState*

	currentInstance = nextInstance;

	nextInstance = std::make_shared<PixelShaderContextCommon>(*currentInstance);

	instances = std::vector<std::shared_ptr<PixelShaderContext>>(renderThreads);

	for (Ceng::UINT32 k = 0; k < instances.size(); k++)
	{
		CRESULT cresult = InternalPixelShaderContext::GetInstance(currentInstance, instances[k]);

		if (cresult != CE_OK)
		{
			return cresult;
		}
	}

	return CE_OK;
}