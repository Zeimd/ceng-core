#include <ceng/GLSL/ArrayIndex.h>

#include <ceng/GLSL/VariableExpression.h>

using namespace Ceng::GLSL;

ArrayIndex::ArrayIndex()
	: value(0U), indexType(ArrayIndexType::invalid_value)
{

}

ArrayIndex::ArrayIndex(bool implicit)
	: value(0U)
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
	: indexType(ArrayIndexType::uint_literal), value(Ceng::UINT32(value))
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

bool ArrayIndex::operator == (const ArrayIndex& other) const
{
	switch (indexType)
	{
	case ArrayIndexType::unused:		
	case ArrayIndexType::implicit:
		return indexType == other.indexType;
	case ArrayIndexType::uint_literal:
		return std::get<Ceng::UINT32>(value) == std::get<Ceng::UINT32>(other.value);
	case ArrayIndexType::variable:
		return *std::get<std::shared_ptr<VariableExpression>>(value) == 
			*std::get<std::shared_ptr<VariableExpression>>(other.value);
	}

	return false;
}

bool ArrayIndex::HasSize() const
{
	switch (indexType)
	{
	case ArrayIndexType::uint_literal:
	case ArrayIndexType::variable:
		return true;
	}

	return false;
}

bool ArrayIndex::IsArray() const
{
	switch (indexType)
	{
	case ArrayIndexType::implicit:
	case ArrayIndexType::uint_literal:
	case ArrayIndexType::variable:
	case ArrayIndexType::invalid_value:
		return true;
	}

	return false;
}

Ceng::UINT32 ArrayIndex::GetInt() const
{
	return std::get<Ceng::UINT32>(value);
}

const std::shared_ptr<VariableExpression>& ArrayIndex::GetVariable() const
{
	return std::get< std::shared_ptr<VariableExpression>>(value);
}