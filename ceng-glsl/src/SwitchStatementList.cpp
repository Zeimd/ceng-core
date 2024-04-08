#include "SwitchStatementList.h"
#include "StatementList.h"

#include "AST_Visitor.h"

using namespace Ceng;

SwitchStatementList::~SwitchStatementList()
{

}

void SwitchStatementList::Release()
{
	delete this;
}

SwitchStatementList::SwitchStatementList(std::shared_ptr<StatementList>& list)
	: INonTerminal(NonTerminalType::switch_statement_list), list(list)
{

}

Ceng::StringUtf8 SwitchStatementList::ToString(unsigned int indentLevel) const
{
	return list->ToString(indentLevel);
}

void SwitchStatementList::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_SwitchStatementList(*this);
}