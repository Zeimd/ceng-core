#include "ShiftExpression.h"

using namespace Ceng;

void ShiftExpression::Release()
{
	delete this;
}

ShiftExpression::ShiftExpression(std::shared_ptr<AdditiveExpression>& mulEx)
	: INonTerminal(NonTerminalType::shift_expression), rhs(mulEx), operation(ShiftOp::unassigned)
{

}

ShiftExpression::ShiftExpression(std::shared_ptr<ShiftExpression>& lhs, const Token& token, std::shared_ptr<AdditiveExpression>& rhs)
	: INonTerminal(NonTerminalType::shift_expression), lhs(lhs), rhs(rhs)
{
	switch (token.type)
	{
	case TokenType::left_op:
		operation = ShiftOp::left;
		break;
	case TokenType::right_op:
		operation = ShiftOp::right;
		break;
	default:
		operation = ShiftOp::invalid_value;
		break;
	}
}

ShiftExpression::ShiftExpression(std::shared_ptr<ShiftExpression>& lhs, ShiftOp::value operation, std::shared_ptr<AdditiveExpression>& rhs)
	: INonTerminal(NonTerminalType::shift_expression), lhs(lhs), operation(operation), rhs(rhs)
{

}

Ceng::StringUtf8 ShiftExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (operation == ShiftOp::unassigned)
	{
		return rhs->ToString(indentLevel);
	}

	out = lhs->ToString(indentLevel);
	out += ' ';

	switch (operation)
	{
	case ShiftOp::left:
		out += "<<";
		break;
	case ShiftOp::right:
		out += ">>";
		break;
	default:
		out += "<UNHANDLED SHIFT OPERATOR>";
		break;
	}

	out += ' ';
	out += rhs->ToString(indentLevel);

	return out;
}