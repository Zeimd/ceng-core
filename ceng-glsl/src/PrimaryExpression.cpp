#include "PrimaryExpression.h"

using namespace Ceng;

PrimaryExpression::PrimaryExpression(const Token& token)
	: INonTerminal(NonTerminalType::primary_expression)
{
	switch (token.type)
	{
	case TokenType::int_constant:
		type = ExpressionType::int_const;
		intValue = token.value.intVal;
		break;
	case TokenType::uint_constant:
		type = ExpressionType::uint_const;
		uintValue = token.value.intVal;
		break;
	case TokenType::float_constant:
		type = ExpressionType::float_const;
		floatValue = token.value.floatVal;
		break;
	case TokenType::bool_constant:
		type = ExpressionType::bool_const;
		boolValue = token.value.boolVal;
		break;
	case TokenType::identifier:
		type = ExpressionType::identifier;
		name = token.name;
		break;
	}
}

PrimaryExpression::PrimaryExpression(bool value)
	: INonTerminal(NonTerminalType::primary_expression),type(ExpressionType::bool_const),boolValue(value)
{
	
}

PrimaryExpression::PrimaryExpression(const Ceng::INT32 value)
	: INonTerminal(NonTerminalType::primary_expression), type(ExpressionType::int_const), intValue(value)
{

}

PrimaryExpression::PrimaryExpression(const Ceng::UINT32 value)
	: INonTerminal(NonTerminalType::primary_expression), type(ExpressionType::uint_const), uintValue(value)
{

}

PrimaryExpression::PrimaryExpression(const Ceng::FLOAT32 value)
	: INonTerminal(NonTerminalType::primary_expression), type(ExpressionType::float_const), floatValue(value)
{

}

PrimaryExpression::PrimaryExpression(const Ceng::StringUtf8& identifier)
	: INonTerminal(NonTerminalType::primary_expression), type(ExpressionType::identifier), name(identifier)
{

}

PrimaryExpression::PrimaryExpression(std::shared_ptr<Expression>& expression)
	: INonTerminal(NonTerminalType::primary_expression), type(ExpressionType::expression), expression(expression)
{

}

void PrimaryExpression::Release()
{
	delete this;
}

Ceng::StringUtf8 PrimaryExpression::ToString() const
{
	Ceng::StringUtf8 out;

	switch (type)
	{
	case ExpressionType::identifier:
		return name;
	case ExpressionType::int_const:
		return intValue;
	case ExpressionType::uint_const:
		return uintValue;
	case ExpressionType::float_const:
		return floatValue;
	case ExpressionType::bool_const:
		return boolValue;
	case ExpressionType::expression:
		return expression->ToString();
	}

	return "";
}