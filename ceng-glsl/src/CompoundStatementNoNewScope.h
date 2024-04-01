#ifndef CENG_GLSL_COMPOUND_STATEMENT_NO_NEW_SCOPE_H
#define CENG_GLSL_COMPOUND_STATEMENT_NO_NEW_SCOPE_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class StatementList;

	class CompoundStatementNoNewScope : public INonTerminal
	{
	public:

		std::shared_ptr<StatementList> list;

	public:

		~CompoundStatementNoNewScope() override;

		void Release() override;

		CompoundStatementNoNewScope(std::shared_ptr<StatementList>& list);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif