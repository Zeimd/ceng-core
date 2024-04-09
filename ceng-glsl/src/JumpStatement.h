#ifndef CENG_GLSL_JUMP_STATEMENT_H
#define CENG_GLSL_JUMP_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	namespace JumpType
	{
		enum value
		{
			breakStatement,
			continueStatement,
			discard,
			returnStatement,
		};
	}

	class Expression;

	class JumpStatement : public INonTerminal
	{
	public:

		JumpType::value jumpType;

		std::shared_ptr<Expression> returnExpression;

	public:

		~JumpStatement() override;

		void Release() override;

		JumpStatement(JumpType::value jumpType);

		JumpStatement(std::shared_ptr<Expression>& returnExpression);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif // !CENG_GLSL_JUMP_STATEMENT_H
