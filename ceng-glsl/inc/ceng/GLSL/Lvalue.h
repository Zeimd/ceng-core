#ifndef CENG_GLSL_AST_LVALUE_H
#define CENG_GLSL_AST_LVALUE_H

#include <ceng/datatypes/ce-string.h>

#include "ArrayIndex.h"

namespace Ceng
{
	namespace GLSL
	{
		class Lvalue
		{
		public:

			Ceng::StringUtf8 variable;

			// variable[variableIndex]
			ArrayIndex variableIndex;

			// Indicates variable.memberName
			bool memberAccess;

			Ceng::StringUtf8 memberName;

			// Indicates memberName[memberIndex]
			ArrayIndex memberIndex;

		public:

			Lvalue(const Ceng::StringUtf8& variable, ArrayIndex& variableIndex,
				bool memberAccess, const Ceng::StringUtf8& memberName,
				ArrayIndex& memberIndex);
				
			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;
		};
	}
}

#endif