/*****************************************************************************
*
* cr-vertex-shader.cpp
*
* --------------------------------------------------
* Jari Korkala 8/2014
*
* - Renamed to cr-vertex-shader.cpp
*
* --------------------------------------------------
*
* Created By Jari Korkala 9/2011
*
* Implements CR_VertexShader
*
*
*****************************************************************************/

#include <ceng/math/ce-matrix.h>

#include "InternalVertexShader.h"

#include "vshader-instance.h"

#include "VertexShaderInstanceCommon.h"

using namespace Ceng;

CRESULT InternalVertexShader::GetInstances(std::vector<std::shared_ptr<CR_VertexShaderInstance>>& instances,
	const Ceng::UINT32 renderThreads)
{
	// Create an instance using *nextState*

	nextInstance->ConfigureInput(inputSemantics);

	currentInstance = nextInstance;

	nextInstance = std::make_shared<VertexShaderInstanceCommon>(*currentInstance);
		
	instances = std::vector<std::shared_ptr<CR_VertexShaderInstance>>(renderThreads);

	for (Ceng::UINT32 k = 0; k < instances.size(); k++)
	{
		instances[k] = std::make_shared<CR_VertexShaderInstance>(currentInstance);

		instances[k]->Configure(inputSemantics);
	}

	return CE_OK;
}

