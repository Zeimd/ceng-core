#ifndef CENG_GLSL_CONSTANT_EXPRESSION_H
#define CENG_GLSL_CONSTANT_EXPRESSION_H

#include "INonTerminal.h"

namespace Ceng
{
	class ConstantExpression : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif