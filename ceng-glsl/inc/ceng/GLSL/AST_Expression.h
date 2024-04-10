#ifndef CENG_GLSL_AST_EXPRESSION_H
#define CENG_GLSL_AST_EXPRESSION_H

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

				variable,
			};
		}

		union AST_ExpressionContent
		{
			bool boolValue;
						
			Ceng::INT32 intValue;
			Ceng::UINT32 uintValue;
			Ceng::FLOAT32 floatValue;

			Ceng::StringUtf8 name;
		};

		class AST_Expression
		{
		public:

			AST_ExpressionType::value expressionType;

			AST_ExpressionContent value;

		};
	}
}

#endif