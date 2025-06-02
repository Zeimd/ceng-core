#pragma once

#ifndef CENG_SWR_QUAD_VARIABLE_H
#define CENG_SWR_QUAD_VARIABLE_H

#include <ceng/enums/shader-datatype.h>
#include <ceng/enums/shader-semantic.h>

#include <ceng/datatypes/basic-types.h>

namespace Ceng
{
	class CR_QuadVariable
	{
	public:
		Ceng::SHADER_SEMANTIC::value semantic;
		Ceng::SHADER_DATATYPE::value format;

		/**
		 * Position within vertex shader output struct.
		 */
		UINT32 fragmentOffset;

		/**
		 * Position within quad struct.
		 */
		UINT32 quadOffset;

		/**
		 * Address for pixel stepping values
		 */
		UINT32 gradientOffset;

		/**
		 * For pixel shader input register optimization.
		 */
		UINT32 options;

		CR_QuadVariable()
		{
			semantic = SHADER_SEMANTIC::FORMAT_END;
			format = SHADER_DATATYPE::UNKNOWN;

			fragmentOffset = 0;
			quadOffset = 0;
			gradientOffset = 0;
			options = 0;
		}
	};
}

#endif