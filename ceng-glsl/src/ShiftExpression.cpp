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
	}
}

ShiftExpression::ShiftExpression(std::shared_ptr<ShiftExpression>& lhs, ShiftOp::value operation, std::shared_ptr<AdditiveExpression>& rhs)
	: INonTerminal(NonTerminalType::shift_expression), lhs(lhs), operation(operation), rhs(rhs)
{

}