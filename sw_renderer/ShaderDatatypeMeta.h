#pragma once

#ifndef CENG_SHADER_DATA_TYPE_META_H
#define CENG_SHADER_DATA_TYPE_META_H

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>

#include <ceng/enums/shader-datatype.h>

namespace Ceng
{
	extern const UINT32 CR_SHADER_DATA_TYPE_SIZE[];
	extern const Ceng::BOOL CR_PSHADER_VALID_INPUT_TYPE[];
	extern const Ceng::BOOL CR_SHADER_VALID_UNIFORM_TYPE[];
	extern const SHADER_DATATYPE::value CR_SHADER_UNIFORM_EFFECTIVE_TYPE[];
	extern const char* CR_SHADER_DATA_TYPE_NAME[];
}

#endif