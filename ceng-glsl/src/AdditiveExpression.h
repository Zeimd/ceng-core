#ifndef CENG_GLSL_ADDITIVE_EXPRESSION_H
#define CENG_GLSL_ADDITIVE_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "MultiplicativeExpression.h"

namespace Ceng
{
	namespace AdditiveOp
	{
		enum value
		{
			add,
			sub,
			unassigned,
		};
	}

	class AdditiveExpression : public INonTerminal
	{
	public:

		std::shared_ptr<AdditiveExpression> lhs;
		std::shared_ptr<MultiplicativeExpression> rhs;

		AdditiveOp::value operation;

	public:

		void Release() override;

		AdditiveExpression(std::shared_ptr<MultiplicativeExpression>& unaryEx);

		AdditiveExpression(std::shared_ptr<AdditiveExpression>& lhs, const Token& token, std::shared_ptr<MultiplicativeExpression>& rhs);

		AdditiveExpression(std::shared_ptr<AdditiveExpression>& lhs, AdditiveOp::value operation, std::shared_ptr<MultiplicativeExpression>& rhs);
	};
}

#endif