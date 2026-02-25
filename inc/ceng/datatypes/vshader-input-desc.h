#pragma once 

#ifndef CENG_VSHADER_INPUT_DESC_H
#define CENG_VSHADER_INPUT_DESC_H

#include "basic-types.h"

#include "../enums/shader-semantic.h"

namespace Ceng
{
	struct VertexShaderInputDesc
	{
		Ceng::SHADER_SEMANTIC::value semantic;

		// Which variable in the vertex format this corresponds to.
		Ceng::INT32 sourceIndex;

		Ceng::UINT32 options;

		VertexShaderInputDesc()
		{

		}

		VertexShaderInputDesc(Ceng::SHADER_SEMANTIC::value semantic)
			: semantic(semantic), sourceIndex(-1), options(0)
		{

		}
	};
}

#endif