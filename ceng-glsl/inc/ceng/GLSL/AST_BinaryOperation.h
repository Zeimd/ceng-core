#ifndef CENG_GLSL_AST_BINARY_OPERATION_H
#define CENG_GLSL_AST_BINARY_OPERATION_H

#include "IASTNode.h"

#include "Lvalue.h"
#include "AST_Expression.h"

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

				field_select,

				logical_and,
				logical_or,
				logical_xor,
			};

			const char* ToString(BinaryOperator::value operation);
		}

		class AST_BinaryOperation : public IASTNode
		{
		public:
			Lvalue lhs;

			AST_Expression a;

			BinaryOperator::value operation;

			AST_Expression b;

		public:

			AST_BinaryOperation(Lvalue& lhs, AST_Expression& a, BinaryOperator::value operation, AST_Expression& b);

			~AST_BinaryOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;
		};

	}
}

#endif