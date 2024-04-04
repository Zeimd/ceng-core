#include "SelectionStatement.h"

#include "Expression.h"
#include "SelectionRestStatement.h"

using namespace Ceng;

SelectionStatement::~SelectionStatement()
{

}

void SelectionStatement::Release()
{
	delete this;
}

SelectionStatement::SelectionStatement(std::shared_ptr<Expression>& condition, std::shared_ptr<SelectionRestStatement>& rest)
	: INonTerminal(NonTerminalType::selection_statement), condition(condition), rest(rest)
{

}

Ceng::StringUtf8 SelectionStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out = GetIndent(indentLevel);

	out += "if (";
	out += condition->ToString(indentLevel);
	out += ") ";

	out += rest->ToString(indentLevel);

	return out;
}