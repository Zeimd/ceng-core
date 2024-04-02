#ifndef CENG_GLSL_DECLARATION_H
#define CENG_GLSL_DECLARATION_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	namespace DeclarationType
	{
		enum value
		{
			function_prototype,
			init_list,
		};
	}

	class InitDeclaratorList;
	class FunctionPrototype;

	class Declaration : public INonTerminal
	{
	public:

		DeclarationType::value type;

		std::shared_ptr<FunctionPrototype> prototype;

		std::shared_ptr<InitDeclaratorList> declList;

	public:

		void Release() override;

		Declaration(std::shared_ptr<FunctionPrototype>& prototype);

		Declaration(std::shared_ptr<InitDeclaratorList>& declList);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

	};
}

#endif