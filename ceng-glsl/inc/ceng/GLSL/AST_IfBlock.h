#ifndef CENG_GLSL_AST_IF_BLOCK_H
#define CENG_GLSL_AST_IF_BLOCK_H

#include "IASTNode.h"

#include "Rvalue.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_IfBlock : public IASTNode
		{
		public:

			Rvalue condition;

		public:

			AST_IfBlock(const Rvalue& condition);

			~AST_IfBlock() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}


#endif