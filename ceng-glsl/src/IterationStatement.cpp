#include "IterationStatement.h"

#include "Condition.h"

#include "Expression.h"
#include "Statement.h"
#include "StatementNoNewScope.h"

#include "ForInitStatement.h"
#include "ForRestStatement.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

IterationStatement::~IterationStatement()
{

}

void IterationStatement::Release()
{
	delete this;
}

IterationStatement::IterationStatement(std::shared_ptr<Condition>& whileCondition, std::shared_ptr<StatementNoNewScope>& forWhileBody)
	: INonTerminal(NonTerminalType::iteration_statement), iterationType(IterationType::whileLoop), whileCondition(whileCondition),
	forWhileBody(forWhileBody)
{

}

IterationStatement::IterationStatement(std::shared_ptr<Statement>& doBody, std::shared_ptr<Expression>& doWhileCondition)
	: INonTerminal(NonTerminalType::iteration_statement), iterationType(IterationType::doLoop), doBody(doBody), doWhileCondition(doWhileCondition)
{

}

IterationStatement::IterationStatement(std::shared_ptr<ForInitStatement>& forInit, std::shared_ptr<ForRestStatement>& forRest,
	std::shared_ptr<StatementNoNewScope>& forWhileBody)
	: INonTerminal(NonTerminalType::iteration_statement), iterationType(IterationType::forLoop),
	forInit(forInit), forRest(forRest), forWhileBody(forWhileBody)
{

}

Ceng::StringUtf8 IterationStatement::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (iterationType)
	{
	case IterationType::whileLoop:
		out += GetIndent(indentLevel);
		out += "while (";
		out += whileCondition->ToString(indentLevel);
		out += ")";
		out += forWhileBody->ToString(indentLevel);
		break;
	case IterationType::doLoop:
		out += GetIndent(indentLevel);
		out += "do";
		out += doBody->ToString(indentLevel);
		out += GetIndent(indentLevel);
		out += "while (";
		out += doWhileCondition->ToString(indentLevel);
		out += ");";
		break;
	case IterationType::forLoop:
		out += GetIndent(indentLevel);
		out += "for (";
		out += forInit->ToString(indentLevel);
		out += ' ';
		out += forRest->ToString(indentLevel);
		out += ")";
		out += forWhileBody->ToString(indentLevel);
		break;
	default:
		out += "<UNHANDLED ITERATION TYPE>";
		break;
	}

	return out;
}

void IterationStatement::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_IterationStatement(*this);
}