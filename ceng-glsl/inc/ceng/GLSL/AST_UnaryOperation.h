#ifndef CENG_GLSL_AST_UNARY_OPERATION_H
#define CENG_GLSL_AST_UNARY_OPERATION_H

#include "IASTNode.h"
#include "Lvalue.h"
#include "Rvalue.h"

#include "AST_UnaryOperator.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_UnaryOperation : public IASTNode
		{
		public:

			Lvalue lhs;

			UnaryOperation::value operation;

			Rvalue input;

		public:

			AST_UnaryOperation(Lvalue& lhs, UnaryOperation::value operation, Rvalue& input);

			~AST_UnaryOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif