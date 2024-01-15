#include "AndExpression.h"

using namespace Ceng;

void AndExpression::Release()
{
	delete this;
}

AndExpression::AndExpression(std::shared_ptr<EqualityExpression>& mulEx)
	: INonTerminal(NonTerminalType::and_expression), rhs(mulEx), operation(EqualityOp::unassigned)
{

}

AndExpression::AndExpression(std::shared_ptr<AndExpression>& lhs, std::shared_ptr<EqualityExpression>& rhs)
	: INonTerminal(NonTerminalType::and_expression), lhs(lhs), operation(operation), rhs(rhs)
{

}