#include <ceng/GLSL/AST_FragmentShaderOut.h>

using namespace Ceng::GLSL;

AST_FragmentShaderOut::AST_FragmentShaderOut(bool explicitLocation, Ceng::UINT32 location,
	bool explicitIndex, Ceng::UINT32 index, const AST_Datatype& datatype, const Ceng::StringUtf8& name)
	: IASTNode(AST_NodeType::fragment_shader_output_variable), explicitLocation(explicitLocation),
	location(location), explicitIndex(explicitIndex), index(index), datatype(datatype), name(name)
{

}

AST_FragmentShaderOut::~AST_FragmentShaderOut()
{

}

Ceng::StringUtf8 AST_FragmentShaderOut::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	if (explicitLocation || explicitIndex)
	{
		out += "layout(";
	}

	if (explicitLocation)
	{
		out += "location = ";
		out += location;
		
		if (explicitIndex)
		{
			out += ", ";
		}
	}

	if (explicitIndex)
	{
		out += "index = ";
		out += index;
	}

	if (explicitLocation || explicitIndex)
	{
		out += ") ";
	}

	out += "out ";

	out += datatype.ToString();

	out += ' ';

	out += name;

	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_FragmentShaderOut::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}