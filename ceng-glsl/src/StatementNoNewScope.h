#ifndef CENG_GLSL_STATEMENT_NO_NEW_SCOPE_H
#define CENG_GLSL_STATEMENT_NO_NEW_SCOPE_H

#include "INonTerminal.h"

#include "StatementCategory.h"

namespace Ceng
{
	class SimpleStatement;
	class CompoundStatement;
	class CompoundStatementNoNewScope;

	class StatementNoNewScope : public INonTerminal
	{
	public:

		StatementCategory::value category;

		std::shared_ptr<SimpleStatement> simpleStatement;
		std::shared_ptr<CompoundStatementNoNewScope> compoundStatement;

	public:

		~StatementNoNewScope() override;

		void Release() override;

		StatementNoNewScope(std::shared_ptr<SimpleStatement>& simpleStatement);

		StatementNoNewScope(std::shared_ptr<CompoundStatement>& compoundStatement);

		StatementNoNewScope(std::shared_ptr<CompoundStatementNoNewScope>& compoundStatement);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}


#endif // !CENG_GLSL_STATEMENT_NO_NEW_SCOPE_H
