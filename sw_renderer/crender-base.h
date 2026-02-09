/*****************************************************************************
*
* crender-base.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#pragma once

#ifndef CENG_CRENDER_BASE_H
#define CENG_CRENDER_BASE_H

#include <ceng/datatypes/basic-types.h>

namespace Ceng
{
	static const UINT32 CRENDER_MAX_COLOR_TARGETS = 8;
	static const UINT32 CRENDER_MAX_SHADER_TEXTURES = 8;

	static const UINT32 CRENDER_MAX_VTX_DECL_FLOATS = 64;

	static const UINT32 CRENDER_MAX_VERTEX_STREAMS = 8;
	static const UINT32 CRENDER_TEXCOORD_MAX_INDEX = 8;

	static const Ceng::FLOAT32 math_pi = 3.1415926535f;

	static const Ceng::FLOAT32 degrees_to_radians = math_pi / 180.0f;
}

#endif