#ifndef CENG_GLSL_CONDITIONAL_EXPRESSION_H
#define CENG_GLSL_CONDITIONAL_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "LogicalOrExpression.h"
#include "Expression.h"

namespace Ceng
{
	class AssignmentExpression;

	class ConditionalExpression : public INonTerminal
	{
	public:

		std::shared_ptr<LogicalOrExpression> a;
		std::shared_ptr<Expression> b;
		std::shared_ptr<AssignmentExpression> c;

		bool full;

	public:

		void Release() override;

		ConditionalExpression(std::shared_ptr<LogicalOrExpression>& a);

		ConditionalExpression(std::shared_ptr<LogicalOrExpression>& a, std::shared_ptr<Expression>& b, std::shared_ptr<AssignmentExpression>& c);
	};
}

#endif