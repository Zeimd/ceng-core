#ifndef CENG_GLSL_COMPOUND_STATEMENT_H
#define CENG_GLSL_COMPOUND_STATEMENT_H

#include <vector>

#include "INonTerminal.h"

namespace Ceng
{
	class StatementList;

	class CompoundStatement : public INonTerminal
	{
	public:

		std::shared_ptr<StatementList> list;

	public:

		~CompoundStatement() override;

		void Release() override;

		CompoundStatement();
		CompoundStatement(std::shared_ptr<StatementList>& list);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif