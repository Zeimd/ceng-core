#include "AndExpression.h"

using namespace Ceng;

void AndExpression::Release()
{
	delete this;
}

AndExpression::AndExpression(std::shared_ptr<EqualityExpression>& mulEx)
	: INonTerminal(NonTerminalType::and_expression), rhs(mulEx), full(false)
{

}

AndExpression::AndExpression(std::shared_ptr<AndExpression>& lhs, std::shared_ptr<EqualityExpression>& rhs)
	: INonTerminal(NonTerminalType::and_expression), lhs(lhs), rhs(rhs), full(true)
{

}

Ceng::StringUtf8 AndExpression::ToString() const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString();
		out += " & ";
		out += rhs->ToString();
	}
	else
	{
		out = rhs->ToString();
	}


	return out;
}