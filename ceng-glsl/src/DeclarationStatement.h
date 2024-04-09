#ifndef CENG_GLSL_DECLARATION_STATEMENT_H
#define CENG_GLSL_DECLARATION_STATEMENT_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class Declaration;

	class DeclarationStatement : public INonTerminal
	{
	public:

		std::shared_ptr<Declaration> declaration;

	public:

		~DeclarationStatement() override;

		void Release() override;

		DeclarationStatement(std::shared_ptr<Declaration>& declaration);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif