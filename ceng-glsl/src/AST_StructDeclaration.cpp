#include <ceng/GLSL/AST_StructDeclaration.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

AST_StructDeclaration::AST_StructDeclaration(const Ceng::StringUtf8& name, std::vector<StructMember>&& members)
	: IASTNode(AST_NodeType::struct_declaration), name(name), members(std::move(members))
{

}

AST_StructDeclaration::~AST_StructDeclaration()
{

}

Ceng::StringUtf8 AST_StructDeclaration::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);
	out += "struct {\n";

	for (auto& x : members)
	{
		out += x.ToString(indentLevel + 1);
	}

	out += INonTerminal::GetIndent(indentLevel);
	out += "};\n";

	return out;
}

Ceng::StringUtf8 AST_StructDeclaration::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}