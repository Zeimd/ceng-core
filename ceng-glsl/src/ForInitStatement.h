#ifndef CENG_GLSL_FOR_INIT_STATEMENT_H
#define CENG_GLSL_FOR_INIT_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class ForInitStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif