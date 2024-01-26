#ifndef CENG_GLSL_COMPOUND_STATEMENT_NO_NEW_SCOPE_H
#define CENG_GLSL_COMPOUND_STATEMENT_NO_NEW_SCOPE_H

#include "INonTerminal.h"

namespace Ceng
{
	class CompoundStatementNoNewScope : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif