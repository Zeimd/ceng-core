#ifndef CENG_GLSL_AST_RETURN_H
#define CENG_GLSL_AST_RETURN_H

#include "IASTNode.h"

#include "AST_Expression.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_Return : public IASTNode
		{
		public:

			bool empty;
			AST_Expression expression;

		public:

			AST_Return();
			AST_Return(AST_Expression& expression);

			~AST_Return() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif