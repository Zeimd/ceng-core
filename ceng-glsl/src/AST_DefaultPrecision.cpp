#include <ceng/GLSL/AST_DefaultPrecision.h>

using namespace Ceng::GLSL;

AST_DefaultPrecision::AST_DefaultPrecision(PrecisionQualifierType::value precision, PrecisionTarget target)
	: IASTNode(AST_NodeType::default_precision), precision(precision), target(target)
{

}

AST_DefaultPrecision::~AST_DefaultPrecision()
{

}

Ceng::StringUtf8 AST_DefaultPrecision::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += "precision ";
	
	out += PrecisionQualifierType::ToString(precision);
	out += ' ';

	switch (target)
	{
	case PrecisionTarget::floating:
		out += "float";
		break;
	case PrecisionTarget::integer:
		out += "int";
		break;
	default:
		out += "<UNHANDLED PRECISION TARGET>";
		break;
	}

	out += ";\n";

	return out;
}

Ceng::StringUtf8 AST_DefaultPrecision::RhsToString(Ceng::UINT32 indentLevel) const
{
	return "";
}