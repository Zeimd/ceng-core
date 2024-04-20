#include <ceng/GLSL/AST_SwitchBlock.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_SwitchBlock::AST_SwitchBlock(const Rvalue& input)
	: IASTNode(AST_NodeType::switch_block), input(input)
{

}

AST_SwitchBlock::~AST_SwitchBlock() 
{

}

Ceng::StringUtf8 AST_SwitchBlock::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);
	out += "switch(";
	out += input.ToString(indentLevel);
	out += ")\n";

	out += INonTerminal::GetIndent(indentLevel);
	out += "{\n";

	for (auto& x : children)
	{
		out += x->ToString(indentLevel);
	}

	out += INonTerminal::GetIndent(indentLevel);
	out += "}\n";

	return out;
}

Ceng::StringUtf8 AST_SwitchBlock::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}