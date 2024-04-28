#include <ceng/GLSL/AST_FragCoordLayout.h>

using namespace Ceng::GLSL;

AST_FragCoordLayout::AST_FragCoordLayout(bool originUpperLeft, bool pixelCenterInt)
	: IASTNode(AST_NodeType::frag_coord_layout), originUpperLeft(originUpperLeft), pixelCenterInt(pixelCenterInt)
{

}

AST_FragCoordLayout::~AST_FragCoordLayout()
{

}

Ceng::StringUtf8 AST_FragCoordLayout::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	if (originUpperLeft || pixelCenterInt)
	{
		out += "layout(";
	}

	if (originUpperLeft)
	{
		out += "origin_upper_left";

		if (pixelCenterInt)
		{
			out += ", ";
		}
	}

	if (pixelCenterInt)
	{
		out += "pixel_center_integer";
	}

	if (originUpperLeft || pixelCenterInt)
	{
		out += ") ";
	}

	out += "in vec4 gl_FragCoord;\n";

	return out;
}

Ceng::StringUtf8 AST_FragCoordLayout::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}