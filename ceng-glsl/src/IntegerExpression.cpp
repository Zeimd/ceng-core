#include "IntegerExpression.h"

using namespace Ceng;

IntegerExpression::IntegerExpression()
	: INonTerminal(NonTerminalType::integer_expression)
{

}

void IntegerExpression::Release()
{
	delete this;
}

Ceng::StringUtf8 IntegerExpression::ToString() const
{
	return "";
}