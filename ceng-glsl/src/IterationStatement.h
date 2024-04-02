#ifndef CENG_GLSL_ITERATION_STATEMENT_H
#define CENG_GLSL_ITERATION_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class IterationStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif // !CENG_GLSL_ITERATION_STATEMENT_H
