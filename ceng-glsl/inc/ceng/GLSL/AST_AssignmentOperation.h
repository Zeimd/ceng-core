#ifndef CENG_GLSL_AST_ASSIGNMENT_OPERATION_H
#define CENG_GLSL_AST_ASSIGNMENT_OPERATION_H

#include "IASTNode.h"

#include "Lvalue.h"
#include "Rvalue.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_AssignmentOperation : public IASTNode
		{
		public:

			Lvalue lhs;
			Rvalue rhs;

		public:

			AST_AssignmentOperation(Lvalue& lhs, Rvalue& rhs);

			~AST_AssignmentOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};

	}
}

#endif