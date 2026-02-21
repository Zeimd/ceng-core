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

		//************************************
		// Input state


		/**
		 * Semantic links to vertex buffer data. Used
		 * in ShaderFunction().
		 */
		AlignedBuffer<CR_vsInputRegister> inputRegisters;
		

		// Input references
		CR_vsInputRegister* IN_POSITION;

		CR_vsInputRegister* IN_NORMAL;
		CR_vsInputRegister* IN_BINORMAL;
		CR_vsInputRegister* IN_TANGENT;

		CR_vsInputRegister* IN_COLOR0;
		CR_vsInputRegister* IN_COLOR1;

		CR_vsInputRegister* IN_TEXCOORD0;
		CR_vsInputRegister* IN_TEXCOORD1;
		CR_vsInputRegister* IN_TEXCOORD2;
		CR_vsInputRegister* IN_TEXCOORD3;
		CR_vsInputRegister* IN_TEXCOORD4;
		CR_vsInputRegister* IN_TEXCOORD5;
		CR_vsInputRegister* IN_TEXCOORD6;
		CR_vsInputRegister* IN_TEXCOORD7;

		std::array<Vshader::VertexShaderOutputRegister, 5> outputRegisters;

		Vshader::OutFloat4 outPosition;
		Vshader::OutFloat4 outNormal;
		Vshader::OutFloat4 outTangent;
		Vshader::OutFloat2 outTexCoord0;
		Vshader::OutFloat2 outTexCoord1;

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