#ifndef CENG_GLSL_ASSIGNMENT_EXPRESSION_H
#define CENG_GLSL_ASSIGNMENT_EXPRESSION_H

#include <memory>

#include "INonTerminal.h"

#include "ConditionalExpression.h"
#include "UnaryExpression.h"
#include "AssignmentOperator.h"

namespace Ceng
{
	class AssignmentExpression : public INonTerminal
	{
	public:
		std::shared_ptr<ConditionalExpression> cond;

		std::shared_ptr<UnaryExpression> unaryEx;
		std::shared_ptr<AssignmentOperator> op;
		std::shared_ptr<AssignmentExpression> assignEx;

		bool full;

	public:

		void Release() override;

		AssignmentExpression(std::shared_ptr<ConditionalExpression>& cond);

		AssignmentExpression(std::shared_ptr<UnaryExpression>& unaryEx, std::shared_ptr<AssignmentOperator>& op, std::shared_ptr<AssignmentExpression>& assignEx);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif