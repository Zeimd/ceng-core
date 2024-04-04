#ifndef CENG_GLSL_SWITCH_STATEMENT_H
#define CENG_GLSL_SWITCH_STATEMENT_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class Expression;
	class SwitchStatementList;

	class SwitchStatement : public INonTerminal
	{
	public:

		std::shared_ptr<Expression> expression;

		std::shared_ptr<SwitchStatementList> list;

	public:

		~SwitchStatement() override;

		void Release() override;

		SwitchStatement(std::shared_ptr<Expression>& expression);

		SwitchStatement(std::shared_ptr<Expression>& expression, std::shared_ptr<SwitchStatementList>& list);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif