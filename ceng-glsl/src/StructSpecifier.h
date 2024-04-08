#ifndef CENG_GLSL_STRUCT_SPECIFIER
#define CENG_GLSL_STRUCT_SPECIFIER

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class StructDeclarationList;

	class StructSpecifier : public INonTerminal
	{
	public:

		bool anonymous;

		Ceng::StringUtf8 name;
		std::shared_ptr<StructDeclarationList> list;

	public:

		~StructSpecifier() override;

		StructSpecifier(const Ceng::StringUtf8& name, std::shared_ptr<StructDeclarationList>& list);

		StructSpecifier(std::shared_ptr<StructDeclarationList>& list);

		void Release() override;

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif