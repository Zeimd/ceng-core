#pragma once

#ifndef CENG_PSHADER_DESCRIPTOR_H
#define CENG_PSHADER_DESCRIPTOR_H

#include "base-interface.h"

#include "../datatypes/pshader-input-desc.h"
#include "../datatypes/pshader-output-desc.h"
#include "../datatypes/shader-uniform-desc.h"

namespace Ceng
{
	class PixelShaderInstance;

	class PixelShaderDescriptor : public BASE_INTERFACE
	{
	protected:

		~PixelShaderDescriptor() override
		{

		}

	public:

		virtual Ceng::UINT32 InputAmount() = 0;

		virtual const PixelShaderInputDesc* InputArray() = 0;

		virtual Ceng::UINT32 UniformAmount() = 0;

		virtual const ShaderUniformDesc* UniformArray() = 0;

		virtual Ceng::UINT32 OutputAmount() = 0;

		virtual const PixelShaderOutputDesc* OutputArray() = 0;

		virtual PixelShaderInstance* GetInstance() = 0;
		
	};
}

#endif