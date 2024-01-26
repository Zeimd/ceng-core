#ifndef CENG_GLSL_STATEMENT_H
#define CENG_GLSL_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class Statement : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif