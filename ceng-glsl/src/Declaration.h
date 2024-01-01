#ifndef CENG_GLSL_DECLARATION_H
#define CENG_GLSL_DECLARATION_H

#include "INonTerminal.h"
#include "InitDeclaratorList.h"
#include "TypeQualifier.h"

namespace Ceng
{
	class Declaration : public INonTerminal
	{
	public:

		//FunctionPrototype funcProto;

		InitDeclaratorList declList;

	public:

		void Release() override;

		Declaration(const InitDeclaratorList& declList);

	};
}

#endif