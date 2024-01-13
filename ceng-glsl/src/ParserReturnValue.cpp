#include "ParserReturnValue.h"

using namespace Ceng;

ParserReturnValue::ParserReturnValue()
	: nonTerminal(nullptr), backtrackCounter(0)
{

}

/*
ParserReturnValue::ParserReturnValue(ParserReturnValue&& value)
	: nonTerminal(std::move(value.nonTerminal)), backtrackCounter(value.backtrackCounter)
{

}

ParserReturnValue& ParserReturnValue::operator = (ParserReturnValue&& value)
{
	this->nonTerminal = std::move(value.nonTerminal);
	this->backtrackCounter = value.backtrackCounter;
}
*/

ParserReturnValue::ParserReturnValue(std::shared_ptr<INonTerminal>& nonTerminal, Ceng::UINT32 backtrackCounter)
	: nonTerminal(nonTerminal), backtrackCounter(backtrackCounter)
{

}

ParserReturnValue::ParserReturnValue(std::shared_ptr<INonTerminal> nonTerminal, Ceng::UINT32 backtrackCounter)
	: nonTerminal(nonTerminal), backtrackCounter(backtrackCounter)
{

}