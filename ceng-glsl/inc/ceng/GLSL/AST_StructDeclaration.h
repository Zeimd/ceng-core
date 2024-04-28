#ifndef CENG_GLSL_AST_STRUCT_DECLARATION_H
#define CENG_GLSL_AST_STRUCT_DECLARATION_H

#include <ceng/datatypes/ce-string.h>

#include "IASTNode.h"

#include "StructMember.h"

namespace Ceng
{
	namespace GLSL
	{
		


		class AST_StructDeclaration : public IASTNode
		{
		public:

			Ceng::StringUtf8 name;

			std::vector<StructMember> members;

		public:

			AST_StructDeclaration(const Ceng::StringUtf8& name, std::vector<StructMember>&& members);

			~AST_StructDeclaration() override;

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const override;

			Ceng::StringUtf8 RhsToString(Ceng::UINT32 indentLevel) const override;
		};
	}
}

#endif