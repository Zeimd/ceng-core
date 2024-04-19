#include "PrimaryExpression.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

PrimaryExpression::PrimaryExpression(const Token& token)
	: INonTerminal(NonTerminalType::primary_expression)
{
	switch (token.type)
	{
	case TokenType::int_constant:
		valuetype = ExpressionType::int_const;
		intValue = token.value.intVal;
		isInteger = true;
		isConst = true;
		break;
	case TokenType::uint_constant:
		valuetype = ExpressionType::uint_const;
		uintValue = token.value.intVal;
		isInteger = true;
		isConst = true;
		break;
	case TokenType::float_constant:
		valuetype = ExpressionType::float_const;
		floatValue = token.value.floatVal;
		isConst = true;
		break;
	case TokenType::bool_constant:
		valuetype = ExpressionType::bool_const;
		boolValue = token.value.boolVal;
		isConst = true;
		break;
		/*
	case TokenType::identifier:
		valuetype = ExpressionType::identifier;
		name = token.name;
		break;
		*/
	}
}

PrimaryExpression::PrimaryExpression(bool value)
	: INonTerminal(NonTerminalType::primary_expression), valuetype(ExpressionType::bool_const),boolValue(value)
{
	
}

PrimaryExpression::PrimaryExpression(const Ceng::INT32 value)
	: INonTerminal(NonTerminalType::primary_expression), valuetype(ExpressionType::int_const), intValue(value)
{

}

PrimaryExpression::PrimaryExpression(const Ceng::UINT32 value)
	: INonTerminal(NonTerminalType::primary_expression), valuetype(ExpressionType::uint_const), uintValue(value)
{

}

PrimaryExpression::PrimaryExpression(const Ceng::FLOAT32 value)
	: INonTerminal(NonTerminalType::primary_expression), valuetype(ExpressionType::float_const), floatValue(value)
{

}

PrimaryExpression::PrimaryExpression(const SymbolLink& identifier)
	: INonTerminal(NonTerminalType::primary_expression), valuetype(ExpressionType::identifier), identifier(identifier)
{

}

PrimaryExpression::PrimaryExpression(std::shared_ptr<Expression>& expression)
	: INonTerminal(NonTerminalType::primary_expression), valuetype(ExpressionType::expression), expression(expression)
{

}

void PrimaryExpression::Release()
{
	delete this;
}

Ceng::StringUtf8 PrimaryExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (valuetype)
	{
	case ExpressionType::identifier:
		return *identifier.Get()->Name();
	case ExpressionType::int_const:
		return intValue;
	case ExpressionType::uint_const:
		return uintValue;
	case ExpressionType::float_const:
		return floatValue;
	case ExpressionType::bool_const:
		return boolValue;
	case ExpressionType::expression:
		out = '(';
		out += expression->ToString(indentLevel);
		out += ')';
		return out;
	default:
		return "<UNHANDLED PRIMARY EXPRESSION>";
	}

	return "";
}

void PrimaryExpression::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_PrimaryExpression(*this);
}