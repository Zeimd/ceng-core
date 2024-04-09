#include "DeclarationStatement.h"
#include "Declaration.h"

#include "NonTerminalVisitor.h"

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
	Ceng::StringUtf8 out;

	out = GetIndent(indentLevel);

	out += declaration->ToString(indentLevel);

	return out;
}

void DeclarationStatement::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_DeclarationStatement(*this);
}