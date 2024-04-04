#ifndef CENG_GLSL_FOR_REST_STATEMENT_H
#define CENG_GLSL_FOR_REST_STATEMENT_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class Condition;
	class Expression;

	class ForRestStatement : public INonTerminal
	{
	public:

		std::shared_ptr<Condition> condition;

		std::shared_ptr<Expression> expression;

	public:

		~ForRestStatement() override;

		void Release() override;

		ForRestStatement();

		ForRestStatement(std::shared_ptr<Condition>& condition);

		ForRestStatement(std::shared_ptr<Condition>& condition, std::shared_ptr<Expression>& expression);

		ForRestStatement(std::shared_ptr<Expression>& expression);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
	};
}

#endif // !CENG_GLSL_FOR_REST_STATEMENT_H
