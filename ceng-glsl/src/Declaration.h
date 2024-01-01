#ifndef CENG_GLSL_DECLARATION_H
#define CENG_GLSL_DECLARATION_H

#include "InitDeclaratorList.h"
#include "TypeQualifier.h"

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