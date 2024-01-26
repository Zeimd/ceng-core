#ifndef CENG_GLSL_EXPRESSION_STATEMENT_H
#define CENG_GLSL_EXPRESSION_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class ExpressionStatement : public INonTerminal
	{
	public:


		Ceng::StringUtf8 ToString() const override;
	};
}

#endif