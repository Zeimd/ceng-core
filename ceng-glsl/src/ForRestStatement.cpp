#include "ForRestStatement.h"

#include "Expression.h"
#include "Condition.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

ForRestStatement::~ForRestStatement()
{

}

void ForRestStatement::Release()
{
	delete this;
}

ForRestStatement::ForRestStatement()
	: INonTerminal(NonTerminalType::for_rest_statement), condition(nullptr), expression(nullptr)
{

}

ForRestStatement::ForRestStatement(std::shared_ptr<Condition>& condition)
	: INonTerminal(NonTerminalType::for_rest_statement), condition(condition), expression(nullptr)
{

}

ForRestStatement::ForRestStatement(std::shared_ptr<Condition>& condition, std::shared_ptr<Expression>& expression)
	: INonTerminal(NonTerminalType::for_rest_statement), condition(condition), expression(expression)
{

}

ForRestStatement::ForRestStatement(std::shared_ptr<Expression>& expression)
	: INonTerminal(NonTerminalType::for_rest_statement), condition(nullptr), expression(expression)
{

}

Ceng::StringUtf8 ForRestStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (condition != nullptr)
	{
		out += condition->ToString(indentLevel);
	}

	out += ';';

	if (expression != nullptr)
	{
		out += ' ';
		out += expression->ToString(indentLevel);
	}

	return out;
}

void ForRestStatement::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_ForRestStatement(*this);
}