#include <ceng/GLSL/AST_InvariantStatement.h>

using namespace Ceng::GLSL;

AST_InvariantStatement::AST_InvariantStatement(std::vector<Ceng::StringUtf8>&& names)
	: IASTNode(AST_NodeType::invariant_statement), names(std::move(names))
{

}

AST_InvariantStatement::~AST_InvariantStatement()
{

}

Ceng::StringUtf8 AST_InvariantStatement::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += "invariant ";

	for (size_t k = 0; k < names.size(); k++)
	{
		out += names[k];

		if (k != names.size() - 1)
		{
			out += ", ";
		}
	}

	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_InvariantStatement::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}