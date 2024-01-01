#ifndef CENG_GLSL_KEYWORD_DB_H
#define CENG_GLSL_KEYWORD_DB_H

#include <unordered_map>
#include <ceng/datatypes/ce-string.h>

#include "token-info.h"

namespace Ceng
{
	extern std::unordered_map<Ceng::StringUtf8, TokenInfo> keywords;
}

#endif