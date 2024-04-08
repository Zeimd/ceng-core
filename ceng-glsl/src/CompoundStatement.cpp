#include "CompoundStatement.h"
#include "StatementList.h"

#include "AST_Visitor.h"

using namespace Ceng;

CompoundStatement::~CompoundStatement()
{

}

void CompoundStatement::Release()
{
	delete this;
}

CompoundStatement::CompoundStatement()
	: INonTerminal(NonTerminalType::compound_statement), list(nullptr)
{

}

CompoundStatement::CompoundStatement(std::shared_ptr<StatementList>& list)
	: INonTerminal(NonTerminalType::compound_statement), list(list)
{

}

Ceng::StringUtf8 CompoundStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += "\n";
	out += GetIndent(indentLevel);
	out += "{\n";

	if (list != nullptr)
	{
		out += list->ToString(indentLevel+1);
	}
	else
	{
		out += '\n';
	}

	out += GetIndent(indentLevel);
	out += "}\n";

	return out;
}

void CompoundStatement::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_CompoundStatement(*this);
}