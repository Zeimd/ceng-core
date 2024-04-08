#include "ConditionalExpression.h"
#include "AssignmentExpression.h"

#include "AST_Visitor.h"

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

Ceng::StringUtf8 ConditionalExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = a->ToString(indentLevel);
		out += " ? ";
		out += b->ToString(indentLevel);
		out += " : ";
		out += c->ToString(indentLevel);
	}
	else
	{
		out = a->ToString(indentLevel);
	}


	return out;
}

void ConditionalExpression::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_ConditionalExpression(*this);
}