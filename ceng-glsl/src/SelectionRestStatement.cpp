#include "SelectionRestStatement.h"
#include "Statement.h"

using namespace Ceng;

SelectionRestStatement::~SelectionRestStatement()
{

}

void SelectionRestStatement::Release()
{
	delete this;
}


SelectionRestStatement::SelectionRestStatement(std::shared_ptr<Statement>& main)
	: INonTerminal(NonTerminalType::selection_rest_statement), main(main), elseBlock(nullptr)
{

}

SelectionRestStatement::SelectionRestStatement(std::shared_ptr<Statement>& main, std::shared_ptr<Statement>& elseBlock)
	: INonTerminal(NonTerminalType::selection_rest_statement), main(main), elseBlock(elseBlock)
{

}

Ceng::StringUtf8 SelectionRestStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += main->ToString(indentLevel);

	if (elseBlock != nullptr)
	{
		if (main->category == StatementCategory::compound)
		{
			out += GetIndent(indentLevel);
			out += "else";
		}
		else
		{
			out += " else ";
		}
		
		out += elseBlock->ToString(indentLevel);
	}

	return out;
}