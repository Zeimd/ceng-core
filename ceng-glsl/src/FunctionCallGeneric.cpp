#include "FunctionCallGeneric.h"

#include "NonTerminalVisitor.h"

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

Ceng::StringUtf8 FunctionCallGeneric::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (noParams != nullptr)
	{
		out += noParams->ToString(indentLevel);
		out += ')';
		return out;
	}
	else if (withParams != nullptr)
	{
		out += withParams->ToString(indentLevel);
		out += ')';
		return out;
	}

	return "<UNHANDLED FUNCTION TYPE>";
}

void FunctionCallGeneric::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FunctionCallGeneric(*this);
}