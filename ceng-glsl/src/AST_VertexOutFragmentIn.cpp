#include <ceng/GLSL/AST_VertexOutFragmentIn.h>

using namespace Ceng::GLSL;

AST_VertexOutFragmentIn::AST_VertexOutFragmentIn(bool invariant, InterpolationQualifierType::value interpolation,
	StorageQualifierType::value storage, const AST_Datatype& datatype, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::vertex_fragment_interface_variable), invariant(invariant), interpolation(interpolation),
	storage(storage), datatype(datatype), name(name)
{

}

AST_VertexOutFragmentIn::~AST_VertexOutFragmentIn()
{

}

Ceng::StringUtf8 AST_VertexOutFragmentIn::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	if (invariant)
	{
		out += "invariant ";
	}

	if (interpolation != InterpolationQualifierType::unused)
	{
		out += InterpolationQualifierType::ToString(interpolation);
		out += ' ';
	}

	out += StorageQualifierType::ToString(storage);
	out += ' ';

	out += datatype.ToString();
	out += ' ';
	out += name;
	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_VertexOutFragmentIn::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}