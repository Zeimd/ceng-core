#ifndef CENG_GLSL_FUNCTION_PROTOTYPE_H
#define CENG_GLSL_FUNCTION_PROTOTYPE_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class FunctionDeclarator;

	class FunctionPrototype : public INonTerminal
	{
	public:

		std::shared_ptr<FunctionDeclarator> decl;

	public:

		~FunctionPrototype() override;

		void Release() override;

		FunctionPrototype(std::shared_ptr<FunctionDeclarator>& decl);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif