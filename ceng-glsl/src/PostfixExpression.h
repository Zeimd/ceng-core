#ifndef CENG_GLSL_POSTFIX_EXPRESSION_H
#define CENG_GLSL_POSTFIX_EXPRESSION_H

#include <memory>
#include "INonTerminal.h"
#include "IntegerExpression.h"
#include "PrimaryExpression.h"

namespace Ceng
{
	class FunctionCall;

	namespace PostfixOperator
	{
		enum value
		{
			inc_op,
			dec_op,
		};
	}

	namespace PostfixType
	{
		enum value
		{
			primary_expression,
			array_index,
			function_call,
			field_select,
			inc_op,
			dec_op,
		};
	}

	class PostfixExpression : public INonTerminal
	{
	public:

		std::shared_ptr<PrimaryExpression> primaryExpression;

		std::shared_ptr<IntegerExpression> arrayIndex;

		std::shared_ptr<FunctionCall> functionCall;

		std::shared_ptr<PostfixExpression> postfixExpression;
		Ceng::StringUtf8 fieldName;

		PostfixType::value type;
	public:

		void Release() override;

		PostfixExpression(std::shared_ptr<PrimaryExpression>& primaryExpression);

		PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, std::shared_ptr<IntegerExpression>& arrayIndex);

		PostfixExpression(std::shared_ptr<FunctionCall>& functionCall);

		PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, PostfixOperator::value type);

		PostfixExpression(std::shared_ptr<PostfixExpression>& postfixExpression, const Ceng::StringUtf8& fieldName);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif