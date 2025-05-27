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
#include <ceng/datatypes/aligned-buffer.h>
#include <ceng/datatypes/ring-buffer.h>

#include "vshader-input.h"
#include "vshader-output.h"

#include <ceng/datatypes/shader-uniform-desc.h>

#include "SimpleStage.h"
#include "task-clipper.h"

#include "VertexShaderInstanceCommon.h"

namespace Ceng
{
	class DrawBatch;

	class CR_vsInputSemantic;

	class CR_VertexShader;

	class CR_VertexFormat;

	class CR_FragmentFormat;

	class VertexStreamData;

	class LockingStage;

	class CR_VertexShaderInstance
	{
	public:

		std::shared_ptr<VertexShaderInstanceCommon> common;

		//************************************
		// Input state


		/**
		 * Semantic links to vertex buffer data. Used
		 * in ShaderFunction().
		 */
		AlignedBuffer<CR_vsInputRegister> inputRegisters;
		
	

		//************************************
		// Output state
				
		/**
		 * Semantic links to fragment output buffer.
		 * Used in ShaderFunction().
		 */
		AlignedBuffer<CR_vsOutputRegister> outputRegisters;

		/**
		 * Pointer to current output fragment. Output registers
		 * access this value through pointers.
		 */
		POINTER outputBaseAddress;

		// Input references
		CR_vsInputRegister *IN_POSITION;
	
		CR_vsInputRegister *IN_NORMAL;
		CR_vsInputRegister *IN_BINORMAL;
		CR_vsInputRegister *IN_TANGENT;

		CR_vsInputRegister *IN_COLOR0;
		CR_vsInputRegister *IN_COLOR1;
	
		CR_vsInputRegister *IN_TEXCOORD0;
		CR_vsInputRegister *IN_TEXCOORD1;
		CR_vsInputRegister *IN_TEXCOORD2;
		CR_vsInputRegister *IN_TEXCOORD3;
		CR_vsInputRegister *IN_TEXCOORD4;
		CR_vsInputRegister *IN_TEXCOORD5;
		CR_vsInputRegister *IN_TEXCOORD6;
		CR_vsInputRegister *IN_TEXCOORD7;

		// Output references
		CR_vsOutputRegister *OUT_POSITION;

		CR_vsOutputRegister *OUT_NORMAL;
		CR_vsOutputRegister *OUT_BINORMAL;
		CR_vsOutputRegister *OUT_TANGENT;

		CR_vsOutputRegister *OUT_COLOR0;
		CR_vsOutputRegister *OUT_COLOR1;

		CR_vsOutputRegister *OUT_TEXCOORD0;
		CR_vsOutputRegister *OUT_TEXCOORD1;
		CR_vsOutputRegister *OUT_TEXCOORD2;
		CR_vsOutputRegister *OUT_TEXCOORD3;
		CR_vsOutputRegister *OUT_TEXCOORD4;
		CR_vsOutputRegister *OUT_TEXCOORD5;
		CR_vsOutputRegister *OUT_TEXCOORD6;
		CR_vsOutputRegister *OUT_TEXCOORD7;		

	public:

		CR_VertexShaderInstance() = delete;

		CR_VertexShaderInstance(std::shared_ptr<VertexShaderInstanceCommon>& common);

		//CR_VertexShaderInstance(const CR_VertexShaderInstance &source);

		virtual ~CR_VertexShaderInstance();

		const CRESULT ConfigureInput(const std::vector<VertexShaderInputDesc> &inputSemantics);
		
		const CRESULT SetFragmentFormat();

		virtual const CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
												LockingStage *outputQueue);

		virtual const CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch, Ceng::UINT32 threadId,
			Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future);

		virtual void ShaderFunction();


	};
}

#endif