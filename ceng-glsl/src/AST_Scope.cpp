#include <ceng/GLSL/AST_Scope.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_Scope::AST_Scope()
	: IASTNode(AST_NodeType::scope)
{

}

AST_Scope::~AST_Scope()
{

}

Ceng::StringUtf8 AST_Scope::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);
	out += "{\n";

	for (auto& x : children)
	{
		out += x->ToString(indentLevel + 1);
	}

	out += INonTerminal::GetIndent(indentLevel);
	out += "}\n";

	return out;
}

Ceng::StringUtf8 AST_Scope::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}