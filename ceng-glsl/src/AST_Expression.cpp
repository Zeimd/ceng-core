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