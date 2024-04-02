#ifndef CENG_GLSL_INONTERMINAL_H
#define CENG_GLSL_INONTERMINAL_H

#include <ceng/datatypes/ce-string.h>

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

		virtual Ceng::StringUtf8 ToString(unsigned int indentLevel) const
		{
			return "";
		}

		static Ceng::StringUtf8 GetIndent(unsigned int indentLevel)
		{
			return Ceng::StringUtf8(' ', 4 * indentLevel );
		}
	};
}

#endif