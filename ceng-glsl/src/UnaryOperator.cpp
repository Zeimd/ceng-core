#include "UnaryOperator.h"

using namespace Ceng;

void UnaryOperator::Release()
{
	delete this;
}

UnaryOperator::UnaryOperator(UnaryOperatorType::value type)
	: INonTerminal(NonTerminalType::unary_operator), type(type)
{

}

UnaryOperator::UnaryOperator(const Token& token)
	: INonTerminal(NonTerminalType::unary_operator)
{
	switch (token.type)
	{
	case TokenType::plus:
		type = UnaryOperatorType::plus;
		break;
	case TokenType::dash:
		type = UnaryOperatorType::negation;
		break;
	case TokenType::tilde:
		type = UnaryOperatorType::two_complement;
		break;
	case TokenType::bang:
		type = UnaryOperatorType::logical_not;
		break;
	}
}

Ceng::StringUtf8 UnaryOperator::ToString(unsigned int indentLevel) const
{
	switch (type)
	{
	case UnaryOperatorType::plus:
		return "+";
	case  UnaryOperatorType::logical_not:
		return "!";
	case UnaryOperatorType::negation:
		return "-";
	case UnaryOperatorType::two_complement:
		return "~";
	default:
		return "UnaryOperator: unhandled case";
	}
}