#include "AssignmentOperator.h"
#include "AST_Visitor.h"

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

Ceng::StringUtf8 AssignmentOperator::ToString(unsigned int indentLevel) const
{
	switch (operation)
	{
	case AssignOpType::equal:
		return "=";
	case AssignOpType::add:
		return "+=";
	case AssignOpType::sub:
		return "-=";
	case AssignOpType::mul:
		return "*=";
	case AssignOpType::div:
		return "/=";
	case AssignOpType::mod:
		return "%=";
	case AssignOpType::left:
		return "<<=";
	case AssignOpType::right:
		return ">>=";
	case AssignOpType::and_op:
		return "&=";
	case AssignOpType::or_op:
		return "|=";
	case AssignOpType::xor_op:
		return "^=";
	default:
		return "<UNHANDLED ASSIGNMENT OPERATOR>";

	}
}

void AssignmentOperator::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_AssignmentOperator(*this);
}