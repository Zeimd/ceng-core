#include "LogicalXorExpression.h"

#include "AST_Visitor.h"

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

Ceng::StringUtf8 LogicalXorExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString(indentLevel);
		out += " ^^ ";
		out += rhs->ToString(indentLevel);
	}
	else
	{
		out = rhs->ToString(indentLevel);
	}


	return out;
}

void LogicalXorExpression::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_LogicalXorExpression(*this);
}