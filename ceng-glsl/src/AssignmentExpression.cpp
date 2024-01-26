#include "AssignmentExpression.h"

using namespace Ceng;


void AssignmentExpression::Release()
{
	delete this;
}

AssignmentExpression::AssignmentExpression(std::shared_ptr<ConditionalExpression>& cond)
	: INonTerminal(NonTerminalType::assignment_expression), cond(cond), full(false)
{

}

AssignmentExpression::AssignmentExpression(std::shared_ptr<UnaryExpression>& unaryEx, std::shared_ptr<AssignmentOperator>& op, std::shared_ptr<AssignmentExpression>& assignEx)
	: INonTerminal(NonTerminalType::assignment_expression), unaryEx(unaryEx), op(op), assignEx(assignEx), full(true)
{

}

Ceng::StringUtf8 AssignmentExpression::ToString() const
{
	return "";
}