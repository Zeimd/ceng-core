#ifndef CENG_GLSL_SELECTION_REST_STATEMENT_H
#define CENG_GLSL_SELECTION_REST_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	class Statement;

	class SelectionRestStatement : public INonTerminal
	{
	public:

		std::shared_ptr<Statement> main;

		std::shared_ptr<Statement> elseBlock;

	public:

		~SelectionRestStatement() override;

		void Release() override;

		SelectionRestStatement(std::shared_ptr<Statement>& main);

		SelectionRestStatement(std::shared_ptr<Statement>& main, std::shared_ptr<Statement>& elseBlock);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif