#include "StatementList.h"
#include "Statement.h"

using namespace Ceng;

StatementList::~StatementList()
{

}

void StatementList::Release()
{
	delete this;
}

StatementList::StatementList(std::shared_ptr<Statement>& statement)
	: INonTerminal(NonTerminalType::statement_list), list{statement}
{

}

void StatementList::Append(std::shared_ptr<Statement>& statement)
{
	list.push_back(statement);
}

Ceng::StringUtf8 StatementList::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	for (auto& x : list)
	{
		//out += GetIndent(indentLevel);
		out += x->ToString(indentLevel);
		out += '\n';
	}

	return out;
}
