#include <ceng/GLSL/AST_IncDecOperation.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_IncDecOperation::AST_IncDecOperation(Lvalue& target, bool dec)
	: IASTNode(AST_NodeType::inc_dec), target(target), dec(dec)
{

}

AST_IncDecOperation::~AST_IncDecOperation()
{

}

Ceng::StringUtf8 AST_IncDecOperation::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);

	if (dec)
	{
		out += "--";
	}
	else
	{
		out += "++";
	}

	out += target.ToString(indentLevel);
	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_IncDecOperation::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}