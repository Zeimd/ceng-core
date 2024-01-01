#include "ParserReturnValue.h"

using namespace Ceng;

ParserReturnValue::ParserReturnValue()
	: nonTerminal(nullptr)
{

}

ParserReturnValue::ParserReturnValue(INonTerminal* nonTerminal)
	: nonTerminal(nonTerminal)
{

}