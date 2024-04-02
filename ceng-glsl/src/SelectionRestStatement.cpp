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

Ceng::StringUtf8 SelectionRestStatement::ToString() const
{
	Ceng::StringUtf8 out;

	out += main->ToString();

	if (elseBlock != nullptr)
	{
		out += " else ";
		out += elseBlock->ToString();
	}

	return out;
}