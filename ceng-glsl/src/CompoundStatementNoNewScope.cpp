#include "CompoundStatementNoNewScope.h"
#include "StatementList.h"
#include "CompoundStatement.h"

using namespace Ceng;

CompoundStatementNoNewScope::~CompoundStatementNoNewScope()
{

}

void CompoundStatementNoNewScope::Release()
{
	delete this;
}

CompoundStatementNoNewScope::CompoundStatementNoNewScope()
	: INonTerminal(NonTerminalType::compound_statement_no_new_scope), list(nullptr)
{

}

CompoundStatementNoNewScope::CompoundStatementNoNewScope(std::shared_ptr<StatementList>& list)
	: INonTerminal(NonTerminalType::compound_statement_no_new_scope), list(list)
{

}

CompoundStatementNoNewScope::CompoundStatementNoNewScope(std::shared_ptr<CompoundStatement>& compound)
	: INonTerminal(NonTerminalType::compound_statement_no_new_scope), list(compound->list)
{

}

Ceng::StringUtf8 CompoundStatementNoNewScope::ToString(unsigned int indentLevel) const
{
	printf(__FUNCTION__);

	Ceng::StringUtf8 out;

	out += '\n';
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