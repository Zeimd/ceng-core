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
			two_complement,
		};
	}

	class UnaryOperator : public INonTerminal
	{
	public:

		UnaryOperatorType::value type;

	public:

		void Release() override;

		UnaryOperator(UnaryOperatorType::value type);

		UnaryOperator(const Token& token);

	};
}

#endif