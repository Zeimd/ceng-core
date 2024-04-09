#include "Statement.h"
#include "SimpleStatement.h"
#include "CompoundStatement.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

Statement::~Statement()
{

}

void Statement::Release()
{
	delete this;
}

Statement::Statement(std::shared_ptr<SimpleStatement>& simpleStatement)
	: INonTerminal(NonTerminalType::statement), category(StatementCategory::simple),
	simpleStatement(simpleStatement), compoundStatement(nullptr)
{

}

Statement::Statement(std::shared_ptr<CompoundStatement>& compoundStatement)
	: INonTerminal(NonTerminalType::statement), category(StatementCategory::compound), 
	simpleStatement(nullptr), compoundStatement(compoundStatement)
{

}

Ceng::StringUtf8 Statement::ToString(unsigned int indentLevel) const
{
	switch (category)
	{
	case StatementCategory::simple:
		return simpleStatement->ToString(indentLevel);
	case StatementCategory::compound:
		return compoundStatement->ToString(indentLevel);
	default:
		return "<UNHANDLED STATEMENT CATEGORY>";
	}
}

void Statement::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_Statement(*this);
}