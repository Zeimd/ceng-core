#include "SwitchStatement.h"
#include "Expression.h"
#include "SwitchStatementList.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

SwitchStatement::~SwitchStatement()
{

}

void SwitchStatement::Release()
{
	delete this;
}

SwitchStatement::SwitchStatement(std::shared_ptr<Expression>& expression)
	: INonTerminal(NonTerminalType::switch_statement), expression(expression), list(nullptr)
{

}

SwitchStatement::SwitchStatement(std::shared_ptr<Expression>& expression, std::shared_ptr<SwitchStatementList>& list)
	: INonTerminal(NonTerminalType::switch_statement), expression(expression), list(list)
{

}

Ceng::StringUtf8 SwitchStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += GetIndent(indentLevel);
	out += "switch (";
	out += expression->ToString(indentLevel);
	out += ")\n";

	out += GetIndent(indentLevel);
	out += "{\n";

	if (list != nullptr)
	{
		out += list->ToString(indentLevel+1);
	}

	out += GetIndent(indentLevel);
	out += "}\n";

	return out;
}

void SwitchStatement::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_SwitchStatement(*this);
}