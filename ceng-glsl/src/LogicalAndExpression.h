#ifndef CENG_GLSL_LOGICAL_AND_EXPRESSION_H
#define CENG_GLSL_LOGICAL_AND_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "OrExpression.h"

namespace Ceng
{
	class LogicalAndExpression : public INonTerminal
	{
	public:

		std::shared_ptr<LogicalAndExpression> lhs;
		std::shared_ptr<OrExpression> rhs;

		bool full;

	public:

		void Release() override;

		LogicalAndExpression(std::shared_ptr<OrExpression>& addEx);

		LogicalAndExpression(std::shared_ptr<LogicalAndExpression>& lhs, std::shared_ptr<OrExpression>& rhs);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif