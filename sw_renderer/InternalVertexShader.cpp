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

#include "vshader-context.h"
#include "InternalVshaderContext.h"

#include "VertexShaderInstanceCommon.h"

using namespace Ceng;

CRESULT InternalVertexShader::GetInstances(std::vector<std::shared_ptr<VertexShaderContext>>& instances,
	const Ceng::UINT32 renderThreads)
{
	// Create an instance using *nextState*

	nextInstance->ConfigureInput(inputSemantics);

	currentInstance = nextInstance;

	nextInstance = std::make_shared<VertexShaderInstanceCommon>(*currentInstance);
		
	instances = std::vector<std::shared_ptr<VertexShaderContext>>(renderThreads);

	for (Ceng::UINT32 k = 0; k < instances.size(); k++)
	{
		instances[k] = std::make_shared<InternalVshaderContext>(currentInstance);

		instances[k]->Configure();
	}

	return CE_OK;
}

