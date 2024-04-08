#ifndef CENG_GLSL_LOGICAL_OR_EXPRESSION_H
#define CENG_GLSL_LOGICAL_OR_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "LogicalXorExpression.h"

namespace Ceng
{
	class LogicalOrExpression : public INonTerminal
	{
	public:

		std::shared_ptr<LogicalOrExpression> lhs;
		std::shared_ptr<LogicalXorExpression> rhs;

		bool full;

	public:

		void Release() override;

		LogicalOrExpression(std::shared_ptr<LogicalXorExpression>& addEx);

		LogicalOrExpression(std::shared_ptr<LogicalOrExpression>& lhs, std::shared_ptr<LogicalXorExpression>& rhs);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif