#include "PostfixExpression.h"
#include "FunctionCall.h"

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

Ceng::StringUtf8 PostfixExpression::ToString() const
{
	Ceng::StringUtf8 out;

	switch (type)
	{
	case PostfixType::primary_expression:
		return primaryExpression->ToString();
	case PostfixType::array_index:
		out = '[';
		out += arrayIndex->ToString();
		out += ']';
		return out;
	case PostfixType::function_call:
		return functionCall->ToString();
	case PostfixType::field_select:
		out = postfixExpression->ToString();
		out += '.';
		out += fieldName;
		return out;
	case PostfixType::inc_op:
		out += postfixExpression->ToString();
		out += "++";
		return out;
	case PostfixType::dec_op:
		out += postfixExpression->ToString();
		out += "--";
		return out;
		break;
	}

	return out;
}