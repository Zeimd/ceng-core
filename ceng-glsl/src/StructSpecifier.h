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

		Ceng::StringUtf8 name;
		std::shared_ptr<StructDeclarationList> list;

	public:

		~StructSpecifier() override;

		StructSpecifier(const Ceng::StringUtf8& name, std::shared_ptr<StructDeclarationList>& list);

		void Release() override;

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif