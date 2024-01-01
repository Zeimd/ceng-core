#ifndef CENG_GLSL_PARSER_RETURN_VALUE_H
#define CENG_GLSL_PARSER_RETURN_VALUE_H

#include <ceng/datatypes/basic-types.h>

#include "INonTerminal.h"

namespace Ceng
{
	struct ParserReturnValue
	{
		INonTerminal* nonTerminal;

		Ceng::UINT32 backtrackCounter;
	};
}

#endif