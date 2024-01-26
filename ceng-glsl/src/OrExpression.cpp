#include "OrExpression.h"

using namespace Ceng;

void OrExpression::Release()
{
	delete this;
}

OrExpression::OrExpression(std::shared_ptr<XorExpression>& mulEx)
	: INonTerminal(NonTerminalType::or_expression), rhs(mulEx), full(false)
{

}

OrExpression::OrExpression(std::shared_ptr<OrExpression>& lhs, std::shared_ptr<XorExpression>& rhs)
	: INonTerminal(NonTerminalType::or_expression), lhs(lhs), rhs(rhs), full(true)
{

}

Ceng::StringUtf8 OrExpression::ToString() const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString();
		out += " | ";
		out += rhs->ToString();
	}
	else
	{
		out = rhs->ToString();
	}


	return out;
}