#include <ceng/GLSL/AST_FunctionCall.h>

#include "SymbolLink.h"

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_FunctionCall::AST_FunctionCall(const Lvalue& lhs, std::shared_ptr<Ceng::SymbolLink>& function, std::vector<Rvalue>&& params)
	: IASTNode(AST_NodeType::function_call), lhs(lhs), function(function), params(std::move(params))
{

}

AST_FunctionCall::~AST_FunctionCall()
{

}

Ceng::StringUtf8 AST_FunctionCall::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);

	out += lhs.ToString(indentLevel);
	out += " = ";
	out += RhsToString(indentLevel);
	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_FunctionCall::RhsToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	Symbol* func = function->Get();

	out += *func->Name();
	out += '(';

	for(size_t k=0; k < params.size(); k++)
	{
		out += params[k].ToString(indentLevel);

		if (k < params.size() - 1)
		{
			out += ", ";
		}
	}

	out += ')';

	return out;
}