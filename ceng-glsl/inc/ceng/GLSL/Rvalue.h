#ifndef CENG_GLSL_AST_EXPRESSION_H
#define CENG_GLSL_AST_EXPRESSION_H

#include <variant>
#include <ceng/datatypes/ce-string.h>

#include "AST_UnaryOperator.h"
#include "VariableExpression.h"
#include "Lvalue.h"

namespace Ceng
{
	namespace GLSL
	{
		enum class RvalueType
		{
			unused,
			int_literal,
			uint_literal,
			float_literal,
			bool_literal,

			variable,
		};
		

		using RvalueData = std::variant<bool, Ceng::INT32, Ceng::UINT32, Ceng::FLOAT32, VariableExpression>;

		class Rvalue
		{
		public:

			RvalueType valueType;

			RvalueData value;

			Rvalue();
			Rvalue(bool value);
			Rvalue(Ceng::INT32 value);
			Rvalue(Ceng::UINT32 value);
			Rvalue(Ceng::FLOAT32 value);
			Rvalue(Ceng::StringUtf8& name);
			Rvalue(std::vector<FieldExpression>&& expression);
			Rvalue(const Lvalue& lvalue);

			~Rvalue();

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;

			bool IsLiteral() const;

			
			void PreIncr();

			void PreDec();

			void UnaryOp(UnaryOperation::value op);

			Lvalue ToLvalue() const;

			bool IsZero() const;

		};
	}
}

#endif