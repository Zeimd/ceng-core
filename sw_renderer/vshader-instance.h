/*****************************************************************************
*
* vshader-instance.h
*
* By Jari Korkala 8/2014
*
*****************************************************************************/

#ifndef CRENDER_VSHADER_INSTANCE_H
#define CRENDER_VSHADER_INSTANCE_H

#include <memory>
#include <array>

#include <ceng/datatypes/aligned-buffer.h>
#include <ceng/datatypes/ring-buffer.h>

#include "vshader-input.h"
#include "vshader-output.h"
#include "vshader-uniform.h"

#include <ceng/datatypes/vshader-input-desc.h>

#include "future.h"

namespace Ceng
{
	namespace Experimental
	{
		class Task_Clipper;
	};

	class DrawBatch;

	class CR_vsInputSemantic;

	class CR_VertexShader;

	class CR_VertexFormat;

	class CR_FragmentFormat;

	class VertexStreamData;

	class LockingStage;

	class VertexShaderInstanceCommon;

	class CR_VertexShaderInstance
	{
	public:

		std::shared_ptr<VertexShaderInstanceCommon> common;

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

		CR_VertexShaderInstance() = delete;

		CR_VertexShaderInstance(std::shared_ptr<VertexShaderInstanceCommon>& common);

		//CR_VertexShaderInstance(const CR_VertexShaderInstance &source);

		virtual ~CR_VertexShaderInstance();

		CRESULT Configure(const std::vector<VertexShaderInputDesc>& inputSemantics);

		virtual const CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
												LockingStage *outputQueue);

		virtual const CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch, Ceng::UINT32 threadId,
			Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future);

		virtual void ShaderFunction();


	};
}

#endif