#ifndef CENG_GLSL_XOR_EXPRESSION_H
#define CENG_GLSL_XOR_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "AndExpression.h"

namespace Ceng
{
	class XorExpression : public INonTerminal
	{
	public:

		std::shared_ptr<XorExpression> lhs;
		std::shared_ptr<AndExpression> rhs;

		bool full;

	public:

		void Release() override;

		XorExpression(std::shared_ptr<AndExpression>& addEx);

		XorExpression(std::shared_ptr<XorExpression>& lhs, std::shared_ptr<AndExpression>& rhs);
	};
}

#endif