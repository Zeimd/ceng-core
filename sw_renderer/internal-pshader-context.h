#pragma once

#ifndef CENG_SWR_INTERNAL_PSHADER_INSTANCE_H
#define CENG_SWR_INTERNAL_PSHADER_INSTANCE_H

#include <array>
#include <ceng/datatypes/aligned-buffer.h>

#include "pshader-context.h"
#include <ceng/swshader/pshader-uniform.h>

#include <ceng/swshader/pshader-input.h>
#include <ceng/swshader/pshader-output.h>

namespace Ceng
{
	class InternalPixelShaderContext : public PixelShaderContext
	{
	public:

		POINTER quadTargetStart;

		/**
		 * Temporary buffer for current quad.
		 */
		AlignedBuffer<Ceng::UINT8> quadBuffer;

		// w for each pixel in a quad (4xFLOAT or 4xDOUBLE)
		// must be 16-byte aligned
		AlignedBuffer<Ceng::UINT8> perspectiveTemp;

		/**
		 * Pixel coverage mask for render target writes.
		 * Accessed through pointers.
		 */
		Ceng::UINT32 coverageAddress;

		POINTER stepBufferPtr;

		// Add input variables in the same order they appear in PixelShaderDeclaration.
		std::array<Pshader::PixelShaderInputRegister,4> inputRegisters;

		Pshader::InFloat4 normal;
		Pshader::InFloat4 tangent;
		Pshader::InFloat2 texCoord0;
		Pshader::InFloat2 texCoord1;

		std::array<Pshader::PixelShaderUniform, 1> uniforms;

		Pshader::UniformSampler2d diffuseTex;

		std::array<Pshader::PixelShaderOutputRegister, 10> outputRegisters;

		Pshader::OutFloat OUT_STENCIL;
		Pshader::OutFloat OUT_DEPTH;

		Pshader::OutFloat4 OUT_TARGET0;
		Pshader::OutFloat4 OUT_TARGET1;
		Pshader::OutFloat4 OUT_TARGET2;
		Pshader::OutFloat4 OUT_TARGET3;
		Pshader::OutFloat4 OUT_TARGET4;
		Pshader::OutFloat4 OUT_TARGET5;
		Pshader::OutFloat4 OUT_TARGET6;
		Pshader::OutFloat4 OUT_TARGET7;

	public:

		InternalPixelShaderContext(std::shared_ptr<PixelShaderContextCommon>& common);

		~InternalPixelShaderContext() override;

		static CRESULT GetInstance(Ceng::UINT32 index,
			std::shared_ptr<PixelShaderContextCommon>& common, std::shared_ptr<PixelShaderContext>& out);

		CRESULT Configure(std::vector<PixelShaderInputDesc>& inputSemantics,
			std::vector<PixelShaderOutputDesc>& renderTargets,
			UniformManager& manager) override;

		void ShaderFunction(const FLOAT32* perspective, const FLOAT32* invertW,
			const Ceng::INT32 coverage, const Ceng::INT32 threadId);

		CRESULT ProcessQuads(Task_PixelShader* batch, const Ceng::INT32 threadId) override;

		CRESULT ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId) override;
	};
}

#endif