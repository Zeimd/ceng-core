#ifndef CENG_GLSL_AST_SWITCH_BLOCK_H
#define CENG_GLSL_AST_SWITCH_BLOCK_H

#include "IASTNode.h"

#include "Rvalue.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_SwitchBlock : public IASTNode
		{
		public:

			Rvalue input;

		public:

			AST_SwitchBlock(const Rvalue& input);

			~AST_SwitchBlock() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif