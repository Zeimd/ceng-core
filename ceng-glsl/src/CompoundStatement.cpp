#include "CompoundStatement.h"
#include "StatementList.h"

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

Ceng::StringUtf8 CompoundStatement::ToString() const
{
	if (list == nullptr)
	{
		return "";
	}

	Ceng::StringUtf8 out;

	out += '{\n';
	
	list->ToString();

	out += '}\n';

	return out;
}