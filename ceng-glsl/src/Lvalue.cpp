#include <ceng/GLSL/Lvalue.h>

using namespace Ceng::GLSL;

Lvalue::Lvalue()
	: valid(false)
{

}

Lvalue::Lvalue(const Ceng::StringUtf8& variable)
	: valid(true), expression(FieldExpression(variable))
{

}

Lvalue::Lvalue(const Ceng::StringUtf8& variable, ArrayIndex& index)
	: valid(true), expression(FieldExpression(variable, index))
{

}

Lvalue::Lvalue(const VariableExpression& expression)
	: expression(expression)
{

}

Lvalue::Lvalue(VariableExpression&& expression)
	: expression(std::move(expression))
{

}

Ceng::StringUtf8 Lvalue::ToString(Ceng::UINT32 indentLevel) const
{
	return expression.ToString();

	/*
	Ceng::StringUtf8 out;

	out += variable;
	out += variableIndex.ToString(indentLevel);

	if (memberAccess)
	{
		out += memberName;
		out += memberIndex.ToString(indentLevel);
	}

	return out;	
	*/
}