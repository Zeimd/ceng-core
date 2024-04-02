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

Ceng::StringUtf8 Expression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	for (size_t k = 0; k < assignEx.size(); k++)
	{
		out += assignEx[k]->ToString(indentLevel);

		if (k < assignEx.size() - 1)
		{
			out += ", ";
		}
	}

	return out;
}