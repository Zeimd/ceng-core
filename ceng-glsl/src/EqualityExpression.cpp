#include "EqualityExpression.h"

using namespace Ceng;

void EqualityExpression::Release()
{
	delete this;
}

EqualityExpression::EqualityExpression(std::shared_ptr<RelationalExpression>& mulEx)
	: INonTerminal(NonTerminalType::equality_expression), rhs(mulEx), operation(EqualityOp::unassigned)
{

}

EqualityExpression::EqualityExpression(std::shared_ptr<EqualityExpression>& lhs, const Token& token, std::shared_ptr<RelationalExpression>& rhs)
	: INonTerminal(NonTerminalType::equality_expression), lhs(lhs), rhs(rhs)
{
	switch (token.type)
	{
	case TokenType::eq_op:
		operation = EqualityOp::equal;
		break;
	case TokenType::ne_op:
		operation = EqualityOp::not_equal;
		break;
	}
}

EqualityExpression::EqualityExpression(std::shared_ptr<EqualityExpression>& lhs, EqualityOp::value operation, std::shared_ptr<RelationalExpression>& rhs)
	: INonTerminal(NonTerminalType::equality_expression), lhs(lhs), operation(operation), rhs(rhs)
{

}

Ceng::StringUtf8 EqualityExpression::ToString() const
{
	return "";
}