#ifndef CENG_GLSL_DECLARATION_H
#define CENG_GLSL_DECLARATION_H

#include "init-decl-list.h"
#include "type-qualifier.h"

namespace Ceng
{
	class Declaration
	{
	public:

		//FunctionPrototype funcProto;

		InitDeclaratorList declList;

	public:

		Declaration(const InitDeclaratorList& declList);

	};
}

#endif