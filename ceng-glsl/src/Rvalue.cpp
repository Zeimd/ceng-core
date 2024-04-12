#include <ceng/GLSL/Rvalue.h>

using namespace Ceng::GLSL;

Rvalue::Rvalue()
	: valueType(RvalueType::unused), value(false)
{

}


Rvalue::Rvalue(bool value)
	: valueType(RvalueType::bool_literal), value(value)
{

}

Rvalue::Rvalue(Ceng::INT32 value)
	: valueType(RvalueType::int_literal), value(value)
{

}

Rvalue::Rvalue(Ceng::UINT32 value)
	: valueType(RvalueType::uint_literal), value(value)
{

}

Rvalue::Rvalue(Ceng::FLOAT32 value)
	: valueType(RvalueType::float_literal), value(value)
{

}

Rvalue::Rvalue(Ceng::StringUtf8& name)
	: valueType(RvalueType::identifier), value(name)
{

}

Rvalue::~Rvalue()
{

}

Ceng::StringUtf8 Rvalue::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (valueType)
	{
	case RvalueType::bool_literal:
		if (std::get<bool>(value) == true)
		{
			return "true";
		}
		else
		{
			return "false";
		}
		break;
	case RvalueType::int_literal:
		out = std::get<Ceng::INT32>(value);
		break;
	case RvalueType::uint_literal:
		out = std::get<Ceng::UINT32>(value);
		break;
	case RvalueType::float_literal:
		out = std::get<Ceng::FLOAT32>(value);
		break;
	case RvalueType::identifier:
		out = std::get<Ceng::StringUtf8>(value);
		break;
	default:
		out = "<UNHANDLED AST EXPRESSION TYPE>";
	}

	return out;
}