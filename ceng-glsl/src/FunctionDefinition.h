#ifndef CENG_GLSL_FUNCTION_DEFINITION_H
#define CENG_GLSL_FUNCTION_DEFINITION_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class FunctionPrototype;
	class CompoundStatementNoNewScope;

	class FunctionDefinition : public INonTerminal
	{
	public:

		std::shared_ptr<FunctionPrototype> prototype;
		std::shared_ptr<CompoundStatementNoNewScope> body;

	public:

		~FunctionDefinition() override;

		void Release() override;

		FunctionDefinition(std::shared_ptr<FunctionPrototype>& prototype,
			std::shared_ptr<CompoundStatementNoNewScope>& body);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}


#endif