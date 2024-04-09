#include "ExpressionStatement.h"
#include "Expression.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

ExpressionStatement::~ExpressionStatement()
{

}

void ExpressionStatement::Release()
{
	delete this;
}

ExpressionStatement::ExpressionStatement()
	: INonTerminal(NonTerminalType::expression_statement), ex(nullptr)
{

}

ExpressionStatement::ExpressionStatement(std::shared_ptr<Expression>& ex)
	: INonTerminal(NonTerminalType::expression_statement),ex(ex)
{

}

Ceng::StringUtf8 ExpressionStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += GetIndent(indentLevel);

	if (ex == nullptr)
	{
		out += ';';
		return out;
	}

	out += ex->ToString(indentLevel);
	out += ';';

	return out;
}

void ExpressionStatement::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_ExpressionStatement(*this);
}