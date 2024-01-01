#ifndef CENG_GLSL_KEYWORD_DB_H
#define CENG_GLSL_KEYWORD_DB_H

#include <unordered_map>

#include "token-info.h"

namespace Ceng
{
	extern std::unordered_map<const char*, TokenInfo> keywords;
}

#endif