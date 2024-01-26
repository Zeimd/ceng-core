#ifndef CENG_GLSL_SIMPLE_STATEMENT_H
#define CENG_GLSL_SIMPLE_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class SimpleStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif