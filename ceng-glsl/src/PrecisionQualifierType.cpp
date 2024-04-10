#include <ceng/GLSL/PrecisionQualifierType.h>

using namespace Ceng::GLSL;

#define CASE_TO_TEXT(x) case GLSL::PrecisionQualifierType::x: return #x; break;

const char* PrecisionQualifierType::ToString(PrecisionQualifierType::value type)
{
	switch (type)
	{
		CASE_TO_TEXT(high);
		CASE_TO_TEXT(medium);
		CASE_TO_TEXT(low);
	case GLSL::PrecisionQualifierType::unassigned:
		return "";
	case GLSL::PrecisionQualifierType::invalid_value:
		return "<INVALID PRECISION TYPE>";
	default:
		return "<UNHANDLED PRECISION TYPE>";
	}
}

#undef CASE_TO_TEXT