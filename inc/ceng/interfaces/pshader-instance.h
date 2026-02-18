#pragma once

#ifndef CENG_PSHADER_INSTANCE_H
#define CENG_PSHADER_INSTANCE_H

#include "../datatypes/return-val.h"

#include "base-interface.h"

#include "../datatypes/pshader-input-desc.h"
#include "../datatypes/pshader-output-desc.h"

#include "../swshader/pshader-input.h"
#include "../swshader/pshader-output.h"
#include "../swshader/pshader-uniform.h"

#include "../datatypes/pshader-quad-batch.h"

#include "../datatypes/pshader-triangle-data.h"

#include "../swshader/RenderTargetService.h"

namespace Ceng
{
	class PixelShaderInstance : public BASE_INTERFACE
	{
	protected:

		~PixelShaderInstance() override
		{

		}

	public:

		virtual CRESULT BasicConfig(Ceng::UINT32 quadSize, Ceng::UINT32 cacheLine, Ceng::POINTER quadTargetStart) = 0;

		virtual Pshader::PixelShaderInputRegister* GetInputs() = 0;
		virtual Ceng::UINT32 InputSize() = 0;

		virtual Pshader::PixelShaderOutputRegister* GetOutputs() = 0;
		virtual Ceng::UINT32 OutputSize() = 0;

		virtual Pshader::PixelShaderUniform* GetUniforms() = 0;
		virtual Ceng::UINT32 UniformSize() = 0;

		virtual Ceng::UINT8* QuadBuffer() = 0;

		virtual Ceng::POINTER* StepBufferPtr() = 0;

		virtual void* PerpectiveTemp() = 0;

		virtual Ceng::UINT32* CoverageAddress() = 0;

		virtual void SetRenderTargetService(Pshader::RenderTargetService* service) = 0;

		virtual void ProcessConfig(
			UINT32 quadFloatOffset,
			UINT32 quadDoubleOffset,
			UINT32 quadTargetOffset,
			UINT32 floatBlockSize,
			UINT32 doubleBlockSize) = 0;
				
		virtual CRESULT ProcessQuads(SWRender::PixelShaderQuadBatch* batch, Ceng::UINT32 batchSize, 
			SWRender::PixelShaderTriangleData* triangleData, Ceng::UINT32 threadId) = 0;
	};
}

#endif