#include "OrExpression.h"

#include "NonTerminalVisitor.h"

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

Ceng::StringUtf8 OrExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (full)
	{
		out = lhs->ToString(indentLevel);
		out += " | ";
		out += rhs->ToString(indentLevel);
	}
	else
	{
		out = rhs->ToString(indentLevel);
	}


	return out;
}

void OrExpression::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_OrExpression(*this);
}