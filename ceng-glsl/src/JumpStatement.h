#ifndef CENG_GLSL_JUMP_STATEMENT_H
#define CENG_GLSL_JUMP_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class JumpStatement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif // !CENG_GLSL_JUMP_STATEMENT_H
