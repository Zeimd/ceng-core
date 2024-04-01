#include "CompoundStatementNoNewScope.h"
#include "StatementList.h"

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

Ceng::StringUtf8 CompoundStatementNoNewScope::ToString() const
{
	if (list == nullptr)
	{
		return "";
	}

	Ceng::StringUtf8 out;

	out += '{\n';

	list->ToString();

	out += '}\n';
}