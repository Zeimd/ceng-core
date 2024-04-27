#include <ceng/GLSL/AST_GeometryShaderOut.h>

using namespace Ceng::GLSL;

AST_GeometryShaderOut::AST_GeometryShaderOut(GeometryShaderOutputPrimitive primitive)
	: IASTNode(AST_NodeType::geometry_shader_output_layout), definedPrimitive(true), primitive(primitive), definedMax(false), maxVertices(0)
{

}

AST_GeometryShaderOut::AST_GeometryShaderOut(Ceng::UINT32 maxVertices)
	: IASTNode(AST_NodeType::geometry_shader_output_layout), definedPrimitive(false), definedMax(true), maxVertices(maxVertices)
{

}

AST_GeometryShaderOut::AST_GeometryShaderOut(GeometryShaderOutputPrimitive primitive, Ceng::UINT32 maxVertices)
	: IASTNode(AST_NodeType::geometry_shader_output_layout), definedPrimitive(true), primitive(primitive), definedMax(true), maxVertices(maxVertices)
{

}

AST_GeometryShaderOut::~AST_GeometryShaderOut()
{

}

Ceng::StringUtf8 AST_GeometryShaderOut::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += "layout(";

	if (definedPrimitive)
	{
		switch (primitive)
		{
		case GeometryShaderOutputPrimitive::points:
			out += "points";
			break;
		case GeometryShaderOutputPrimitive::line_strip:
			out += "line_strip";
			break;
		case GeometryShaderOutputPrimitive::triangle_strip:
			out += "triangle_strip";
			break;
		default:
			out += "<UNHANDLED GEOMETRY SHADER OUTPUT PRIMITIVE>";
		}

		out += ",";
	}

	if (definedMax)
	{
		out += maxVertices;
	}

	out += ");\n";

	return out;
}

Ceng::StringUtf8 AST_GeometryShaderOut::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}