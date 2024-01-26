#include "XorExpression.h"

using namespace Ceng;

void XorExpression::Release()
{
	delete this;
}

XorExpression::XorExpression(std::shared_ptr<AndExpression>& mulEx)
	: INonTerminal(NonTerminalType::xor_expression), rhs(mulEx), full(false)
{

}

XorExpression::XorExpression(std::shared_ptr<XorExpression>& lhs, std::shared_ptr<AndExpression>& rhs)
	: INonTerminal(NonTerminalType::xor_expression), lhs(lhs), rhs(rhs), full(true)
{

}

Ceng::StringUtf8 XorExpression::ToString() const
{
	return "";
}