#ifndef CENG_GLSL_AST_EXPRESSION_H
#define CENG_GLSL_AST_EXPRESSION_H

#include <variant>
#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	namespace GLSL
	{
		namespace AST_ExpressionType
		{
			enum value
			{
				int_literal,
				uint_literal,
				float_literal,
				bool_literal,

				identifier,
			};
		}

		using AST_ExpressionContent = std::variant<bool, Ceng::INT32, Ceng::UINT32, Ceng::FLOAT32, Ceng::StringUtf8>;

		class AST_Expression
		{
		public:

			AST_ExpressionType::value expressionType;

			AST_ExpressionContent value;

			AST_Expression(bool value);
			AST_Expression(Ceng::INT32 value);
			AST_Expression(Ceng::UINT32 value);
			AST_Expression(Ceng::FLOAT32 value);
			AST_Expression(Ceng::StringUtf8& name);

			~AST_Expression();

		};
	}
}

#endif