#ifndef CENG_GLSL_UNARY_OPERATOR_H
#define CENG_GLSL_UNARY_OPERATOR_H

#include <ceng/GLSL/Token.h>

#include "INonTerminal.h"

namespace Ceng
{
	namespace UnaryOperatorType
	{
		enum value
		{
			plus,
			negation,
			logical_not,
			bit_flip,
			invalid_value
		};
	}

	class UnaryOperator : public INonTerminal
	{
	public:

		UnaryOperatorType::value operatorType;

	public:

		void Release() override;

		UnaryOperator(UnaryOperatorType::value operatorType);

		UnaryOperator(const Token& token);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

	};
}

#endif