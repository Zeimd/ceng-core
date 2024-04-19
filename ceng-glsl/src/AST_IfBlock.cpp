#include <ceng/GLSL/AST_IfBlock.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_IfBlock::AST_IfBlock(const Rvalue& condition)
	: IASTNode(AST_NodeType::if_block), condition(condition)
{

}

AST_IfBlock::~AST_IfBlock() 
{

}

Ceng::StringUtf8 AST_IfBlock::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);

	out += "if(";

	out += condition.ToString(indentLevel);

	out += ")\n";

	out += children[0]->ToString(indentLevel);

	if (children.size() == 2)
	{
		out += INonTerminal::GetIndent(indentLevel);
		out += "else";

		out += children[1]->ToString(indentLevel);
	}

	return out;
}

Ceng::StringUtf8 AST_IfBlock::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}