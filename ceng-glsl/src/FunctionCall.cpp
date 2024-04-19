#include "FunctionCall.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void FunctionCall::Release()
{
	delete this;
}

FunctionCall::FunctionCall(std::shared_ptr<FunctionCallOrMethod>& call, std::vector<SymbolLink>&& functions)
	: INonTerminal(NonTerminalType::function_call), call(call), functions(std::move(functions))
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