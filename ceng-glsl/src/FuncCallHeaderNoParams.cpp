#include "FuncCallHeaderNoParams.h"

#include "AST_Visitor.h"

using namespace Ceng;

void FuncCallHeaderNoParams::Release()
{
	delete this;
}

FuncCallHeaderNoParams::FuncCallHeaderNoParams(std::shared_ptr<FunctionCallHeader>& header)
	: INonTerminal(NonTerminalType::function_call_header_no_parameters), header(header)
{

}

Ceng::StringUtf8 FuncCallHeaderNoParams::ToString(unsigned int indentLevel) const
{
	return header->ToString(indentLevel);
}

void FuncCallHeaderNoParams::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_FuncCallHeaderNoParams(*this);
}