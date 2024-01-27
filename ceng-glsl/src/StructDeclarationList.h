#ifndef CENG_GLSL_STRUCT_DECLARATION_LIST
#define CENG_GLSL_STRUCT_DECLARATION_LIST

#include <vector>
#include "INonTerminal.h"

namespace Ceng
{
	class StructDeclaration;

	class StructDeclarationList : public INonTerminal
	{
	public:

		std::vector<std::shared_ptr<StructDeclaration>> list;

	public:

		StructDeclarationList(std::shared_ptr<StructDeclaration>& decl);

		void Append(std::shared_ptr<StructDeclaration>& decl);

		void Release() override;

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif // !CENG_GLSL_STRUCT_DECLARATION_LIST