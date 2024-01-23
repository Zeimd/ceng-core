#ifndef CENG_GLSL_INONTERMINAL_H
#define CENG_GLSL_INONTERMINAL_H

#include "NonTerminalType.h"

namespace Ceng
{
	class INonTerminal
	{
	public:
		const NonTerminalType::value type;

		bool isInteger;
		bool isConst;

	protected:

		virtual ~INonTerminal()
		{

		}
	public:

		INonTerminal(NonTerminalType::value type)
			: type(type)
		{

		}

		virtual void Release() = 0;
	};
}

#endif