#pragma once

#ifndef CENG_SWRENDER_VERTEX_SHADER_H
#define CENG_SWRENDER_VERTEX_SHADER_H

#include <memory>
#include <vector>

#include <ceng/interfaces/vertex-shader.h>
#include <ceng/datatypes/aligned-buffer.h>

#include <ceng/datatypes/vshader-input-desc.h>
#include <ceng/datatypes/vshader-output-desc.h>
#include <ceng/datatypes/shader-uniform-desc.h>

#include "vshader-wrapper.h"
#include "UniformManager.h"

#include <ceng/swshader/vshader-input.h>
#include <ceng/swshader/vshader-output.h>

namespace Ceng
{
	class VertexShaderInstanceCommon;
	class VertexShaderContext;
	class CR_VertexFormat;
	class VertexStreamData;
	class CR_FragmentFormat;

	class CR_VertexShader : public VertexShader
	{
	public:

		Ceng::BOOL compiled;

		VertexShaderWrapper wrapper;

		std::vector<ShaderUniformDesc> uniformList;

		UniformManager uniformManager;

		Ceng::UINT32 uniformBufferSize;

		Ceng::UINT32 cacheLine;

		// List of input semantics the shader uses.
		std::vector<VertexShaderInputDesc> inputSemantics;

		// List of output semantics the shader can use.
		std::vector<VertexShaderOutputDesc> outputSemantics;

		// Used to temporarily store semantics that appear both in vertex shader
		// output and pixel shader input. POSITION-semantic excluded.
		std::vector<VertexShaderOutputDesc> linkedOutput;

		std::shared_ptr<VertexShaderInstanceCommon> nextInstance;
		std::shared_ptr<VertexShaderInstanceCommon> currentInstance;

		// Flags for input semantics the shader uses.
		UINT32 inputFlags;

		Vshader::CR_VertexShaderInput nullInput;
		Vshader::CR_VertexShaderOutput nullOutput;

		AlignedBuffer<Ceng::UINT8> nullBuffer;
		POINTER nullBufferPtr;

	public:

		CR_VertexShader();

		~CR_VertexShader() override;

		void Release() override;

		const CRESULT ReadUniform(const Ceng::UINT32 index, void* destBuffer);

		const CRESULT WriteUniform(const Ceng::UINT32 index, void* sourceBuffer);

		CRESULT SetVertexFormat(CR_VertexFormat* format);

		CRESULT SetVertexStreams(UINT32 streamCount, VertexStreamData* streamList);

		CRESULT SetFragmentFormat(CR_FragmentFormat* format);

		CRESULT ConfigureConstants();
		CRESULT ConfigureInput();

		CRESULT GetConstant(const char* variableName,
			Ceng::UINT32& out_index, Ceng::SHADER_DATATYPE::value& out_type);

		const Ceng::CRESULT GetLog(Ceng::StringUtf8** log) override;

		const Ceng::BOOL Compiled() override;

		virtual CRESULT GetInstances(std::vector<std::shared_ptr<VertexShaderContext>>& instances,
			const Ceng::UINT32 renderThreads) = 0;
	};
}

#endif