#include "FunctionCall.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void FunctionCall::Release()
{
	delete this;
}

FunctionCall::FunctionCall(std::shared_ptr<FunctionCallOrMethod>& call)
	: INonTerminal(NonTerminalType::function_call), call(call)
{

}

Ceng::StringUtf8 FunctionCall::ToString(unsigned int indentLevel) const
{
	return call->ToString(indentLevel);
}

void FunctionCall::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FunctionCall(*this);
}