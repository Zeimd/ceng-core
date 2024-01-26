#include "LogicalXorExpression.h"

using namespace Ceng;

void LogicalXorExpression::Release()
{
	delete this;
}

LogicalXorExpression::LogicalXorExpression(std::shared_ptr<LogicalAndExpression>& mulEx)
	: INonTerminal(NonTerminalType::logical_xor_expression), rhs(mulEx), full(false)
{

}

LogicalXorExpression::LogicalXorExpression(std::shared_ptr<LogicalXorExpression>& lhs, std::shared_ptr<LogicalAndExpression>& rhs)
	: INonTerminal(NonTerminalType::logical_xor_expression), lhs(lhs), rhs(rhs), full(true)
{

}

Ceng::StringUtf8 LogicalXorExpression::ToString() const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString();
		out += " ^^ ";
		out += rhs->ToString();
	}
	else
	{
		out = rhs->ToString();
	}


	return out;
}