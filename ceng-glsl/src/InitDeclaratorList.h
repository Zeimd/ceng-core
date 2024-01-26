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

		std::vector<std::shared_ptr<SingleDeclaration>> list;

	public:

		void Release() override;

		InitDeclaratorList(std::shared_ptr<SingleDeclaration>& decl);

		void Append(std::shared_ptr<SingleDeclaration>& decl);
	};
}

#endif