#include "Expression.h"
#include "AssignmentExpression.h"

using namespace Ceng;

Expression::~Expression()
{

}

void Expression::Release()
{
	delete this;
}

Expression::Expression(std::shared_ptr<AssignmentExpression>& ex)
	: INonTerminal(NonTerminalType::expression)
{
	Append(ex);
}

void Expression::Append(std::shared_ptr<AssignmentExpression>& ex)
{
	assignEx.push_back(ex);
}

Ceng::StringUtf8 Expression::ToString() const
{
	Ceng::StringUtf8 out;

	for (auto& x : assignEx)
	{
		out += x->ToString();
	}

	return out;
}