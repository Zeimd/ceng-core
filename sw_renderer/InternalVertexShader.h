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

#include <ceng/datatypes/aligned-buffer.h>

#include <ceng/swshader/pshader-input.h>
#include <ceng/swshader/vshader-input.h>

#include "cr-vertex-shader.h"

#include "crender-base.h"

#include "fragment-var.h"
#include "fragment-format.h"

#include "vshader-output.h"

#include "vshader-wrapper.h"

#include "UniformManager.h"

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