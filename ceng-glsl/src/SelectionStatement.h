#ifndef CENG_GLSL_SELECTION_STATEMENT_H
#define CENG_GLSL_SELECTION_STATEMENT_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class Expression;
	class SelectionRestStatement;

	class SelectionStatement : public INonTerminal
	{
	public:

		std::shared_ptr<Expression> condition;

		std::shared_ptr<SelectionRestStatement> rest;

	public:

		~SelectionStatement() override;

		void Release() override;

		SelectionStatement(std::shared_ptr<Expression>& condition, std::shared_ptr<SelectionRestStatement>& rest);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif