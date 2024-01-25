#include "FuncCallHeaderParams.h"

using namespace Ceng;

void FuncCallHeaderParams::Release()
{
	delete this;
}

FuncCallHeaderParams::FuncCallHeaderParams(std::shared_ptr<FunctionCallHeader>& header, std::shared_ptr<AssignmentExpression>& param)
	: INonTerminal(NonTerminalType::function_call_header_with_parameters), header(header)
{
	params.push_back(param);
}

void FuncCallHeaderParams::Append(std::shared_ptr<AssignmentExpression>& param)
{
	params.push_back(param);
}