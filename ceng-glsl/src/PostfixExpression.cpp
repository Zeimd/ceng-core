#include "PostfixExpression.h"

using namespace Ceng;

PostfixExpression::PostfixExpression(std::shared_ptr<PrimaryExpression>& primaryExpression)
	: INonTerminal(NonTerminalType::postfix_expression), type(PostfixType::primary_expression), primaryExpression(primaryExpression)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, std::shared_ptr<IntegerExpression>& arrayIndex)
	: INonTerminal(NonTerminalType::postfix_expression), type(PostfixType::array_index), postfixExpression(postfixExpression),arrayIndex(arrayIndex)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<FunctionCall>& functionCall)
	: INonTerminal(NonTerminalType::postfix_expression), type(PostfixType::function_call), functionCall(functionCall)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, const Ceng::StringUtf8& fieldName)
	: INonTerminal(NonTerminalType::postfix_expression), type(PostfixType::field_select), postfixExpression(postfixExpression),fieldName(fieldName)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, PostfixOperator::value type)
	: INonTerminal(NonTerminalType::postfix_expression), postfixExpression(postfixExpression)
{
	switch (type)
	{
	case PostfixOperator::dec_op:
		this->type = PostfixType::dec_op;
		break;
	case PostfixOperator::inc_op:
		this->type = PostfixType::inc_op;
		break;
	}
}

void PostfixExpression::Release()
{
	delete this;
}