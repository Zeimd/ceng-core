#ifndef CENG_GLSL_AST_UNARY_OPERATION_H
#define CENG_GLSL_AST_UNARY_OPERATION_H

#include "IASTNode.h"
#include "Lvalue.h"
#include "AST_Expression.h"

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

		class AST_UnaryOperation : public IASTNode
		{
		public:

			Lvalue lhs;

			UnaryOperation::value operation;

			AST_Expression input;

		public:

			AST_UnaryOperation(Lvalue& lhs, UnaryOperation::value operation, AST_Expression& input);

			~AST_UnaryOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif