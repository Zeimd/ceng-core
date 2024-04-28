#include <ceng/GLSL/StructMember.h>

#include "INonTerminal.h"

using namespace Ceng::GLSL;

StructMember::StructMember(const AST_Datatype& datatype, const Ceng::StringUtf8& name)
	: precision(GLSL::PrecisionQualifierType::unassigned), datatype(datatype), name(name)
{

}

StructMember::StructMember(PrecisionQualifierType::value precision, const AST_Datatype& datatype, const Ceng::StringUtf8& name)
	: precision(precision), datatype(datatype), name(name)
{

}

Ceng::StringUtf8 StructMember::ToString(Ceng::UINT32 indentLevel) const
{
	Ceng::StringUtf8 out;

	out += INonTerminal::GetIndent(indentLevel);
	
	if (precision != GLSL::PrecisionQualifierType::unassigned)
	{
		out += GLSL::PrecisionQualifierType::ToString(precision);
		out += ' ';
	}

	out += datatype.ToString();
	out += ' ';

	out += name;

	out += ";\n";

	return out;
}