#include <ceng/GLSL/ParameterQualifierType.h>

using namespace Ceng::GLSL;

const char* ParameterQualifierType::ToString(ParameterQualifierType::value type)
{
	switch (type)
	{
	case GLSL::ParameterQualifierType::empty:
		return "";
	case GLSL::ParameterQualifierType::in:
		return "in";
	case GLSL::ParameterQualifierType::out:
		return "out";
	case GLSL::ParameterQualifierType::inout:
		return "inout";
	case GLSL::ParameterQualifierType::invalid_value:
		return "<invalid>";
	default:
		return "<UNHANDLED PARAMETER QUALIFIER>";
	}
}