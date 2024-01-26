#include "ConditionalExpression.h"

using namespace Ceng;

void ConditionalExpression::Release()
{

}

ConditionalExpression::ConditionalExpression(std::shared_ptr<LogicalOrExpression>& a)
	: INonTerminal(NonTerminalType::conditional_expression), a(a), full(false)
{

}

ConditionalExpression::ConditionalExpression(std::shared_ptr<LogicalOrExpression>& a, std::shared_ptr<Expression>& b, std::shared_ptr<AssignmentExpression>& c)
	: INonTerminal(NonTerminalType::conditional_expression), a(a), b(b), c(c), full(true)
{

}

Ceng::StringUtf8 ConditionalExpression::ToString() const
{
	return "";
}