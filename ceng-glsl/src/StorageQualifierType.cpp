#include <ceng/GLSL/StorageQualifierType.h>

using namespace Ceng::GLSL;

const char* StorageQualifierType::ToString(StorageQualifierType::value type)
{
	switch (type)
	{
	case GLSL::StorageQualifierType::sq_const:
		return "const";
	case GLSL::StorageQualifierType::sq_attribute:
		return "attribute";
	case GLSL::StorageQualifierType::sq_centroid_in:
		return "centroid in";
	case GLSL::StorageQualifierType::sq_centroid_out:
		return "centroid out";
	case GLSL::StorageQualifierType::sq_centroid_varying:
		return "centroid varying";
	case GLSL::StorageQualifierType::sq_in:
		return "in";
	case GLSL::StorageQualifierType::sq_out:
		return "out";
	case GLSL::StorageQualifierType::sq_uniform:
		return "uniform";
	case GLSL::StorageQualifierType::sq_varying:
		return "varying";
	case GLSL::StorageQualifierType::unused:
		return "";
	default:
		return"StorageQualifier::unhandled";
	}
}

