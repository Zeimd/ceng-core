#include <ceng/GLSL/PrecisionQualifierType.h>

using namespace Ceng::GLSL;


const char* PrecisionQualifierType::ToString(PrecisionQualifierType::value type)
{
	switch (type)
	{
	case GLSL::PrecisionQualifierType::low:
		return "lowp";
	case GLSL::PrecisionQualifierType::medium:
		return "mediump";
	case GLSL::PrecisionQualifierType::high:
		return "highp";
	case GLSL::PrecisionQualifierType::unassigned:
		return "";
	case GLSL::PrecisionQualifierType::invalid_value:
		return "<INVALID PRECISION TYPE>";
	default:
		return "<UNHANDLED PRECISION TYPE>";
	}
}

