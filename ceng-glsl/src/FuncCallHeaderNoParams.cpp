#include "FuncCallHeaderNoParams.h"

using namespace Ceng;

void FuncCallHeaderNoParams::Release()
{
	delete this;
}

FuncCallHeaderNoParams::FuncCallHeaderNoParams(std::shared_ptr<FunctionCallHeader>& header)
	: INonTerminal(NonTerminalType::function_call_header_no_parameters), header(header)
{

}