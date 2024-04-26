#include <ceng/GLSL/SimpleDeclaration.h>

using namespace Ceng::GLSL;

SimpleDeclaration::SimpleDeclaration(bool constant_, PrecisionQualifierType::value precision_,
	const AST_Datatype& datatype_, Ceng::StringUtf8 name_)
	: constant(constant_), precision(precision_), datatype(datatype_), name(name_)
{

}

Ceng::StringUtf8 SimpleDeclaration::ToString() const
{
	Ceng::StringUtf8 out;

	if (constant)
	{
		out += "const ";
	}

	out += GLSL::PrecisionQualifierType::ToString(precision);
	if (precision != GLSL::PrecisionQualifierType::unassigned)
	{
		out += ' ';
	}

	out += datatype.ToString();
	out += ' ';

	out += name;

	return out;
}