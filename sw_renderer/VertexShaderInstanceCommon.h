#pragma once

#ifndef CENG_SWR_VERTEX_SHADER_INSTANCE_COMMON_H
#define CENG_SWR_VERTEX_SHADER_INSTANCE_COMMON_H

#include <vector>

#include <ceng/datatypes/aligned-buffer.h>

#include "texture-unit.h"

#include <ceng/datatypes/shader-uniform-desc.h>

#include <ceng/datatypes/vshader-input-desc.h>

#include "UniformBufferInstance.h"

namespace Ceng
{
	class CR_VertexShader;
	class CR_VertexFormat;
	class CR_FragmentFormat;

	class VertexStreamData;

	class UniformManager;

	class VertexShaderInstanceCommon
	{
	public:

		CR_VertexShader* shader;

		CR_VertexFormat* vertexFormat;

		Ceng::UINT32 streamCount;

		VertexStreamData* vertexStreams;

		UniformBufferInstance uniformBuffer;

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

		const CRESULT ConfigureInput(const std::vector<VertexShaderInputDesc>& inputSemantics);

		CRESULT ConfigureUniforms(const std::vector<ShaderUniformDesc>& uniformList,
			UniformManager& uniformManager);
	};
}

#endif