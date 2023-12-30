#ifndef CENG_GLSL_KEYWORD_DB_H
#define CENG_GLSL_KEYWORD_DB_H

#include <unordered_map>

#include <ceng/token-type.h>

namespace Ceng
{
	std::unordered_map<const char*, Ceng::TokenType::value> keywords;
}

#endif