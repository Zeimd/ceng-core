#ifndef CENG_GLSL_STRUCT_DECLARATION_H
#define CENG_GLSL_STRUCT_DECLARATION_H

#include "INonTerminal.h"

#include "TypeQualifier.h"
#include "TypeSpecifier.h"

namespace Ceng
{
	class StructDeclaratorList;


	class StructDeclaration : public INonTerminal
	{
	public:
		TypeQualifier typeQ;
		TypeSpecifier typeSpec;

		std::shared_ptr<StructDeclaratorList> list;

	public:

		~StructDeclaration() override;

		StructDeclaration(TypeSpecifier& typeSpec, std::shared_ptr<StructDeclaratorList>& list);
		StructDeclaration(TypeQualifier& typeQ, TypeSpecifier& typeSpec, std::shared_ptr<StructDeclaratorList>& list);

		void Release() override;

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

	};
}

#endif // !CENG_GLSL_STRUCT_DECLARATION_H
