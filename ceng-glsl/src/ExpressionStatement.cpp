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

	return ex->ToString();
}