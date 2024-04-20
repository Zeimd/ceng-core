#include <ceng/GLSL/AST_Break.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_Break::AST_Break()
	: IASTNode(AST_NodeType::break_statement)
{

}

AST_Break::~AST_Break()
{

}

Ceng::StringUtf8 AST_Break::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;
	
	out += INonTerminal::GetIndent(indentLevel);

	out += "break;\n";

	return out;
}

Ceng::StringUtf8 AST_Break::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}