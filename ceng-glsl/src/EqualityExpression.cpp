#include "EqualityExpression.h"

#include "AST_Visitor.h"

using namespace Ceng;

void EqualityExpression::Release()
{
	delete this;
}

EqualityExpression::EqualityExpression(std::shared_ptr<RelationalExpression>& mulEx)
	: INonTerminal(NonTerminalType::equality_expression), rhs(mulEx), operation(EqualityOp::unassigned)
{

}

EqualityExpression::EqualityExpression(std::shared_ptr<EqualityExpression>& lhs, const Token& token, std::shared_ptr<RelationalExpression>& rhs)
	: INonTerminal(NonTerminalType::equality_expression), lhs(lhs), rhs(rhs)
{
	switch (token.type)
	{
	case TokenType::eq_op:
		operation = EqualityOp::equal;
		break;
	case TokenType::ne_op:
		operation = EqualityOp::not_equal;
		break;
	default:
		operation = EqualityOp::invalid_value;
		break;
	}
}

EqualityExpression::EqualityExpression(std::shared_ptr<EqualityExpression>& lhs, EqualityOp::value operation, std::shared_ptr<RelationalExpression>& rhs)
	: INonTerminal(NonTerminalType::equality_expression), lhs(lhs), operation(operation), rhs(rhs)
{

}

Ceng::StringUtf8 EqualityExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (operation == EqualityOp::unassigned)
	{
		return rhs->ToString(indentLevel);
	}

	out = lhs->ToString(indentLevel);
	out += ' ';

	switch (operation)
	{
	case EqualityOp::equal:
		out += "==";
		break;
	case EqualityOp::not_equal:
		out += "!=";
		break;
	case EqualityOp::invalid_value:
		out += "<INVALID EQUALITY OP>";
		break;
	default:
		out += "<UNHANDLED EQUALITY OP>";
		break;
	}

	out += ' ';
	out += rhs->ToString(indentLevel);

	return out;
}

void EqualityExpression::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_EqualityExpression(*this);
}