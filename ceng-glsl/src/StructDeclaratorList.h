#ifndef CENG_GLSL_STRUCT_DECLARATOR_LIST_H
#define CENG_GLSL_STRUCT_DECLARATOR_LIST_H

#include <vector>
#include "INonTerminal.h"

namespace Ceng
{
	class StructDeclarator;

	class StructDeclaratorList : public INonTerminal
	{
	public:
		std::vector <std::shared_ptr<StructDeclarator>> list;

	public:

		~StructDeclaratorList() override;

		void Release() override;

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		StructDeclaratorList(std::shared_ptr<StructDeclarator>& decl);

		void Append(std::shared_ptr<StructDeclarator>& decl);

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}


#endif // !CENG_GLSL_STRUCT_DECLARATOR_LIST_H
