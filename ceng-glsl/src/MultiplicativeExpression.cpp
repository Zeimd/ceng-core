#include "MultiplicativeExpression.h"

using namespace Ceng;

void MultiplicativeExpression::Release()
{

}

MultiplicativeExpression::MultiplicativeExpression(std::shared_ptr<UnaryExpression>& unaryEx)
	: INonTerminal(NonTerminalType::multiplicative_expression), rhs(unaryEx), operation(MultiplicativeOp::unassigned)
{

}

MultiplicativeExpression::MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& lhs, const Token& token, std::shared_ptr<UnaryExpression>& rhs)
	: INonTerminal(NonTerminalType::multiplicative_expression), lhs(lhs), rhs(rhs)
{
	switch (token.type)
	{
	case TokenType::star:
		operation = MultiplicativeOp::mul;
		break;
	case TokenType::slash:
		operation = MultiplicativeOp::div;
		break;
	case TokenType::percent:
		operation = MultiplicativeOp::mod;
		break;
	}
}

MultiplicativeExpression::MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& lhs, 
	MultiplicativeOp::value operation, std::shared_ptr<UnaryExpression>& rhs)
	: INonTerminal(NonTerminalType::multiplicative_expression), lhs(lhs), rhs(rhs), operation(operation)
{

}

Ceng::StringUtf8 MultiplicativeExpression::ToString() const
{
	return "";
}