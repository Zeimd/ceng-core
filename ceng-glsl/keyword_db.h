#ifndef CENG_GLSL_KEYWORD_DB_H
#define CENG_GLSL_KEYWORD_DB_H

#include <unordered_map>

#include <ceng/token-type.h>
#include <ceng/token-category.h>

namespace Ceng
{
	struct TokenInfo
	{
		TokenType::value type;
		TokenCategory::value category;

	};

	std::unordered_map<const char*, TokenInfo> keywords;
}

#endif