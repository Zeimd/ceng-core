#ifndef CENG_GLSL_STATEMENT_LIST_H
#define CENG_GLSL_STATEMENT_LIST_H

#include <vector>
#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class Statement;

	class StatementList : public INonTerminal
	{
	public:

		std::vector<std::shared_ptr<Statement>> list;

	public:

		~StatementList() override;

		void Release() override;

		StatementList(std::shared_ptr<Statement>& statement);

		void Append(std::shared_ptr<Statement>& statement);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};

}

#endif