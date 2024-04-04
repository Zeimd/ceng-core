#include "SwitchStatementList.h"
#include "StatementList.h"

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