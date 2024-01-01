#ifndef CENG_GLSL_TOKEN_INFO_H
#define CENG_GLSL_TOKEN_INFO_H

#include <ceng/token-type.h>
#include <ceng/token-category.h>

namespace Ceng
{
	struct TokenInfo
	{
		TokenType::value type;
		TokenCategory::value category;

	};
}

#endif