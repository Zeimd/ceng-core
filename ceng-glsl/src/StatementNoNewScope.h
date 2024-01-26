#ifndef CENG_GLSL_STATEMENT_NO_NEW_SCOPE_H
#define CENG_GLSL_STATEMENT_NO_NEW_SCOPE_H

#include "INonTerminal.h"

namespace Ceng
{
	class StatementNoNewScope : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif // !CENG_GLSL_STATEMENT_NO_NEW_SCOPE_H
