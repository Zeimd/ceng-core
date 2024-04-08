#ifndef CENG_GLSL_EQUALITY_EXPRESSION_H
#define CENG_GLSL_EQUALITY_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "RelationalExpression.h"

namespace Ceng
{
	namespace EqualityOp
	{
		enum value
		{
			equal,
			not_equal,
			unassigned,
			invalid_value,
		};
	}

	class EqualityExpression : public INonTerminal
	{
	public:

		std::shared_ptr<EqualityExpression> lhs;
		std::shared_ptr<RelationalExpression> rhs;

		EqualityOp::value operation;

	public:

		void Release() override;

		EqualityExpression(std::shared_ptr<RelationalExpression>& addEx);

		EqualityExpression(std::shared_ptr<EqualityExpression>& lhs, const Token& token, std::shared_ptr<RelationalExpression>& rhs);

		EqualityExpression(std::shared_ptr<EqualityExpression>& lhs, EqualityOp::value operation, std::shared_ptr<RelationalExpression>& rhs);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif