#ifndef CENG_GLSL_AST_CONDITIONAL_OPERATION_H
#define CENG_GLSL_AST_CONDITIONAL_OPERATION_H

#include "IASTNode.h"

#include "Lvalue.h"
#include "Rvalue.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_ConditionalOperation : public IASTNode
		{
		public:
			Lvalue lhs;

			Rvalue a;
			Rvalue b;
			Rvalue c;

		public:

			AST_ConditionalOperation(Lvalue& lhs, Rvalue& a, Rvalue& b, Rvalue& c);

			~AST_ConditionalOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif