#include "LogicalOrExpression.h"

#include "NonTerminalVisitor.h"

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

Ceng::StringUtf8 LogicalOrExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString(indentLevel);
		out += " || ";
		out += rhs->ToString(indentLevel);
	}
	else
	{
		out = rhs->ToString(indentLevel);
	}


	return out;
}

void LogicalOrExpression::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_LogicalOrExpression(*this);
}