#include <ceng/GLSL/AST_NormalVariable.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_NormalVariable::AST_NormalVariable(const SimpleDeclaration& declaration)
	: IASTNode(AST_NodeType::normal_variable), declaration(declaration)
{

}

AST_NormalVariable::~AST_NormalVariable()
{

}

Ceng::StringUtf8 AST_NormalVariable::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);
	out += declaration.ToString();
	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_NormalVariable::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}