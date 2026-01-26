#pragma once

#ifndef CENG_SHADER_UNIFORM_DESC_H
#define CENG_SHADER_UNIFORM_DESC_H

#include "basic-types.h"
#include "../enums/shader-datatype.h"

namespace Ceng
{
	struct ShaderUniformDesc
	{
		const char* blockName;

		const char* name;

		Ceng::SHADER_DATATYPE::value dataType;

		// Address of the constant in the shader's
		// constant buffer.
		UINT32 bufferOffset;

		// Size of the constant in bytes.
		UINT32 size;

		ShaderUniformDesc()
		{
			blockName = nullptr;
		}
	};
}

#endif