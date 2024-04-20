#ifndef CENG_GLSL_AST_CASE_LABEL_H
#define CENG_GLSL_AST_CASE_LABEL_H

#include "IASTNode.h"

#include "Rvalue.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_CaseLabel : public IASTNode
		{
		public:

			Rvalue expression;

		public:

			AST_CaseLabel();

			AST_CaseLabel(const Rvalue& expression);

			~AST_CaseLabel() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};

	}
}

#endif