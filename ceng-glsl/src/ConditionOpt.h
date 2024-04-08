#ifndef CENG_GLSL_CONDITION_OPT_H
#define CENG_GLSL_CONDITION_OPT_H

#include "INonTerminal.h"

namespace Ceng
{
	class ConditionOpt : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif