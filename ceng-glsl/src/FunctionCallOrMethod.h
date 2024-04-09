#ifndef CENG_GLSL_FUNCTION_CALL_OR_METHOD_H
#define CENG_GLSL_FUNCTION_CALL_OR_METHOD_H

#include <memory>

#include "INonTerminal.h"
#include "FunctionCallGeneric.h"
#include "PostfixExpression.h"

namespace Ceng
{
	class FunctionCallOrMethod : public INonTerminal
	{
	public:
		std::shared_ptr<PostfixExpression> root;

		std::shared_ptr<FunctionCallGeneric> func;

		bool method;

	public:

		void Release() override;

		FunctionCallOrMethod(std::shared_ptr<FunctionCallGeneric>& func);

		FunctionCallOrMethod(std::shared_ptr<PostfixExpression>& root, std::shared_ptr<FunctionCallGeneric>& func);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;

		void AcceptVisitor(NonTerminalVisitor& visitor) override;

	};
}

#endif