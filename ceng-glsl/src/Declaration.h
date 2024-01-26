#ifndef CENG_GLSL_DECLARATION_H
#define CENG_GLSL_DECLARATION_H

#include <memory>

#include "INonTerminal.h"
#include "InitDeclaratorList.h"
#include "TypeQualifier.h"

namespace Ceng
{
	class Declaration : public INonTerminal
	{
	public:

		//FunctionPrototype funcProto;

		std::shared_ptr<InitDeclaratorList> declList;

	public:

		void Release() override;

		Declaration(std::shared_ptr<InitDeclaratorList>& declList);

	};
}

#endif