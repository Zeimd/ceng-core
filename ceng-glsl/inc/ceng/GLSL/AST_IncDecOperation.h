#ifndef CENG_GLSL_AST_INCDEC_OPERATION_H
#define CENG_GLSL_AST_INCDEC_OPERATION_H

#include "IASTNode.h"
#include "Lvalue.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_IncDecOperation : public IASTNode
		{
		public:

			Lvalue target;

			// If true, use -- instead of ++
			bool dec;

		public:

			AST_IncDecOperation(Lvalue& target, bool dec);

			~AST_IncDecOperation() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}


#endif
