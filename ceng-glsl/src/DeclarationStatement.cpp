#include "DeclarationStatement.h"
#include "Declaration.h"

using namespace Ceng;

DeclarationStatement::~DeclarationStatement()
{

}

void DeclarationStatement::Release()
{
	delete this;
}

DeclarationStatement::DeclarationStatement(std::shared_ptr<Declaration>& declaration)
	: INonTerminal(NonTerminalType::declaration_statement), declaration(declaration)
{

}

Ceng::StringUtf8 DeclarationStatement::ToString(unsigned int indentLevel) const
{
	return declaration->ToString(indentLevel);
}