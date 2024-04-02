#ifndef CENG_GLSL_INTEGER_EXPRESSION_H
#define CENG_GLSL_INTEGER_EXPRESSION_H

#include "INonTerminal.h"

namespace Ceng
{
	class IntegerExpression : public INonTerminal
	{
	public:

		IntegerExpression();

		void Release() override;

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif