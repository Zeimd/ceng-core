#include "ConditionalExpression.h"
#include "AssignmentExpression.h"

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
	Ceng::StringUtf8 out;

	if (full)
	{
		out = a->ToString();
		out += " ? ";
		out += b->ToString();
		out += " : ";
		out += c->ToString();
	}
	else
	{
		out = a->ToString();
	}


	return out;
}