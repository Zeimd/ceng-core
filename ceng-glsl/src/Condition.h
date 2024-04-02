#ifndef CENG_GLSL_CONDITION_H
#define CENG_GLSL_CONDITION_H

#include "INonTerminal.h"

namespace Ceng
{
	class Condition : public INonTerminal
	{
	public:

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}


#endif