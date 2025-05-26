#pragma once

#ifndef CENG_VSHADER_DESCRIPTOR_H
#define CENG_VSHADER_DESCRIPTOR_H

#include "base-interface.h"

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

		virtual VertexShaderInstance* GetInstance() = 0;
	};
}

#endif