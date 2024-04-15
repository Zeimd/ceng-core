#ifndef CENG_GLSL_AST_BINARY_OPERATION_H
#define CENG_GLSL_AST_BINARY_OPERATION_H

#include "IASTNode.h"

#include "Lvalue.h"
#include "Rvalue.h"

#include "AST_BinaryOperator.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_BinaryOperation : public IASTNode
		{
		public:
			Lvalue lhs;

			Rvalue a;

			BinaryOperator::value operation;

			Rvalue b;

		public:

			AST_BinaryOperation(Lvalue& lhs, Rvalue& a, BinaryOperator::value operation, Rvalue& b);

			~AST_BinaryOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;
		};

	}
}

#endif