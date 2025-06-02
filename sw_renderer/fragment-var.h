/*****************************************************************************
*
* cr-fragment-var.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CR_FRAGMENT_VAR_H
#define _CENG_CR_FRAGMENT_VAR_H

#include <ceng/enums/shader-datatype.h>
#include <ceng/enums/shader-semantic.h>

#include "crender-base.h"

#include <ceng/math/ce-vector.h>

namespace Ceng
{
	//*********************************************************************************
	// Vertex shader output (fragment) format

	struct CR_FragmentVariable
	{
		/**
		 * Semantic value.
		 */
		Ceng::SHADER_SEMANTIC::value semantic;

		/**
		 * A CR_SHADER_DATA_TYPE value.
		 */
		Ceng::SHADER_DATATYPE::value format;

		/**
		 * Byte offset in the fragment format.
		 */
		UINT32 offset;

		/**
		 * Combination of CR_FRAGMENT_VARIABLE_OPTIONS values.
		 */
		UINT32 options;
	};

};

#endif