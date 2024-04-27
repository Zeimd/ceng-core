#include <ceng/GLSL/AST_GeometryShaderIn.h>

using namespace Ceng::GLSL;

AST_GeometryShaderIn::AST_GeometryShaderIn(GeometryShaderInputLayout layout)
	: IASTNode(AST_NodeType::geometry_shader_input_layout), layout(layout)
{

}

AST_GeometryShaderIn::~AST_GeometryShaderIn()
{

}

Ceng::StringUtf8 AST_GeometryShaderIn::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += "layout(";

	switch (layout)
	{
	case GeometryShaderInputLayout::lines:
		out += "lines";
		break;
	case GeometryShaderInputLayout::lines_adjacency:
		out += "lines_adjacency";
		break;
	case GeometryShaderInputLayout::points:
		out += "points";
		break;
	case GeometryShaderInputLayout::triangles:
		out += "triangles";
		break;
	case GeometryShaderInputLayout::triangles_adjacency:
		out += "triangles_adjacency";
	default:
		out += "<UNHANDLED GEOMETRY SHADER INPUT LAYOUT";
	}

	out += ") in;\n";

	return out;
}

Ceng::StringUtf8 AST_GeometryShaderIn::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}