#pragma once

#ifndef CENG_SWR_VERTEX_SHADER_INSTANCE_COMMON_H
#define CENG_SWR_VERTEX_SHADER_INSTANCE_COMMON_H

#include <vector>

#include <ceng/datatypes/aligned-buffer.h>

#include "texture-unit.h"

#include <ceng/datatypes/shader-uniform-desc.h>

#include "vshader-input-semantic.h"

namespace Ceng
{
	class CR_VertexShader;
	class CR_VertexFormat;
	class CR_FragmentFormat;

	class VertexStreamData;

	class VertexShaderInstanceCommon
	{
	public:

		CR_VertexShader* shader;

		CR_VertexFormat* vertexFormat;

		Ceng::UINT32 streamCount;

		VertexStreamData* vertexStreams;

		AlignedBuffer<Ceng::UINT8*> uniformPtr;

		AlignedBuffer<Ceng::UINT8> uniformBuffer;

		CR_FragmentFormat* fragmentFormat;
		Ceng::UINT32 fragmentSizeBytes;

		// Which vertex format variable each inputRegister corresponds to.		
		AlignedBuffer<Ceng::UINT32> sourceIndex;

		// Correct stride (stream specific) for each input register.
		AlignedBuffer<POINTER> inputSteps;

		// Stream specific base address for each input register.
		AlignedBuffer<POINTER> inputBaseAddress;

	public:

		VertexShaderInstanceCommon() = delete;

		VertexShaderInstanceCommon(CR_VertexShader* shader);

		VertexShaderInstanceCommon(const VertexShaderInstanceCommon& source);

		const CRESULT ConfigureInput(const std::vector<CR_vsInputSemantic>& inputSemantics);

		const CRESULT ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
			const Ceng::UINT32 bufferSize);
	};
}

#endif