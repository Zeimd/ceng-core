#include "UnaryOperator.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void UnaryOperator::Release()
{
	delete this;
}

UnaryOperator::UnaryOperator(UnaryOperatorType::value operatorType)
	: INonTerminal(NonTerminalType::unary_operator), operatorType(operatorType)
{

}

UnaryOperator::UnaryOperator(const Token& token)
	: INonTerminal(NonTerminalType::unary_operator)
{
	switch (token.type)
	{
	case TokenType::plus:
		operatorType = UnaryOperatorType::plus;
		break;
	case TokenType::dash:
		operatorType = UnaryOperatorType::negation;
		break;
	case TokenType::tilde:
		operatorType = UnaryOperatorType::bit_flip;
		break;
	case TokenType::bang:
		operatorType = UnaryOperatorType::logical_not;
		break;
	default:
		operatorType = UnaryOperatorType::invalid_value;
		break;
	}

	
}

Ceng::StringUtf8 UnaryOperator::ToString(unsigned int indentLevel) const
{
	switch (operatorType)
	{
	case UnaryOperatorType::plus:
		return "+";
	case  UnaryOperatorType::logical_not:
		return "!";
	case UnaryOperatorType::negation:
		return "-";
	case UnaryOperatorType::bit_flip:
		return "~";
	default:
		return "UnaryOperator: unhandled case";
	}
}

void UnaryOperator::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_UnaryOperator(*this);
}