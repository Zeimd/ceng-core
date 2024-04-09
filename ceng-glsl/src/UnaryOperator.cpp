#include "UnaryOperator.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void UnaryOperator::Release()
{
	delete this;
}

UnaryOperator::UnaryOperator(UnaryOperatorType::value type)
	: INonTerminal(NonTerminalType::unary_operator), operatorType(type)
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
		operatorType = UnaryOperatorType::two_complement;
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

void UnaryOperator::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_UnaryOperator(*this);
}