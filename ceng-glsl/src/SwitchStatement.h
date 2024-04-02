#ifndef CENG_GLSL_SWITCH_STATEMENT_H
#define CENG_GLSL_SWITCH_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class SwitchStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif