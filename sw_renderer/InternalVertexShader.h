/*****************************************************************************
*
* cr-vshader.h
*
* By Jari Korkala 2/2012
*
* Vertex shader declarations moved here from "crender.h"
*
*****************************************************************************/

#pragma once

#ifndef CENG_SWRENDER_INTERNAL_VERTEX_SHADER_H
#define CENG_SWRENDER_INTERNAL_VERTEX_SHADER_H

#include <memory>
#include <vector>

#include "cr-vertex-shader.h"

namespace Ceng
{
	class VertexShaderContext;

	class InternalVertexShader : public CR_VertexShader
	{
	public:

	public:
	
		InternalVertexShader()
			: CR_VertexShader()
		{

		}

		~InternalVertexShader() override
		{

		}
	

	public:		

		CRESULT GetInstances(std::vector<std::shared_ptr<VertexShaderContext>>& instances,
			const Ceng::UINT32 renderThreads) override;
	};

} // Namespace end

#endif // Include guard