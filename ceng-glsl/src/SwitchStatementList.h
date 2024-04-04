#ifndef CENG_GLSL_SWITCH_STATEMENT_LIST_H
#define CENG_GLSL_SWITCH_STATEMENT_LIST_H

#include "INonTerminal.h"

namespace Ceng
{
	class StatementList;

	class SwitchStatementList : public INonTerminal
	{
	public:

		std::shared_ptr<StatementList> list;

	public:

		~SwitchStatementList() override;

		void Release() override;

		SwitchStatementList(std::shared_ptr<StatementList>& list);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif