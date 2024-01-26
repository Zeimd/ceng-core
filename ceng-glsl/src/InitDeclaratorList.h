#ifndef CENG_GLSL_INIT_DECL_LIST_H
#define CENG_GLSL_INIT_DECL_LIST_H

#include <memory>
#include <vector>

#include "INonTerminal.h"
#include "SingleDeclaration.h"

namespace Ceng
{
	class InitDeclaratorList : public INonTerminal
	{
	public:
		std::shared_ptr<FullySpecifiedType> fullType;
		bool invariant;

		std::vector<DeclarationData> list;

	public:

		void Release() override;

		InitDeclaratorList(std::shared_ptr<SingleDeclaration>& decl);

		void Append(std::shared_ptr<SingleDeclaration>& decl);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif