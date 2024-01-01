#ifndef CENG_GLSL_TOKEN_INFO_H
#define CENG_GLSL_TOKEN_INFO_H

#include <ceng/GLSL/TokenType.h>
#include <ceng/GLSL/TokenCategory.h>

namespace Ceng
{
	struct TokenInfo
	{
		TokenType::value type;
		TokenCategory::value category;

	};
}

#endif