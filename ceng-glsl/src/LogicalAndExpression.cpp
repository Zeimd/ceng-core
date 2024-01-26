#include "LogicalAndExpression.h"

using namespace Ceng;

void LogicalAndExpression::Release()
{
	delete this;
}

LogicalAndExpression::LogicalAndExpression(std::shared_ptr<OrExpression>& mulEx)
	: INonTerminal(NonTerminalType::logical_and_expression), rhs(mulEx), full(false)
{

}

LogicalAndExpression::LogicalAndExpression(std::shared_ptr<LogicalAndExpression>& lhs, std::shared_ptr<OrExpression>& rhs)
	: INonTerminal(NonTerminalType::logical_and_expression), lhs(lhs), rhs(rhs), full(true)
{

}

Ceng::StringUtf8 LogicalAndExpression::ToString() const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString();
		out += " && ";
		out += rhs->ToString();
	}
	else
	{
		out = rhs->ToString();
	}


	return out;
}