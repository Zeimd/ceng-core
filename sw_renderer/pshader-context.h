/*****************************************************************************
*
* pshader-instance.h
*
* Created By Jari Korkala 2/9/2014
*
*****************************************************************************/

#ifndef CRENDER_PSHADER_INSTANCE_H
#define CRENDER_PSHADER_INSTANCE_H

#include <memory>
#include <ceng/datatypes/aligned-buffer.h>

#include <ceng/datatypes/pshader-input-desc.h>
#include <ceng/swshader/pshader-input.h>

#include <ceng/datatypes/pshader-output-desc.h>
#include "pshader-output.h"

#include "rtarget-data.h"

#include "texture-unit.h"

#include <ceng/datatypes/shader-uniform-desc.h>

#include "PixelShaderContextCommon.h"

namespace Ceng::Experimental
{
	class Task_PixelShader;
}

namespace Ceng
{
	class Task_PixelShader;

	class CR_ShaderConstant;

	class CR_PixelShader;

	class CR_PixelShaderTarget;

	class CR_QuadFormat;

	class ShaderLinkInstance;

	class PixelShaderContext
	{
	public:

		std::shared_ptr<PixelShaderContextCommon> common;

	protected:

		PixelShaderContext()
		{

		}

	public:		

		virtual ~PixelShaderContext()
		{

		}		

		virtual CRESULT Configure(std::vector<PixelShaderInputDesc>& inputSemantics,
			std::vector<PixelShaderOutputDesc>& renderTargets,
			UniformManager& manager) = 0;

		virtual CRESULT ProcessQuads(Task_PixelShader *batch,const Ceng::INT32 threadId) = 0;

		virtual CRESULT ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId) = 0;		
	};
}

#endif