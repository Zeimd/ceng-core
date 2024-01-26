#include "FunctionCall.h"

using namespace Ceng;

void FunctionCall::Release()
{
	delete this;
}

FunctionCall::FunctionCall(std::shared_ptr<FunctionCallOrMethod>& call)
	: INonTerminal(NonTerminalType::function_call), call(call)
{

}

Ceng::StringUtf8 FunctionCall::ToString() const
{
	return call->ToString();
}