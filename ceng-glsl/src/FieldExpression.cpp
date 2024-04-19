#include <ceng/GLSL/FieldExpression.h>

using namespace Ceng::GLSL;

FieldExpression::FieldExpression()
	: empty(true), index(false)
{
}

FieldExpression::FieldExpression(const Ceng::StringUtf8& name)
	: empty(false), name(name), index(false)
{

}

FieldExpression::FieldExpression(const Ceng::StringUtf8& name, ArrayIndex& index)
	: empty(false), name(name), index(index)
{

}

Ceng::StringUtf8 FieldExpression::ToString() const
{
	if (empty)
	{
		return "";
	}

	Ceng::StringUtf8 out;

	out += name;
	out += index.ToString(0);

	return out;
}

bool FieldExpression::operator == (const FieldExpression& other) const
{
	if (empty || other.empty)
	{
		return false;
	}

	if (name != other.name)
	{
		return false;
	}

	return index == other.index;
}