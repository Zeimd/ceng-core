#ifndef CENG_GLSL_STATEMENT_LIST_H
#define CENG_GLSL_STATEMENT_LIST_H

#include "INonTerminal.h"

namespace Ceng
{
	class StatementList : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};

}

#endif