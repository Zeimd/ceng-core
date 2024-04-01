#ifndef CENG_GLSL_STATEMENT_H
#define CENG_GLSL_STATEMENT_H

#include "INonTerminal.h"

#include "StatementCategory.h"

namespace Ceng
{
	class SimpleStatement;
	class CompoundStatement;

	class Statement : public INonTerminal
	{
	public:

		StatementCategory::value category;

		std::shared_ptr<SimpleStatement> simpleStatement;
		std::shared_ptr<CompoundStatement> compoundStatement;

	public:

		~Statement() override;

		void Release() override;

		Statement(std::shared_ptr<SimpleStatement>& simpleStatement);

		Statement(std::shared_ptr<CompoundStatement>& compoundStatement);

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif