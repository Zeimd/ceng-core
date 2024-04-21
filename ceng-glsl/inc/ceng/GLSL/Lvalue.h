#ifndef CENG_GLSL_AST_LVALUE_H
#define CENG_GLSL_AST_LVALUE_H

#include <ceng/datatypes/ce-string.h>

#include "ArrayIndex.h"
#include "VariableExpression.h"

namespace Ceng
{
	namespace GLSL
	{
		class Rvalue;

		class Lvalue
		{
		public:

			VariableExpression expression;

			bool valid;

		public:

			Lvalue();

			Lvalue(const Ceng::StringUtf8& variable);

			Lvalue(const Ceng::StringUtf8& variable, ArrayIndex& index);

			Lvalue(const VariableExpression& expression);

			Lvalue(VariableExpression&& expression);
				
			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;

			bool operator == (const Rvalue& other) const;

			bool operator != (const Rvalue& other) const;
		};
	}
}

#endif