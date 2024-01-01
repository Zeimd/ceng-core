#ifndef CENG_GLSL_INIT_DECL_LIST_H
#define CENG_GLSL_INIT_DECL_LIST_H

#include <vector>
#include "single-declaration.h"

namespace Ceng
{
	class InitDeclaratorList
	{
	public:

		std::vector<SingleDeclaration> list;

	public:

		InitDeclaratorList(const SingleDeclaration& decl);
	};
}

#endif