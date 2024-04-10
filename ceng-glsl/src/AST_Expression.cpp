#include <ceng/GLSL/AST_Expression.h>

using namespace Ceng::GLSL;

AST_Expression::AST_Expression(bool value)
	: expressionType(AST_ExpressionType::bool_literal), value(value)
{

}

AST_Expression::AST_Expression(Ceng::INT32 value)
	: expressionType(AST_ExpressionType::int_literal), value(value)
{

}

AST_Expression::AST_Expression(Ceng::UINT32 value)
	: expressionType(AST_ExpressionType::uint_literal), value(value)
{

}

AST_Expression::AST_Expression(Ceng::FLOAT32 value)
	: expressionType(AST_ExpressionType::float_literal), value(value)
{

}

AST_Expression::AST_Expression(Ceng::StringUtf8& name)
	: expressionType(AST_ExpressionType::identifier), value(name)
{

}

AST_Expression::~AST_Expression()
{

}

Ceng::StringUtf8 AST_Expression::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (expressionType)
	{
	case AST_ExpressionType::bool_literal:
		if (std::get<bool>(value) == true)
		{
			return "true";
		}
		else
		{
			return "false";
		}
		break;
	case AST_ExpressionType::int_literal:
		out = std::get<Ceng::INT32>(value);
		break;
	case AST_ExpressionType::uint_literal:
		out = std::get<Ceng::UINT32>(value);
		break;
	case AST_ExpressionType::float_literal:
		out = std::get<Ceng::FLOAT32>(value);
		break;
	case AST_ExpressionType::identifier:
		out = std::get<Ceng::StringUtf8>(value);
		break;
	default:
		out = "<UNHANDLED AST EXPRESSION TYPE>";
	}

	return out;
}