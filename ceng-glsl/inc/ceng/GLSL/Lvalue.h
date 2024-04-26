#ifndef CENG_GLSL_AST_LVALUE_H
#define CENG_GLSL_AST_LVALUE_H

#include <ceng/datatypes/ce-string.h>

#include "SimpleDeclaration.h"

#include "ArrayIndex.h"
#include "VariableExpression.h"

namespace Ceng
{
	namespace GLSL
	{
		class Rvalue;

		enum class LvalueType
		{
			invalid,
			expression,
			declaration
		};

		class Lvalue
		{
		public:

			using ContentType = std::variant<bool, VariableExpression, SimpleDeclaration>;

			ContentType value;

			LvalueType valueType;

		public:

			Lvalue();

			Lvalue(const Ceng::StringUtf8& variable);

			Lvalue(const Ceng::StringUtf8& variable, ArrayIndex& index);

			Lvalue(const SimpleDeclaration& declaration);

			Lvalue(const VariableExpression& expression);

			Lvalue(VariableExpression&& expression);
				
			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;

			bool operator == (const Rvalue& other) const;

			bool operator != (const Rvalue& other) const;

			VariableExpression ToExpression() const;

			bool IsValid() const;
		};
	}
}

#endif