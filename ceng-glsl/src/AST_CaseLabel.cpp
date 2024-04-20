#include <ceng/GLSL/AST_CaseLabel.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_CaseLabel::AST_CaseLabel()
	: IASTNode(AST_NodeType::case_label), expression()
{

}

AST_CaseLabel::AST_CaseLabel(const Rvalue& expression)
	: IASTNode(AST_NodeType::case_label), expression(expression)
{

}

AST_CaseLabel::~AST_CaseLabel()
{

}

Ceng::StringUtf8 AST_CaseLabel::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);

	if (expression.valueType == RvalueType::unused)
	{
		out += "default:\n";
	}
	else
	{
		out += "case ";
		out += expression.ToString(indentLevel);
		out += ":\n";
	}

	for (auto& x : children)
	{
		out += x->ToString(indentLevel + 1);
	}

	return out;
}

Ceng::StringUtf8 AST_CaseLabel::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}