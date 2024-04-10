#include <ceng/GLSL/InterpolationQualifierType.h>

using namespace Ceng::GLSL;

const char* InterpolationQualifierType::ToString(InterpolationQualifierType::value type)
{
	switch (type)
	{
	case GLSL::InterpolationQualifierType::flat:
		return "flat";
	case GLSL::InterpolationQualifierType::noperspective:
		return "noperspective";
	case GLSL::InterpolationQualifierType::smooth:
		return "smooth";
	case GLSL::InterpolationQualifierType::unused:
		return "";
	default:
		return "<UNHANDLED INTERPOLATION QUALIFIER TYPE>";
	}
}