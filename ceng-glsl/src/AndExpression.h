#ifndef CENG_GLSL_AND_EXPRESSION_H
#define CENG_GLSL_AND_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "EqualityExpression.h"

namespace Ceng
{
	class AndExpression : public INonTerminal
	{
	public:

		std::shared_ptr<AndExpression> lhs;
		std::shared_ptr<EqualityExpression> rhs;

		bool full;

	public:

		void Release() override;

		AndExpression(std::shared_ptr<EqualityExpression>& addEx);

		AndExpression(std::shared_ptr<AndExpression>& lhs, std::shared_ptr<EqualityExpression>& rhs);
	};
}

#endif