#ifndef CENG_GLSL_AST_BINARYOPERATOR_H
#define CENG_GLSL_AST_BINARYOPERATOR_H

namespace Ceng
{
	namespace GLSL
	{
		namespace BinaryOperator
		{
			enum value
			{

				add,
				sub,

				mul,
				div,
				mod,

				left_shift,
				right_shift,

				bitwise_and,
				bitwise_or,
				bitwise_xor,

				less,
				less_eq,

				greater,
				greater_eq,

				equal,
				not_equal,

				logical_and,
				logical_or,
				logical_xor,

			};
			const char* ToString(BinaryOperator::value operation);
		}
	}
}

#endif