#ifndef CENG_GLSL_CASE_LABEL_H
#define CENG_GLSL_CASE_LABEL_H

#include <memory>
#include "INonTerminal.h"

namespace Ceng
{
	class Expression;

	class CaseLabel : public INonTerminal
	{
	public:

		bool defaultCase;

		std::shared_ptr<Expression> expression;

	public:

		~CaseLabel() override;

		void Release() override;

		CaseLabel();

		CaseLabel(std::shared_ptr<Expression>& expression);


		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(AST_Visitor& visitor) override;
	};
}

#endif