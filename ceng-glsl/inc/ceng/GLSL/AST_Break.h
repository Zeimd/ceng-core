#ifndef CENG_GLSL_AST_BREAK_H
#define CENG_GLSL_AST_BREAK_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_Break : public IASTNode
		{
		public:

			AST_Break();

			~AST_Break() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif