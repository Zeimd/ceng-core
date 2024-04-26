#include <ceng/GLSL/Lvalue.h>

#include <ceng/GLSL/Rvalue.h>

using namespace Ceng::GLSL;

Lvalue::Lvalue()
	: valueType(LvalueType::invalid), value(false)
{

}

Lvalue::Lvalue(const Ceng::StringUtf8& variable)
	: valueType(LvalueType::expression), value(FieldExpression(variable))
{

}

Lvalue::Lvalue(const Ceng::StringUtf8& variable, ArrayIndex& index)
	: valueType(LvalueType::expression), value(FieldExpression(variable, index))
{

}

Lvalue::Lvalue(const SimpleDeclaration& declaration)
	: valueType(LvalueType::declaration), value(declaration)
{

}

Lvalue::Lvalue(const VariableExpression& expression)
	: valueType(LvalueType::expression), value(expression)
{

}

Lvalue::Lvalue(VariableExpression&& expression)
	: valueType(LvalueType::expression), value(std::move(expression))
{

}

Ceng::StringUtf8 Lvalue::ToString(Ceng::UINT32 indentLevel) const
{
	switch (valueType)
	{
	case LvalueType::expression:
		return std::get<VariableExpression>(value).ToString();
	case LvalueType::declaration:
		return std::get<SimpleDeclaration>(value).ToString();
	default:
		return "<UNHANDLED LVALUE TYPE>";
	}
}

bool Lvalue::operator == (const Rvalue& other) const
{
	if (other.valueType != RvalueType::variable)
	{
		return false;
	}

	switch (valueType)
	{
	case LvalueType::expression:
		return std::get<VariableExpression>(value) == std::get<VariableExpression>(other.value);
	case LvalueType::declaration:
		return ToExpression() == std::get<VariableExpression>(other.value);
	}

	return false;
}

bool Lvalue::operator != (const Rvalue& other) const
{
	return !(*this == other);
}

VariableExpression Lvalue::ToExpression() const
{
	switch (valueType)
	{
	case LvalueType::expression:
		return std::get<VariableExpression>(value);
	case LvalueType::declaration:

		const SimpleDeclaration& decl = std::get<SimpleDeclaration>(value);

		return VariableExpression(FieldExpression(decl.name));

	}

	return VariableExpression();
}

bool Lvalue::IsValid() const
{
	return valueType != LvalueType::invalid;
}