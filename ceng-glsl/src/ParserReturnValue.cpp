#include "ParserReturnValue.h"

using namespace Ceng;

ParserReturnValue::ParserReturnValue()
	: nonTerminal(nullptr), backtrackCounter(0)
{

}

ParserReturnValue::ParserReturnValue(INonTerminal* nonTerminal, Ceng::UINT32 backtrackCounter)
	: nonTerminal(nonTerminal), backtrackCounter(backtrackCounter)
{

}