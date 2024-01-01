#ifndef CENG_GLSL_PARSER_RETURN_VALUE_H
#define CENG_GLSL_PARSER_RETURN_VALUE_H

#include <ceng/datatypes/basic-types.h>

#include "INonTerminal.h"

namespace Ceng
{
	class ParserReturnValue
	{
	public:
		INonTerminal* nonTerminal;

		//Ceng::UINT32 backtrackCounter;

	public:
		ParserReturnValue();

		ParserReturnValue(INonTerminal* nonTerminal);
	};
}

#endif