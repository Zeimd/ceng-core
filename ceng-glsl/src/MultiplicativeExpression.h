#ifndef CENG_GLSL_MULTIPLICATIVE_EXPRESSION_H
#define CENG_GLSL_MULTIPLICATIVE_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "UnaryExpression.h"

namespace Ceng
{
	namespace MultiplicativeOp
	{
		enum value
		{
			mul,
			div,
			mod,
			unassigned,
		};
	}

	class MultiplicativeExpression : public INonTerminal
	{
	public:

		std::shared_ptr<MultiplicativeExpression> lhs;
		std::shared_ptr<UnaryExpression> rhs;

		MultiplicativeOp::value operation;

	public:

		void Release() override;

		MultiplicativeExpression(std::shared_ptr<UnaryExpression>& unaryEx);

		MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& lhs, const Token& token, std::shared_ptr<UnaryExpression>& rhs);

		MultiplicativeExpression(std::shared_ptr<MultiplicativeExpression>& lhs, MultiplicativeOp::value operation, std::shared_ptr<UnaryExpression>& rhs);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif