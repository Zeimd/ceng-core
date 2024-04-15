#ifndef CENG_GLSL_AST_FUNCTION_PROTOTYPE_H
#define CENG_GLSL_AST_FUNCTION_PROTOTYPE_H

#include <vector>

#include "IASTNode.h"

#include "AST_Datatype.h"
#include "FunctionParameter.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_FunctionPrototype : public IASTNode
		{
		public:
			AST_Datatype returnType;

			Ceng::StringUtf8 name;

			std::vector<FunctionParameter> params;

		public:

			AST_FunctionPrototype(const Ceng::StringUtf8& name);

			AST_FunctionPrototype(AST_Datatype& returnType, const Ceng::StringUtf8& name);

			AST_FunctionPrototype(AST_Datatype& returnType, const Ceng::StringUtf8& name, std::vector<FunctionParameter>&& params);

			~AST_FunctionPrototype() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;

		};
	}
}

#endif