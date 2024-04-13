#include "PostfixExpression.h"
#include "FunctionCall.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

PostfixExpression::PostfixExpression(std::shared_ptr<PrimaryExpression>& primaryExpression)
	: INonTerminal(NonTerminalType::postfix_expression), postfixType(PostfixType::primary_expression), primaryExpression(primaryExpression)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, std::shared_ptr<IntegerExpression>& arrayIndex)
	: INonTerminal(NonTerminalType::postfix_expression), postfixType(PostfixType::array_index), postfixExpression(postfixExpression),arrayIndex(arrayIndex)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<FunctionCall>& functionCall)
	: INonTerminal(NonTerminalType::postfix_expression), postfixType(PostfixType::function_call), functionCall(functionCall)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, const Ceng::StringUtf8& fieldName)
	: INonTerminal(NonTerminalType::postfix_expression), postfixType(PostfixType::field_select), postfixExpression(postfixExpression),fieldName(fieldName)
{

}

PostfixExpression::PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, PostfixOperator::value type)
	: INonTerminal(NonTerminalType::postfix_expression), postfixExpression(postfixExpression)
{
	switch (type)
	{
	case PostfixOperator::dec_op:
		this->postfixType = PostfixType::dec_op;
		break;
	case PostfixOperator::inc_op:
		this->postfixType = PostfixType::inc_op;
		break;
	}
}

void PostfixExpression::Release()
{
	delete this;
}

Ceng::StringUtf8 PostfixExpression::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	switch (postfixType)
	{
	case PostfixType::primary_expression:
		return primaryExpression->ToString(indentLevel);
	case PostfixType::array_index:
		out = '[';
		out += arrayIndex->ToString(indentLevel);
		out += ']';
		return out;
	case PostfixType::function_call:
		return functionCall->ToString(indentLevel);
	case PostfixType::field_select:
		out = postfixExpression->ToString(indentLevel);
		out += '.';
		out += fieldName;
		return out;
	case PostfixType::inc_op:
		out += postfixExpression->ToString(indentLevel);
		out += "++";
		return out;
	case PostfixType::dec_op:
		out += postfixExpression->ToString(indentLevel);
		out += "--";
		return out;
		break;
	}

	return out;
}

void PostfixExpression::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_PostfixExpression(*this);
}