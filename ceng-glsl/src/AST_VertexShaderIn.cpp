#include <ceng/GLSL/AST_VertexShaderIn.h>

using namespace Ceng::GLSL;

AST_VertexShaderIn::AST_VertexShaderIn(const AST_Datatype& dataType, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::vertex_shader_input_variable), hasLocation(false), dataType(dataType), name(name)
{

}

AST_VertexShaderIn::AST_VertexShaderIn(Ceng::UINT32 location, const AST_Datatype& dataType, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::vertex_shader_input_variable), hasLocation(true), location(location), dataType(dataType), name(name)
{

}

AST_VertexShaderIn::~AST_VertexShaderIn()
{

}

Ceng::StringUtf8 AST_VertexShaderIn::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	if (hasLocation)
	{
		out += "layout(location=";

		out += location;

		out += ") ";
	}

	out += "in ";

	out += dataType.ToString();

	out += ' ';

	out += name;
	
	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_VertexShaderIn::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}