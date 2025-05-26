#pragma once

#ifndef CENG_PSHADER_OUTPUT_DESC_H
#define CENG_PSHADER_OUTPUT_DESC_H

#include "../enums/pshader-output-semantic.h"

namespace Ceng
{
	struct PixelShaderOutputDesc
	{
		PSHADER_OUTPUT_SEMANTIC::value target;
	};
}

#endif