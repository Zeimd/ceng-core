#include "UnaryExpression.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void UnaryExpression::Release()
{
	delete this;
}

UnaryExpression::UnaryExpression(std::shared_ptr<PostfixExpression>& postfixExpression)
	: INonTerminal(NonTerminalType::unary_expression), postfixExpression(postfixExpression), unaryType(UnaryExpressionType::postfix_expression)
{

}

UnaryExpression::UnaryExpression(std::shared_ptr<UnaryExpression>& unaryExpression, PrefixOperator::value op)
	: INonTerminal(NonTerminalType::unary_expression), unaryExpression(unaryExpression)
{
	switch (op)
	{
	case PrefixOperator::inc_op:
		unaryType = UnaryExpressionType::inc_op;
		break;
	case PrefixOperator::dec_op:
		unaryType = UnaryExpressionType::dec_op;
		break;
	default:
		unaryType = UnaryExpressionType::invalid_value;
		break;
	}
}

UnaryExpression::UnaryExpression(std::shared_ptr<UnaryOperator>& op, std::shared_ptr<UnaryExpression>& unaryExpression)
	: INonTerminal(NonTerminalType::unary_expression), unaryExpression(unaryExpression)
{
	switch (op->type)
	{
	case UnaryOperatorType::logical_not:
		unaryType = UnaryExpressionType::logical_not;
		break;
	case UnaryOperatorType::two_complement:
		unaryType = UnaryExpressionType::two_complement;
		break;
	case UnaryOperatorType::plus:
		unaryType = UnaryExpressionType::plus;
		break;
	case UnaryOperatorType::negation:
		unaryType = UnaryExpressionType::negation;
		break;
	default:
		unaryType = UnaryExpressionType::invalid_value;
		break;
	}

	
}

Ceng::StringUtf8 UnaryExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (unaryType)
	{
	case UnaryExpressionType::postfix_expression:
		return postfixExpression->ToString(indentLevel);
	case UnaryExpressionType::inc_op:
		out = "++";
		out += unaryExpression->ToString(indentLevel);
		return out;
	case UnaryExpressionType::dec_op:
		out = "--";
		out += unaryExpression->ToString(indentLevel);
		return out;
	case UnaryExpressionType::plus:
		out = "+";
		out += unaryExpression->ToString(indentLevel);
		return out;
	case UnaryExpressionType::negation:
		out = "-";
		out += unaryExpression->ToString(indentLevel);
		return out;
	case UnaryExpressionType::logical_not:
		out = "!";
		out += unaryExpression->ToString(indentLevel);
		return out;
	case UnaryExpressionType::two_complement:
		out = "~";
		out += unaryExpression->ToString(indentLevel);
		return out;
	}

	return "<UNHANDLED UNARY TYPE>";
}

void UnaryExpression::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_UnaryExpression(*this);
}