#include "StatementNoNewScope.h"
#include "SimpleStatement.h"
#include "CompoundStatementNoNewScope.h"

using namespace Ceng;

StatementNoNewScope::~StatementNoNewScope()
{

}

void StatementNoNewScope::Release()
{
	delete this;
}

StatementNoNewScope::StatementNoNewScope(std::shared_ptr<SimpleStatement>& simpleStatement)
	: INonTerminal(NonTerminalType::statement_no_new_scope), category(StatementCategory::simple),
	simpleStatement(simpleStatement), compoundStatement(nullptr)
{

}

StatementNoNewScope::StatementNoNewScope(std::shared_ptr<CompoundStatementNoNewScope>& compoundStatement)
	: INonTerminal(NonTerminalType::statement_no_new_scope), category(StatementCategory::compound),
	simpleStatement(nullptr), compoundStatement(compoundStatement)
{

}

Ceng::StringUtf8 StatementNoNewScope::ToString() const
{
	switch (category)
	{
	case StatementCategory::simple:
		return simpleStatement->ToString();
	case StatementCategory::compound:
		return compoundStatement->ToString();
	default:
		return "<UNHANDLED STATEMENT CATEGORY>";
	}
}