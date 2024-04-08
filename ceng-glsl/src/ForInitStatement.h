#ifndef CENG_GLSL_FOR_INIT_STATEMENT_H
#define CENG_GLSL_FOR_INIT_STATEMENT_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	namespace ForInitType
	{
		enum value
		{
			expression,
			declaration,
		};
	}

	class ExpressionStatement;
	class DeclarationStatement;

	class ForInitStatement : public INonTerminal
	{
	public:
		ForInitType::value initType;

		std::shared_ptr<ExpressionStatement> expression;
		std::shared_ptr<DeclarationStatement> declaration;

	public:

		~ForInitStatement() override;

		void Release() override;

		ForInitStatement(std::shared_ptr<ExpressionStatement>& expression);

		ForInitStatement(std::shared_ptr<DeclarationStatement>& declaration);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif