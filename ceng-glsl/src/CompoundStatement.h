#ifndef CENG_GLSL_COMPOUND_STATEMENT_H
#define CENG_GLSL_COMPOUND_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class CompoundStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif