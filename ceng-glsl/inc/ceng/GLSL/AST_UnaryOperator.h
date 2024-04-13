#ifndef CENG_GLSL_AST_UNARY_OPERATOR_H
#define CENG_GLSL_AST_UNARY_OPERATOR_H

namespace Ceng
{
	namespace GLSL
	{
		namespace UnaryOperation
		{
			enum value
			{
				// !
				logical_not,

				// ~
				bitwise_not,

				// -
				negation,
			};

			const char* ToString(UnaryOperation::value operation);
		}
	}
}


#endif