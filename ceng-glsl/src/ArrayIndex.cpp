#include <ceng/GLSL/ArrayIndex.h>

using namespace Ceng::GLSL;

ArrayIndex::ArrayIndex()
	: indexType(ArrayIndexType::unused), value(0)
{

}

ArrayIndex::ArrayIndex(Ceng::UINT32 value)
	: indexType(ArrayIndexType::uint_literal), value(value)
{

}

ArrayIndex::ArrayIndex(Ceng::StringUtf8 variable)
	: indexType(ArrayIndexType::variable), value(variable)
{

}

Ceng::StringUtf8 ArrayIndex::ToString(Ceng::UINT32 indentLevel) const
{
	switch (indexType)
	{
	case ArrayIndexType::unused:
		return "";
	case ArrayIndexType::uint_literal:
		return std::get<Ceng::UINT32>(value);
	case ArrayIndexType::variable:
		return std::get<Ceng::StringUtf8>(value);
	default:
		return "<UNHANDLED ARRAY INDEX TYPE>";
	}
}