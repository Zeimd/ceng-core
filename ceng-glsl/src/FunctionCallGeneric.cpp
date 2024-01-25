#include "FunctionCallGeneric.h"

using namespace Ceng;

void FunctionCallGeneric::Release()
{
	delete this;
}

FunctionCallGeneric::FunctionCallGeneric(std::shared_ptr<FuncCallHeaderParams>& withParams)
	: INonTerminal(NonTerminalType::function_call_generic), withParams(withParams), noParams(nullptr)
{

}

FunctionCallGeneric::FunctionCallGeneric(std::shared_ptr<FuncCallHeaderNoParams>& noParams)
	: INonTerminal(NonTerminalType::function_call_generic), withParams(nullptr), noParams(noParams)
{

}