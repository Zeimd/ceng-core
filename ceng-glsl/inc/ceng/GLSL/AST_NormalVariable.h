#ifndef CENG_GLSL_AST_NORMAL_VARIABLE_H
#define CENG_GLSL_AST_NORMAL_VARIABLE_H

#include "IASTNode.h"

#include "SimpleDeclaration.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_NormalVariable : public IASTNode
		{
		public:

			SimpleDeclaration declaration;

		public:

			AST_NormalVariable(const SimpleDeclaration& declaration);

			~AST_NormalVariable() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif