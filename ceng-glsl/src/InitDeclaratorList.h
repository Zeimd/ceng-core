#ifndef CENG_GLSL_INIT_DECL_LIST_H
#define CENG_GLSL_INIT_DECL_LIST_H

#include <vector>

#include "INonTerminal.h"
#include "SingleDeclaration.h"

namespace Ceng
{
	class InitDeclaratorList : public INonTerminal
	{
	public:

		std::vector<SingleDeclaration> list;

	public:

		void Release() override;

		InitDeclaratorList(const SingleDeclaration& decl);
	};
}

#endif