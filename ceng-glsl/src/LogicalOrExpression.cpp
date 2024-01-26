#include "LogicalOrExpression.h"

using namespace Ceng;

void LogicalOrExpression::Release()
{
	delete this;
}

LogicalOrExpression::LogicalOrExpression(std::shared_ptr<LogicalXorExpression>& mulEx)
	: INonTerminal(NonTerminalType::logical_or_expression), rhs(mulEx), full(false)
{

}

LogicalOrExpression::LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& lhs, std::shared_ptr<LogicalXorExpression>& rhs)
	: INonTerminal(NonTerminalType::logical_or_expression), lhs(lhs), rhs(rhs), full(true)
{

}

Ceng::StringUtf8 LogicalOrExpression::ToString() const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString();
		out += " || ";
		out += rhs->ToString();
	}
	else
	{
		out = rhs->ToString();
	}


	return out;
}