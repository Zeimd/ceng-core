#ifndef CENG_GLSL_PARSER_RETURN_VALUE_H
#define CENG_GLSL_PARSER_RETURN_VALUE_H

#include <memory>

#include <ceng/datatypes/basic-types.h>

#include "INonTerminal.h"

namespace Ceng
{
	class ParserReturnValue
	{
	public:
		std::shared_ptr<INonTerminal> nonTerminal;

		Ceng::UINT32 backtrackCounter;

	public:
		ParserReturnValue();

		/*
		ParserReturnValue(ParserReturnValue&& value);

		ParserReturnValue& operator = (ParserReturnValue&& value);
		*/

		ParserReturnValue(std::shared_ptr<INonTerminal>& nonTerminal, Ceng::UINT32 backtrackCounter);

		ParserReturnValue(std::shared_ptr<INonTerminal> nonTerminal, Ceng::UINT32 backtrackCounter);
	};
}

#endif