#include "ExpressionStatement.h"
#include "Expression.h"

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

Ceng::StringUtf8 ExpressionStatement::ToString() const
{
	if (ex == nullptr)
	{
		return ";";
	}

	Ceng::StringUtf8 out;

	out = ex->ToString();
	out += ';';

	return out;
}