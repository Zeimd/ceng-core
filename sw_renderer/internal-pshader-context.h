#pragma once

#ifndef CENG_SWR_INTERNAL_PSHADER_INSTANCE_H
#define CENG_SWR_INTERNAL_PSHADER_INSTANCE_H

#include <array>

#include "pshader-context.h"

namespace Ceng
{
	struct PixelShaderInputRegister
	{
		Pshader::CR_PixelShaderInput* variable;
	};

	struct PixelShaderOutputRegister
	{
		CR_psOutputRegister* variable;
		PSHADER_OUTPUT_SEMANTIC::value target;
	};

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
		POINTER coverageAddress;

		POINTER inputBaseAddress;

		POINTER stepBufferPtr;

		std::array<PixelShaderInputRegister,4> inputRegisters;

		Pshader::InFloat4 normal;
		Pshader::InFloat4 tangent;
		Pshader::InFloat2 texCoord0;
		Pshader::InFloat2 texCoord1;

		std::array<PixelShaderOutputRegister, 10> outputRegisters;

		CR_psOutputRegister OUT_STENCIL;
		CR_psOutputRegister OUT_DEPTH;

		CR_psOutputRegister OUT_TARGET0;
		CR_psOutputRegister OUT_TARGET1;
		CR_psOutputRegister OUT_TARGET2;
		CR_psOutputRegister OUT_TARGET3;
		CR_psOutputRegister OUT_TARGET4;
		CR_psOutputRegister OUT_TARGET5;
		CR_psOutputRegister OUT_TARGET6;
		CR_psOutputRegister OUT_TARGET7;

		Pshader::SampleTexture2D sample2d;

		TextureUnit diffuseTexUnit;

	public:

		InternalPixelShaderContext(std::shared_ptr<PixelShaderContextCommon>& common);

		~InternalPixelShaderContext() override;

		static CRESULT GetInstance(std::shared_ptr<PixelShaderContextCommon>& common, std::shared_ptr<PixelShaderContext>& out);

		CRESULT Configure(std::vector<PixelShaderInputDesc>& inputSemantics,
			std::vector<PixelShaderOutputDesc>& renderTargets) override;

		void ShaderFunction(const FLOAT32* perspective, const FLOAT32* invertW,
			const Ceng::INT32 coverage, const Ceng::INT32 threadId);

		CRESULT ProcessQuads(Task_PixelShader* batch, const Ceng::INT32 threadId) override;

		CRESULT ProcessQuads(Experimental::Task_PixelShader* batch, const Ceng::INT32 threadId) override;
	};
}

#endif