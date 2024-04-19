#ifndef CENG_GLSL_AST_SCOPE_H
#define CENG_GLSL_AST_SCOPE_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_Scope : public IASTNode
		{
		public:

			AST_Scope();

			~AST_Scope() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif