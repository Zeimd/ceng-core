#ifndef CENG_GLSL_COMPOUND_STATEMENT_NO_NEW_SCOPE_H
#define CENG_GLSL_COMPOUND_STATEMENT_NO_NEW_SCOPE_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class StatementList;
	class CompoundStatement;

	class CompoundStatementNoNewScope : public INonTerminal
	{
	public:

		std::shared_ptr<StatementList> list;

	public:

		~CompoundStatementNoNewScope() override;

		void Release() override;

		CompoundStatementNoNewScope();
		CompoundStatementNoNewScope(std::shared_ptr<StatementList>& list);
		CompoundStatementNoNewScope(std::shared_ptr<CompoundStatement>& compound);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif