#include <ceng/GLSL/ArrayIndex.h>

#include <ceng/GLSL/VariableExpression.h>

using namespace Ceng::GLSL;

ArrayIndex::ArrayIndex(bool implicit)
	: value(0)
{
	if (implicit)
	{
		indexType = ArrayIndexType::implicit;
	}
	else
	{
		indexType = ArrayIndexType::unused;
	}
}

ArrayIndex::ArrayIndex(Ceng::INT32 value)
	: indexType(ArrayIndexType::uint_literal), value(value)
{

}


ArrayIndex::ArrayIndex(Ceng::UINT32 value)
	: indexType(ArrayIndexType::uint_literal), value(value)
{

}

ArrayIndex::ArrayIndex(const VariableExpression& expression)
	: indexType(ArrayIndexType::variable), value(std::make_unique<VariableExpression>(expression))
{

}

Ceng::StringUtf8 ArrayIndex::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (indexType)
	{
	case ArrayIndexType::unused:
		return "";
	case ArrayIndexType::implicit:
		return "[]";
	case ArrayIndexType::uint_literal:
		out = '[';
		out += std::get<Ceng::UINT32>(value);
		out += ']';
		return out;
	case ArrayIndexType::variable:
		out += '[';
		out += std::get<std::shared_ptr<VariableExpression>>(value)->ToString();
		out += ']';
		return out;
	case ArrayIndexType::invalid_value:
		out = '[';
		out += "<ERROR>";
		out += ']';
		return out;
	default:
		return "<UNHANDLED ARRAY INDEX TYPE>";
	}
}