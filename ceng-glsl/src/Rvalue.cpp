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
	: valueType(RvalueType::variable), value(FieldExpression(name))
{

}

Rvalue::Rvalue(std::vector<FieldExpression>&& expression)
	: valueType(RvalueType::variable), value(VariableExpression(std::move(expression)))
{

}

Rvalue::Rvalue(const Lvalue& lvalue)
	: valueType(RvalueType::variable), value(lvalue.expression)
{

}

Rvalue::~Rvalue()
{

}

Lvalue Rvalue::ToLvalue() const
{
	switch (valueType)
	{
	case RvalueType::variable:
		return { std::get<VariableExpression>(value) };

	default:
		return Lvalue();
	}
}

bool Rvalue::IsLiteral() const
{
	switch (valueType)
	{
	case RvalueType::bool_literal:
	case RvalueType::int_literal:
	case RvalueType::uint_literal:
	case RvalueType::float_literal:
		return true;
	}

	return false;
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
	case RvalueType::variable:
		{
			auto& temp = std::get<VariableExpression>(value);
			out = temp.ToString();
		}
		break;
	default:
		out = "<UNHANDLED AST EXPRESSION TYPE>";
	}

	return out;
}

void Rvalue::PreIncr()
{
	switch (valueType)
	{
	case RvalueType::int_literal:
		{
			Ceng::INT32 in = std::get<Ceng::INT32>(value);
			value = in + 1;
		}	
		break;
	case RvalueType::uint_literal:
		{
			Ceng::UINT32 in = std::get<Ceng::UINT32>(value);
			value = in + 1;
		}
		break;
	case RvalueType::float_literal:
		{
			Ceng::FLOAT32 in = std::get<Ceng::FLOAT32>(value);
			value = in + 1.0f;
		}
		break;		
	}
}

void Rvalue::PreDec()
{
	switch (valueType)
	{
	case RvalueType::int_literal:
	{
		Ceng::INT32 in = std::get<Ceng::INT32>(value);
		value = in - 1;
	}
	break;
	case RvalueType::uint_literal:
	{
		Ceng::UINT32 in = std::get<Ceng::UINT32>(value);
		value = in - 1;
	}
	break;
	case RvalueType::float_literal:
	{
		Ceng::FLOAT32 in = std::get<Ceng::FLOAT32>(value);
		value = in - 1.0f;
	}
	break;
	}
}

void Rvalue::UnaryOp(UnaryOperation::value op)
{
	switch (op)
	{
	case UnaryOperation::negation:
		switch (valueType)
		{
		case RvalueType::int_literal:
			{
				Ceng::INT32 in = std::get<Ceng::INT32>(value);
				value = -in;
			}
			break;
		case RvalueType::uint_literal:
			{
				Ceng::UINT32 in = std::get<Ceng::UINT32>(value);
				value = -Ceng::INT32(in);
			}
			break;
		case RvalueType::float_literal:
			{
				Ceng::FLOAT32 in = std::get<Ceng::FLOAT32>(value);
				value = -in;
			}
			break;
		}
		return;
	case UnaryOperation::bitwise_not:
		switch (valueType)
		{
		case RvalueType::int_literal:
		{
			Ceng::INT32 in = std::get<Ceng::INT32>(value);
			value = ~in;
		}
		break;
		case RvalueType::uint_literal:
		{
			Ceng::UINT32 in = std::get<Ceng::UINT32>(value);
			value = ~in;
		}
		break;
		}
		return;
	case UnaryOperation::logical_not:
		switch (valueType)
		{
		case RvalueType::int_literal:
		{
			Ceng::INT32 in = std::get<Ceng::INT32>(value);
			value = !in;
		}
		break;
		case RvalueType::uint_literal:
		{
			Ceng::UINT32 in = std::get<Ceng::UINT32>(value);
			value = !in;
		}
		break;
		}
		return;
	}
}