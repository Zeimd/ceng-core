#ifndef CENG_GLSL_AST_RETURN_H
#define CENG_GLSL_AST_RETURN_H

#include "IASTNode.h"

#include "AST_Expression.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_ReturnStatement : public IASTNode
		{
		public:

			bool empty;
			AST_Expression expression;

		public:

			AST_ReturnStatement();
			AST_ReturnStatement(AST_Expression& expression);

			~AST_ReturnStatement() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif