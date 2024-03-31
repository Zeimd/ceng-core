#ifndef CENG_GLSL_EXPRESSION_STATEMENT_H
#define CENG_GLSL_EXPRESSION_STATEMENT_H

#include <memory>

#include "INonTerminal.h"

namespace Ceng
{
	class Expression;

	class ExpressionStatement : public INonTerminal
	{
	public:
		std::shared_ptr<Expression> ex;
	public:

		~ExpressionStatement() override;

		void Release() override;

		ExpressionStatement(std::shared_ptr<Expression>& ex);		

		Ceng::StringUtf8 ToString() const override;
	};
}

#endif