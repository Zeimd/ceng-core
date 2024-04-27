#ifndef CENG_GLSL_AST_INVARIANT_STATEMENT_H
#define CENG_GLSL_AST_INVARIANT_STATEMENT_H

#include "IASTNode.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_InvariantStatement : public IASTNode
		{
		public:

			std::vector<Ceng::StringUtf8> names;

		public:

			AST_InvariantStatement(std::vector<Ceng::StringUtf8>&& names);

			~AST_InvariantStatement() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif