#include "ForInitStatement.h"

#include "ExpressionStatement.h"
#include "DeclarationStatement.h"

#include "AST_Visitor.h"

using namespace Ceng;

ForInitStatement::~ForInitStatement()
{

}

void ForInitStatement::Release()
{
	delete this;
}

ForInitStatement::ForInitStatement(std::shared_ptr<ExpressionStatement>& expression)
	: INonTerminal(NonTerminalType::for_init_statement), initType(ForInitType::expression), expression(expression)
{

}

ForInitStatement::ForInitStatement(std::shared_ptr<DeclarationStatement>& declaration)
	: INonTerminal(NonTerminalType::for_init_statement), initType(ForInitType::declaration), declaration(declaration)
{

}

Ceng::StringUtf8 ForInitStatement::ToString(unsigned int indentLevel) const
{
	switch (initType)
	{
	case ForInitType::declaration:
		return declaration->ToString(indentLevel);
	case ForInitType::expression:
		return expression->ToString(indentLevel);
	}

	return "<UNHANDLED FOR INIT TYPE>";
}

void ForInitStatement::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_ForInitStatement(*this);
}