#include "UnaryExpression.h"

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
	}
}