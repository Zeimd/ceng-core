#include "LogicalAndExpression.h"

#include "AST_Visitor.h"

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

Ceng::StringUtf8 LogicalAndExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString(indentLevel);
		out += " && ";
		out += rhs->ToString(indentLevel);
	}
	else
	{
		out = rhs->ToString(indentLevel);
	}


	return out;
}

void LogicalAndExpression::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_LogicalAndExpression(*this);
}