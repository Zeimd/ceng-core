#pragma once

#ifndef CENG_SWRENDER_EXTERN_VSHADER_H
#define CENG_SWRENDER_EXTERN_VSHADER_H

#include <ceng/interfaces/vshader-descriptor.h>

#include "cr-vertex-shader.h"

namespace Ceng
{
	class ExternalVertexShader : public CR_VertexShader
	{
	public:

		VertexShaderDescriptor* desc;

	public:
		ExternalVertexShader();

		static CRESULT Create(VertexShaderDescriptor* desc, ExternalVertexShader** out);

		~ExternalVertexShader() override;

		CRESULT GetInstances(std::vector<std::shared_ptr<VertexShaderContext>>& instances,
			const Ceng::UINT32 renderThreads) override;
	};
}

#endif