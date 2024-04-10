#ifndef CENG_GLSL_AST_UNARY_OPERATION_H
#define CENG_GLSL_AST_UNARY_OPERATION_H

#include "IASTNode.h"
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
		}

		class AST_UnaryOperation : public IASTNode
		{
		public:

			Ceng::StringUtf8 lhs;

			UnaryOperation::value operation;

			AST_Expression input;

		public:

			~AST_UnaryOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif