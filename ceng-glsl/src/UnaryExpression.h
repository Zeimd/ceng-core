#ifndef CENG_GLSL_UNARY_EXPRESSION_H
#define CENG_GLSL_UNARY_EXPRESSION_H

#include <memory>

#include "INonTerminal.h"
#include "PostfixExpression.h"
#include "UnaryOperator.h"

namespace Ceng
{
	namespace UnaryExpressionType
	{
		enum value
		{
			postfix_expression,
			inc_op,
			dec_op,
			plus,
			negation,
			logical_not,
			two_complement,
		};
	}

	namespace PrefixOperator
	{
		enum value
		{
			inc_op,
			dec_op,
		};
	}

	class UnaryExpression : public INonTerminal
	{
	public:

		UnaryExpressionType::value unaryType;

		std::shared_ptr<PostfixExpression> postfixExpression;
		std::shared_ptr<UnaryExpression> unaryExpression;

	public:

		void Release() override;

		UnaryExpression(std::shared_ptr<PostfixExpression>& postfixExpression);

		UnaryExpression(std::shared_ptr<UnaryExpression>& unaryExpression, PrefixOperator::value op);

		UnaryExpression(std::shared_ptr<UnaryOperator>& op, std::shared_ptr<UnaryExpression>& unaryExpression);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif