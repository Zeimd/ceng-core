#include "AdditiveExpression.h"

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
	}
}

AdditiveExpression::AdditiveExpression(std::shared_ptr<AdditiveExpression>& lhs, AdditiveOp::value operation, std::shared_ptr<MultiplicativeExpression>& rhs)
	: INonTerminal(NonTerminalType::additive_expression), lhs(lhs), operation(operation),rhs(rhs)
{

}

Ceng::StringUtf8 AdditiveExpression::ToString() const
{
	return "";
}