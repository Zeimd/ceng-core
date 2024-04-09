#ifndef CENG_GLSL_ITERATION_STATEMENT_H
#define CENG_GLSL_ITERATION_STATEMENT_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	namespace IterationType
	{
		enum value
		{
			whileLoop,
			doLoop,
			forLoop,
		};
	}

	class Condition;
	class StatementNoNewScope;
	class Statement;
	class Expression;
	class ForInitStatement;
	class ForRestStatement;

	class IterationStatement : public INonTerminal
	{
	public:

		IterationType::value iterationType;

		std::shared_ptr<Condition> whileCondition;

		std::shared_ptr<StatementNoNewScope> forWhileBody;

		std::shared_ptr<Statement> doBody;

		std::shared_ptr<Expression> doWhileCondition;

		std::shared_ptr<ForInitStatement> forInit;
		std::shared_ptr<ForRestStatement> forRest;

	public:

		~IterationStatement() override;

		void Release() override;

		// While loop
		IterationStatement(std::shared_ptr<Condition>& whileCondition, std::shared_ptr<StatementNoNewScope>& forWhileBody);

		// Do-while loop
		IterationStatement(std::shared_ptr<Statement>& doBody, std::shared_ptr<Expression>& doWhileCondition);

		// For loop
		IterationStatement(std::shared_ptr<ForInitStatement>& forInit, std::shared_ptr<ForRestStatement>& forRest,
			std::shared_ptr<StatementNoNewScope>& forWhileBody);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif // !CENG_GLSL_ITERATION_STATEMENT_H
