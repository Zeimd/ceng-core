#include "RelationalExpression.h"

using namespace Ceng;

void RelationalExpression::Release()
{
	delete this;
}

RelationalExpression::RelationalExpression(std::shared_ptr<ShiftExpression>& mulEx)
	: INonTerminal(NonTerminalType::relational_expression), rhs(mulEx), operation(RelativeOp::unassigned)
{

}

RelationalExpression::RelationalExpression(std::shared_ptr<RelationalExpression>& lhs, const Token& token, std::shared_ptr<ShiftExpression>& rhs)
	: INonTerminal(NonTerminalType::relational_expression), lhs(lhs), rhs(rhs)
{
	switch (token.type)
	{
	case TokenType::left_angle:
		operation = RelativeOp::less;
		break;
	case TokenType::right_angle:
		operation = RelativeOp::greater;
		break;
	case TokenType::le_op:
		operation = RelativeOp::less_or_equal;
		break;
	case TokenType::ge_op:
		operation = RelativeOp::greater_or_equal;
		break;
	}
}

RelationalExpression::RelationalExpression(std::shared_ptr<RelationalExpression>& lhs, RelativeOp::value operation, std::shared_ptr<ShiftExpression>& rhs)
	: INonTerminal(NonTerminalType::relational_expression), lhs(lhs), operation(operation), rhs(rhs)
{

}