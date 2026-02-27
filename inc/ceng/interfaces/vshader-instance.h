#pragma once

#ifndef CENG_VSHADER_INSTANCE_H
#define CENG_VSHADER_INSTANCE_H

#include "base-interface.h"

#include "../datatypes/return-val.h"

#include "../datatypes/vshader-input-desc.h"

#include "../swshader/vshader-input.h"
#include "../swshader/vshader-output.h"
#include "../swshader/vshader-uniform.h"

#include "../datatypes/fragment-cache-tag.h"

namespace Ceng
{
	class VertexShaderInstance : public BASE_INTERFACE
	{
	protected:

		~VertexShaderInstance() override
		{

		}

	public:

		virtual Vshader::VertexShaderInputRegister* GetInputs() = 0;
		virtual Ceng::UINT32 InputSize() = 0;

		virtual Vshader::VertexShaderOutputRegister* GetOutputs() = 0;
		virtual Ceng::UINT32 OutputSize() = 0;

		virtual Vshader::VertexShaderUniform* GetUniforms() = 0;
		virtual Ceng::UINT32 UniformSize() = 0;

		virtual POINTER* OutputBaseAddress() = 0;

		virtual CRESULT BasicConfig(Ceng::UINT32 fragmentSizeBytes,
			Ceng::POINTER* inputBaseAddress, Ceng::POINTER* inputSteps) = 0;

		virtual CRESULT ProcessVertexBatch(Ceng::UINT32 vertexCount,
			FragmentCacheTag* vertexIndex, 			
			UINT8* output,			
			Ceng::UINT32 threadId) = 0;
	};
}

#endif