#ifndef CENG_GLSL_SIMPLE_STATEMENT_H
#define CENG_GLSL_SIMPLE_STATEMENT_H

#include "INonTerminal.h"

namespace Ceng
{
	namespace StatementType
	{
		enum value
		{
			declaration,
			expression,
			selection,
			switch_statement,
			case_label,
			iteration,
			jump,
		};
	}

	class DeclarationStatement;
	class ExpressionStatement;
	class SelectionStatement;
	class SwitchStatement;
	class CaseLabel;
	class IterationStatement;
	class JumpStatement;

	class SimpleStatement : public INonTerminal
	{
	public:

		StatementType::value statementType;

		std::shared_ptr<DeclarationStatement> declaration;
		std::shared_ptr<ExpressionStatement> expression;
		std::shared_ptr<SelectionStatement> selection;
		std::shared_ptr<SwitchStatement> switchStatement;
		std::shared_ptr<CaseLabel> caseLabel;
		std::shared_ptr<IterationStatement> iteration;
		std::shared_ptr<JumpStatement> jump;

	public:

		~SimpleStatement() override;

		void Release() override;

		SimpleStatement(std::shared_ptr<DeclarationStatement>& declaration);
		SimpleStatement(std::shared_ptr<ExpressionStatement>& expression);
		SimpleStatement(std::shared_ptr<SelectionStatement>& selection);
		SimpleStatement(std::shared_ptr<SwitchStatement>& switchStatement);
		SimpleStatement(std::shared_ptr<CaseLabel>& caseLabel);
		SimpleStatement(std::shared_ptr<IterationStatement>& iteration);
		SimpleStatement(std::shared_ptr<JumpStatement>& jump);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;
	};
}

#endif