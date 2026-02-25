#pragma once

#ifndef CENG_SWRENDER_INTERNAL_VSHADER_CONTEXT_H
#define CENG_SWRENDER_INTERNAL_VSHADER_CONTEXT_H

#include <array>

#include "vshader-context.h"

#include <ceng/swshader/vshader-input.h>
#include "vshader-output.h"
#include "vshader-uniform.h"

namespace Ceng
{
	class InternalVshaderContext : public VertexShaderContext
	{
	public:
		// Pointer to current output fragment. Output registers
		// access this value through a pointer.
		POINTER outputBaseAddress;

		std::array<Vshader::VertexShaderInputRegister, 5> inputRegisters;

		Vshader::InFloat4 inPosition;
		Vshader::InFloat4 inNormal;
		Vshader::InFloat4 inTangent;
		Vshader::InFloat2 inTexCoord0;
		Vshader::InFloat2 inTexCoord1;

		std::array<Vshader::VertexShaderOutputRegister, 5> outputRegisters;

		Vshader::OutFloat4 outPosition;
		Vshader::OutFloat4 outNormal;
		Vshader::OutFloat4 outTangent;
		Vshader::OutFloat2 outTexCoord0;
		Vshader::OutFloat2 outTexCoord1;

		std::array<Vshader::VertexShaderUniform, 1> uniforms;

		Vshader::UniformMat4x4 fullVertexTransform;

	public:

		InternalVshaderContext(std::shared_ptr<VertexShaderInstanceCommon>& common);

		~InternalVshaderContext() override;

		CRESULT Configure(const std::vector<VertexShaderInputDesc>& inputSemantics) override;

		CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
			LockingStage* outputQueue) override;

		CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch, Ceng::UINT32 threadId,
			Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future) override;

		void ShaderFunction();
	};

}

#endif