#ifndef CENG_GLSL_AST_WHILE_LOOP_H
#define CENG_GLSL_AST_WHILE_LOOP_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_WhileLoop : public IASTNode
		{
		public:


		public:

			AST_WhileLoop();

			~AST_WhileLoop() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};


	}
}

#endif