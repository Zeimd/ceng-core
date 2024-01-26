#ifndef CENG_GLSL_SWITCH_STATEMENT_LIST_H
#define CENG_GLSL_SWITCH_STATEMENT_LIST_H

#include "INonTerminal.h"

namespace Ceng
{
	class SwitchStatementList : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif