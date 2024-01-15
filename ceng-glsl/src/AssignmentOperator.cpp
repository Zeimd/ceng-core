#include "AssignmentOperator.h"

using namespace Ceng;

void AssignmentOperator::Release()
{
	delete this;
}

AssignmentOperator::AssignmentOperator(const Token& token)
	: INonTerminal(NonTerminalType::assignment_operator)
{
	switch (token.type)
	{
	case TokenType::equal:
		operation = AssignOpType::equal;
		break;
	case TokenType::and_assign:
		operation = AssignOpType::and_op;
		break;
	case TokenType::or_assign:
		operation = AssignOpType::or_op;
		break;
	case TokenType::xor_assign:
		operation = AssignOpType::xor_op;
		break;
	case TokenType::left_assign:
		operation = AssignOpType::left;
		break;
	case TokenType::right_assign:
		operation = AssignOpType::right;
		break;
	case TokenType::add_assign:
		operation = AssignOpType::add;
		break;
	case TokenType::sub_assign:
		operation = AssignOpType::sub;
		break;
	case TokenType::mul_assign:
		operation = AssignOpType::mul;
		break;
	case TokenType::div_assign:
		operation = AssignOpType::div;
		break;
	case TokenType::mod_assign:
		operation = AssignOpType::mod;
		break;

	}
}

AssignmentOperator::AssignmentOperator(AssignOpType::value operation)
	: INonTerminal(NonTerminalType::assignment_operator), operation(operation)
{

}