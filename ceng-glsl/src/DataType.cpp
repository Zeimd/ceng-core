#include <ceng/GLSL/DataType.h>

using namespace Ceng::GLSL;

#define CASE_TO_TEXT(x) case GLSL::DataType::x: return #x;

const char* DataType::ToString(DataType::value type)
{
	switch (type)
	{
	case GLSL::DataType::ts_void:
		return "void";
	case GLSL::DataType::ts_float:
		return "float";
	case GLSL::DataType::ts_int:
		return "int";
	case GLSL::DataType::ts_uint:
		return "uint";
	case GLSL::DataType::ts_bool:
		return "bool";
		CASE_TO_TEXT(vec2);
		CASE_TO_TEXT(vec3);
		CASE_TO_TEXT(vec4);
		CASE_TO_TEXT(bvec2);
		CASE_TO_TEXT(bvec3);
		CASE_TO_TEXT(bvec4);
		CASE_TO_TEXT(ivec2);
		CASE_TO_TEXT(ivec3);
		CASE_TO_TEXT(ivec4);
		CASE_TO_TEXT(uvec2);
		CASE_TO_TEXT(uvec3);
		CASE_TO_TEXT(uvec4);
		CASE_TO_TEXT(mat2);
		CASE_TO_TEXT(mat3);
		CASE_TO_TEXT(mat4);
		CASE_TO_TEXT(mat2x2);
		CASE_TO_TEXT(mat2x3);
		CASE_TO_TEXT(mat2x4);
		CASE_TO_TEXT(mat3x2);
		CASE_TO_TEXT(mat3x3);
		CASE_TO_TEXT(mat3x4);
		CASE_TO_TEXT(mat4x2);
		CASE_TO_TEXT(mat4x3);
		CASE_TO_TEXT(mat4x4);
		CASE_TO_TEXT(sampler1D);
		CASE_TO_TEXT(sampler2D);
		CASE_TO_TEXT(sampler3D);
		CASE_TO_TEXT(samplerCube);
		CASE_TO_TEXT(sampler1DShadow);
		CASE_TO_TEXT(sampler2DShadow);
		CASE_TO_TEXT(samplerCubeShadow);
		CASE_TO_TEXT(sampler1DArray);
		CASE_TO_TEXT(sampler2DArray);
		CASE_TO_TEXT(sampler1DArrayShadow);
		CASE_TO_TEXT(sampler2DArrayShadow);
		CASE_TO_TEXT(isampler1D);
		CASE_TO_TEXT(isampler2D);
		CASE_TO_TEXT(isampler3D);
		CASE_TO_TEXT(isamplerCube);
		CASE_TO_TEXT(isampler1DArray);
		CASE_TO_TEXT(isampler2DArray);
		CASE_TO_TEXT(usampler1D);
		CASE_TO_TEXT(usampler2D);
		CASE_TO_TEXT(usampler3D);
		CASE_TO_TEXT(usamplerCube);
		CASE_TO_TEXT(usampler1DArray);
		CASE_TO_TEXT(usampler2DArray);
		CASE_TO_TEXT(sampler2DRect);
		CASE_TO_TEXT(sampler2DRectShadow);
		CASE_TO_TEXT(isampler2DRect);
		CASE_TO_TEXT(usampler2DRect);
		CASE_TO_TEXT(samplerBuffer);
		CASE_TO_TEXT(isamplerBuffer);
		CASE_TO_TEXT(usamplerBuffer);
		CASE_TO_TEXT(sampler2DMS);
		CASE_TO_TEXT(isampler2DMS);
		CASE_TO_TEXT(usampler2DMS);
		CASE_TO_TEXT(sampler2DMSArray);
		CASE_TO_TEXT(isampler2DMSArray);
		CASE_TO_TEXT(usampler2DMSArray);
		CASE_TO_TEXT(invalid);
	case GLSL::DataType::type_name:
		return "type_name";
	case GLSL::DataType::struct_specifier:
		return "struct_specifier";
	default:
		return "<UNHANDLED DATA TYPE>";
	}
}

#undef CASE_TO_TEXT
