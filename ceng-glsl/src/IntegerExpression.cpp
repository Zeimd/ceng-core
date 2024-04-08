#include "IntegerExpression.h"

#include "AST_Visitor.h"

using namespace Ceng;

IntegerExpression::IntegerExpression()
	: INonTerminal(NonTerminalType::integer_expression)
{

}

void IntegerExpression::Release()
{
	delete this;
}

Ceng::StringUtf8 IntegerExpression::ToString(unsigned int indentLevel) const
{
	return "";
}

void IntegerExpression::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_IntegerExpression(*this);
}