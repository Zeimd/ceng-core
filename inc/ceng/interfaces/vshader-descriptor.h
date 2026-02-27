#pragma once

#ifndef CENG_VSHADER_DESCRIPTOR_H
#define CENG_VSHADER_DESCRIPTOR_H

#include "base-interface.h"

#include "../datatypes/vshader-input-desc.h"
#include "../datatypes/vshader-output-desc.h"
#include "../datatypes/shader-uniform-desc.h"

#include "../swshader/vshader-input.h"
#include "../swshader/vshader-output.h"

namespace Ceng
{
	class VertexShaderInstance;

	class VertexShaderDescriptor : public BASE_INTERFACE
	{
	protected:

		~VertexShaderDescriptor() override
		{

		}

	public:

		virtual Ceng::UINT32 InputAmount() = 0;

		virtual const VertexShaderInputDesc* InputArray() = 0;

		virtual Ceng::UINT32 UniformAmount() = 0;

		virtual const ShaderUniformDesc* UniformArray() = 0;

		virtual Ceng::UINT32 OutputAmount() = 0;

		virtual const VertexShaderOutputDesc* OutputArray() = 0;

		virtual VertexShaderInstance* GetInstance(Ceng::UINT32 cacheLine, 
			Vshader::CR_VertexShaderInput* nullInput,
			Vshader::CR_VertexShaderOutput* nullOutput) = 0;
	};
}

#endif