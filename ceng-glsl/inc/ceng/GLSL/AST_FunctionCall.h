#ifndef CENG_GLSL_AST_FUNCTION_CALL_H
#define CENG_GLSL_AST_FUNCTION_CALL_H

#include <vector>
#include <memory>

#include "IASTNode.h"

#include "Lvalue.h"
#include "Rvalue.h"

namespace Ceng
{
	struct SymbolLink;

	namespace GLSL
	{
		class AST_FunctionCall : public IASTNode
		{
		public:
			
			std::shared_ptr<SymbolLink> function;

			Lvalue lhs;

			std::vector<Rvalue> params;

		public:

			AST_FunctionCall(const Lvalue& lhs, std::shared_ptr<SymbolLink>& function, std::vector<Rvalue>&& params);

			~AST_FunctionCall() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;

		};

	}
}

#endif