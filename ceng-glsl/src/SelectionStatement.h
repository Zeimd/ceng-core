#ifndef CENG_GLSL_SELECTION_STATEMENT_H
#define CENG_GLSL_SELECTION_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class SelectionStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif