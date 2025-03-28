#include "FunctionHeaderWithParams.h"
#include "FunctionHeader.h"
#include "ParameterDeclaration.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

FunctionHeaderWithParams::~FunctionHeaderWithParams()
{

}

void FunctionHeaderWithParams::Release()
{
	delete this;
}

FunctionHeaderWithParams::FunctionHeaderWithParams(std::shared_ptr<FunctionHeader>& header, std::shared_ptr<ParameterDeclaration>& decl)
	: INonTerminal(NonTerminalType::function_header_with_parameters), header(header), params{ decl }
{

}

FunctionHeaderWithParams::FunctionHeaderWithParams(std::shared_ptr<FunctionHeader>& header, std::vector<std::shared_ptr<ParameterDeclaration>>& params)
	: INonTerminal(NonTerminalType::function_header_with_parameters), header(header), params{ params }
{

}

void FunctionHeaderWithParams::Append(std::shared_ptr<ParameterDeclaration>& decl)
{
	params.push_back(decl);
}

Ceng::StringUtf8 FunctionHeaderWithParams::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += header->ToString(indentLevel);

	for (size_t k = 0; k < params.size(); k++)
	{
		out += params[k]->ToString(indentLevel);

		if (k < params.size() - 1)
		{
			out += ", ";
		}
	}

	return out;
}

void FunctionHeaderWithParams::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FunctionHeaderWithParams(*this);
}