#include "internal-pshader.h"

using namespace Ceng;

CRESULT InternalPixelShader::GetInstances(std::vector<std::shared_ptr<PixelShaderInstance>>& instances,
	const Ceng::UINT32 renderThreads)
{
	// Create an instance using *nextState*

	currentInstance = nextInstance;

	nextInstance = std::make_shared<PixelShaderInstanceCommon>(*currentInstance);

	instances = std::vector<std::shared_ptr<PixelShaderInstance>>(renderThreads);

	for (Ceng::UINT32 k = 0; k < instances.size(); k++)
	{
		CRESULT cresult = PixelShaderInstance::GetInstance(currentInstance, instances[k]);

		if (cresult != CE_OK)
		{
			return cresult;
		}
	}

	return CE_OK;
}