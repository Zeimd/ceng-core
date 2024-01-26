#ifndef CENG_GLSL_RELATIONAL_EXPRESSION_H
#define CENG_GLSL_RELATIONAL_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "ShiftExpression.h"

namespace Ceng
{
	namespace RelativeOp
	{
		enum value
		{
			less,
			greater,
			less_or_equal,
			greater_or_equal,
			unassigned,
		};
	}

	class RelationalExpression : public INonTerminal
	{
	public:

		std::shared_ptr<RelationalExpression> lhs;
		std::shared_ptr<ShiftExpression> rhs;

		RelativeOp::value operation;

	public:

		void Release() override;

		RelationalExpression(std::shared_ptr<ShiftExpression>& addEx);

		RelationalExpression(std::shared_ptr<RelationalExpression>& lhs, const Token& token, std::shared_ptr<ShiftExpression>& rhs);

		RelationalExpression(std::shared_ptr<RelationalExpression>& lhs, RelativeOp::value operation, std::shared_ptr<ShiftExpression>& rhs);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif