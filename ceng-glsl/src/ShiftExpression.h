#ifndef CENG_GLSL_SHIFT_EXPRESSION_H
#define CENG_GLSL_SHIFT_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "AdditiveExpression.h"

namespace Ceng
{
	namespace ShiftOp
	{
		enum value
		{
			left,
			right,
			unassigned,
			invalid_value,
		};
	}

	class ShiftExpression : public INonTerminal
	{
	public:

		std::shared_ptr<ShiftExpression> lhs;
		std::shared_ptr<AdditiveExpression> rhs;

		ShiftOp::value operation;

	public:

		void Release() override;

		ShiftExpression(std::shared_ptr<AdditiveExpression>& addEx);

		ShiftExpression(std::shared_ptr<ShiftExpression>& lhs, const Token& token, std::shared_ptr<AdditiveExpression>& rhs);

		ShiftExpression(std::shared_ptr<ShiftExpression>& lhs, ShiftOp::value operation, std::shared_ptr<AdditiveExpression>& rhs);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif