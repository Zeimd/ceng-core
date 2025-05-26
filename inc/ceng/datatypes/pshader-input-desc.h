#pragma once

#ifndef CENG_PSHADER_INPUT_DESC_H
#define CENG_PSHADER_INPUT_DESC_H

#include "../enums/shader-semantic.h"

namespace Ceng
{
	struct PixelShaderInputDesc
	{
		Ceng::SHADER_SEMANTIC::value semantic;
	};
}

#endif