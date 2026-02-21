/*****************************************************************************
*
* cr-vshader.h
*
* By Jari Korkala 2/2012
*
* Vertex shader declarations moved here from "crender.h"
*
*****************************************************************************/

#ifndef _CENG_CR_VSHADER_H
#define _CENG_CR_VSHADER_H

#include <memory>
#include <vector>

#include <ceng/interfaces/vertex-shader.h>

#include <ceng/datatypes/aligned-buffer.h>

#include <ceng/datatypes/vshader-input-desc.h>
#include <ceng/datatypes/vshader-output-desc.h>

#include <ceng/swshader/pshader-input.h>

#include <ceng/datatypes/shader-uniform-desc.h>

// Vertex shader interface declaration
#include "crender-base.h"

#include "fragment-var.h"
#include "fragment-format.h"

#include "vshader-input.h"
#include "vshader-output.h"

#include "vshader-wrapper.h"

namespace Ceng
{
	//****************************************************************************
	// Vertex shader interface

	class VertexStreamData;

	class CR_VertexFormat;

	class CR_FragmentFormat;

	class DrawBatch;

	class CR_VertexShaderInstance;

	class ShaderConstant;

	class CR_ShaderConstant;

	class VertexShaderInstanceCommon;

	class CR_VertexShaderInstance;

	class CR_VertexShader : public Ceng::VertexShader
	{
	public:

		Ceng::BOOL compiled;

		VertexShaderWrapper wrapper;

		std::vector<ShaderUniformDesc> uniformList;

		Ceng::UINT32 uniformBufferSize;

		Ceng::UINT32 cacheLine;

		//UINT32 vertexSizeBytes;
	
		/**
		 * List of input semantics the shader uses.
		 */
		std::vector<VertexShaderInputDesc> inputSemantics;

		/**
		 * List of output semantics the shader can use.
		 */
		std::vector<VertexShaderOutputDesc> outputSemantics;

		/**
		 * Used to temporarily store semantics that appear both in vertex shader
		 * output and pixel shader input. POSITION-semantic excluded.
		 */
		std::vector<VertexShaderOutputDesc> linkedOutput;

		std::shared_ptr<VertexShaderInstanceCommon> nextInstance;
		std::shared_ptr<VertexShaderInstanceCommon> currentInstance;

		/**
		 * Flags for input semantics the shader uses.
		 */
		UINT32 inputFlags;

		CR_vsInputRegister nullInput;
		Vshader::CR_VertexShaderOutput nullOutput;

	protected:

		AlignedBuffer<Ceng::UINT8> nullBuffer;
		POINTER nullBufferPtr;

	public:
	
		CR_VertexShader();
		~CR_VertexShader() override;

		void Release() override;

		CRESULT GetConstant(const char* variableName,
			Ceng::UINT32& out_index, Ceng::SHADER_DATATYPE::value& out_type);

		const Ceng::CRESULT GetLog(Ceng::StringUtf8** log) override;

		const Ceng::BOOL Compiled() override;

	public:

		const CRESULT ReadUniform(const Ceng::UINT32 index,void *destBuffer);

		const CRESULT WriteUniform(const Ceng::UINT32 index,void *sourceBuffer);

		CRESULT SetVertexFormat(CR_VertexFormat *format);

		CRESULT SetVertexStreams(UINT32 streamCount,VertexStreamData *streamList);

		CRESULT SetFragmentFormat(CR_FragmentFormat *format);

		UINT32 GetDataSize(const Ceng::SHADER_DATATYPE::value datatype);

		const CRESULT GetInstances(std::vector<std::shared_ptr<CR_VertexShaderInstance>>& instances,
			const Ceng::UINT32 renderThreads);

		CRESULT ConfigureConstants();
		CRESULT ConfigureInput();
	
		CRESULT ConfigureOutput();

	protected:

	};

} // Namespace end

#endif // Include guard