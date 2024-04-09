#include "FunctionCallOrMethod.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void FunctionCallOrMethod::Release()
{
	delete this;
}

FunctionCallOrMethod::FunctionCallOrMethod(std::shared_ptr<FunctionCallGeneric>& func)
	: INonTerminal(NonTerminalType::function_call_or_method), root(nullptr), func(func), method(false)
{

}

FunctionCallOrMethod::FunctionCallOrMethod(std::shared_ptr<PostfixExpression>& root, std::shared_ptr<FunctionCallGeneric>& func)
	: INonTerminal(NonTerminalType::function_call_or_method), root(root), func(func), method(true)
{

}

Ceng::StringUtf8 FunctionCallOrMethod::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (method)
	{
		out += root->ToString(indentLevel);
		out += '.';
	}

	out += func->ToString(indentLevel);

	return out;
}

void FunctionCallOrMethod::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FunctionCallOrMethod(*this);
}