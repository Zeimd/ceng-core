#pragma once

#ifndef CENG_VSHADER_OUTPUT_DESC_H
#define CENG_VSHADER_OUTPUT_DESC_H

#include "basic-types.h"

#include "../enums/shader-datatype.h"
#include "../enums/shader-semantic.h"

namespace Ceng
{
	namespace VERTEX_SHADER_OUTPUT_OPTIONS
	{
		enum value
		{
			/**
			 * If set, do not interpolate the variable
			 * over the triangle.
			 */
			CONSTANT = 1,

			/**
			 * If set, pixel shader doesn't use this
			 * variable, and it shouldn't be in the
			 * fragment format.
			 */
			NOWRITE = 2,

			/**
			 * Reading returns default value for given data type.
			 */
			DEFAULT = 4,

			FORCE_32B = 1 << 30,
		};
	
	};


	struct VertexShaderOutputDesc
	{
		Ceng::SHADER_SEMANTIC::value semantic;
		Ceng::SHADER_DATATYPE::value dataType;
		UINT32 options;

		VertexShaderOutputDesc()
		{

		}

		VertexShaderOutputDesc(Ceng::SHADER_SEMANTIC::value semantic, Ceng::SHADER_DATATYPE::value dataType)
			: semantic(semantic), dataType(dataType), options(0)
		{

		}
	};
}

#endif