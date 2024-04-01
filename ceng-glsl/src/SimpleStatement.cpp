#include "SimpleStatement.h"

#include "DeclarationStatement.h"
#include "ExpressionStatement.h"
#include "SelectionStatement.h"
#include "SwitchStatement.h"
#include "CaseLabel.h"
#include "IterationStatement.h"
#include "JumpStatement.h"

using namespace Ceng;

SimpleStatement::~SimpleStatement()
{

}

void SimpleStatement::Release()
{
	delete this;
}

SimpleStatement::SimpleStatement(std::shared_ptr<DeclarationStatement>& declaration)
	: INonTerminal(NonTerminalType::simple_statement), type(StatementType::declaration), declaration(declaration)
{

}

SimpleStatement::SimpleStatement(std::shared_ptr<ExpressionStatement>& expression)
	: INonTerminal(NonTerminalType::simple_statement), type(StatementType::expression), expression(expression)
{

}

SimpleStatement::SimpleStatement(std::shared_ptr<SelectionStatement>& selection)
	: INonTerminal(NonTerminalType::simple_statement), type(StatementType::selection), selection(selection)
{

}

SimpleStatement::SimpleStatement(std::shared_ptr<SwitchStatement>& switchStatement)
	: INonTerminal(NonTerminalType::simple_statement), type(StatementType::switch_statement), switchStatement(switchStatement)
{

}

SimpleStatement::SimpleStatement(std::shared_ptr<CaseLabel>& caseLabel)
	: INonTerminal(NonTerminalType::simple_statement), type(StatementType::case_label), caseLabel(caseLabel)
{

}

SimpleStatement::SimpleStatement(std::shared_ptr<IterationStatement>& iteration)
	: INonTerminal(NonTerminalType::simple_statement), type(StatementType::iteration), iteration(iteration)
{

}

SimpleStatement::SimpleStatement(std::shared_ptr<JumpStatement>& jump)
	: INonTerminal(NonTerminalType::simple_statement), type(StatementType::jump), jump(jump)
{

}

Ceng::StringUtf8 SimpleStatement::ToString() const
{
	switch (type)
	{
	case StatementType::expression:
		return expression->ToString();
	case StatementType::declaration:
		return declaration->ToString();
	case StatementType::selection:
		return selection->ToString();
	case StatementType::switch_statement:
		return switchStatement->ToString();
	case StatementType::case_label:
		return caseLabel->ToString();
	case StatementType::iteration:
		return iteration->ToString();
	case StatementType::jump:
		return jump->ToString();
	default:
		return "<UNHANDLED STATEMENT TYPE>";
	}
}