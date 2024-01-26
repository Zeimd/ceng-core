#ifndef CENG_GLSL_LOGICAL_XOR_EXPRESSION_H
#define CENG_GLSL_LOGICAL_XOR_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "LogicalAndExpression.h"

namespace Ceng
{
	class LogicalXorExpression : public INonTerminal
	{
	public:

		std::shared_ptr<LogicalXorExpression> lhs;
		std::shared_ptr<LogicalAndExpression> rhs;

		bool full;

	public:

		void Release() override;

		LogicalXorExpression(std::shared_ptr<LogicalAndExpression>& addEx);

		LogicalXorExpression(std::shared_ptr<LogicalXorExpression>& lhs, std::shared_ptr<LogicalAndExpression>& rhs);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif