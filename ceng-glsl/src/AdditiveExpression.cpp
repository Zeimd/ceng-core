#include "AdditiveExpression.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void AdditiveExpression::Release()
{
	delete this;
}

AdditiveExpression::AdditiveExpression(std::shared_ptr<MultiplicativeExpression>& mulEx)
	: INonTerminal(NonTerminalType::additive_expression), rhs(mulEx), operation(AdditiveOp::unassigned)
{

}

AdditiveExpression::AdditiveExpression(std::shared_ptr<AdditiveExpression>& lhs, const Token& token, std::shared_ptr<MultiplicativeExpression>& rhs)
	: INonTerminal(NonTerminalType::additive_expression), lhs(lhs), rhs(rhs)
{
	switch (token.type)
	{
	case TokenType::plus:
		operation = AdditiveOp::add;
		break;
	case TokenType::dash:
		operation = AdditiveOp::sub;
		break;
	default:
		operation = AdditiveOp::invalid_value;
		break;
	}
}

AdditiveExpression::AdditiveExpression(std::shared_ptr<AdditiveExpression>& lhs, AdditiveOp::value operation, std::shared_ptr<MultiplicativeExpression>& rhs)
	: INonTerminal(NonTerminalType::additive_expression), lhs(lhs), operation(operation),rhs(rhs)
{

}

Ceng::StringUtf8 AdditiveExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (operation == AdditiveOp::unassigned)
	{
		out = rhs->ToString(indentLevel);
	}
	else
	{
		out = lhs->ToString(indentLevel);
		
		switch (operation)
		{
		case AdditiveOp::add:
			out += " + ";
			break;
		case AdditiveOp::sub:
			out += " - ";
			break;
		default:
			out += " <UNHANDLED ADDITIVE OP> ";
			break;
		}

		out += rhs->ToString(indentLevel);
	}


	return out;
}

void AdditiveExpression::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_AdditiveExpression(*this);
}
