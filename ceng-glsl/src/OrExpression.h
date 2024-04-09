#ifndef CENG_GLSL_OR_EXPRESSION_H
#define CENG_GLSL_OR_EXPRESSION_H

#include <memory>

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"
#include "XorExpression.h"

namespace Ceng
{
	class OrExpression : public INonTerminal
	{
	public:

		std::shared_ptr<OrExpression> lhs;
		std::shared_ptr<XorExpression> rhs;

		bool full;

	public:

		void Release() override;

		OrExpression(std::shared_ptr<XorExpression>& addEx);

		OrExpression(std::shared_ptr<OrExpression>& lhs, std::shared_ptr<XorExpression>& rhs);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif