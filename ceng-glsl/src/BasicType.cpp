#include <ceng/GLSL/BasicType.h>

using namespace Ceng::GLSL;

#define CASE_TO_TEXT(x) case GLSL::BasicType::x: return #x;

const char* BasicType::ToString(BasicType::value type)
{
	switch (type)
	{
	case GLSL::BasicType::ts_void:
		return "void";
	case GLSL::BasicType::ts_float:
		return "float";
	case GLSL::BasicType::ts_int:
		return "int";
	case GLSL::BasicType::ts_uint:
		return "uint";
	case GLSL::BasicType::ts_bool:
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
	default:
		return "<UNHANDLED DATA TYPE>";
	}
}

#undef CASE_TO_TEXT

static BasicTypeInfo info_ts_void{ BasicTypeCategory::scalar, BasicType::ts_void, 1,1, TextureType::none };
static BasicTypeInfo info_ts_float{ BasicTypeCategory::scalar, BasicType::ts_float, 1,1, TextureType::none };
static BasicTypeInfo info_ts_int{ BasicTypeCategory::scalar, BasicType::ts_int, 1,1, TextureType::none };
static BasicTypeInfo info_ts_uint{ BasicTypeCategory::scalar, BasicType::ts_uint, 1,1, TextureType::none };
static BasicTypeInfo info_ts_bool{ BasicTypeCategory::scalar, BasicType::ts_bool, 1,1, TextureType::none };

static BasicTypeInfo info_vec2{ BasicTypeCategory::vector, BasicType::ts_float, 2,1, TextureType::none };
static BasicTypeInfo info_vec3{ BasicTypeCategory::vector, BasicType::ts_float, 3,1, TextureType::none };
static BasicTypeInfo info_vec4{ BasicTypeCategory::vector, BasicType::ts_float, 4,1, TextureType::none };

static BasicTypeInfo info_bvec2{ BasicTypeCategory::vector, BasicType::ts_bool, 2,1, TextureType::none };
static BasicTypeInfo info_bvec3{ BasicTypeCategory::vector, BasicType::ts_bool, 3,1, TextureType::none };
static BasicTypeInfo info_bvec4{ BasicTypeCategory::vector, BasicType::ts_bool, 4,1, TextureType::none };

static BasicTypeInfo info_ivec2{ BasicTypeCategory::vector, BasicType::ts_int, 2,1, TextureType::none };
static BasicTypeInfo info_ivec3{ BasicTypeCategory::vector, BasicType::ts_int, 3,1, TextureType::none };
static BasicTypeInfo info_ivec4{ BasicTypeCategory::vector, BasicType::ts_int, 4,1, TextureType::none };

static BasicTypeInfo info_uvec2{ BasicTypeCategory::vector, BasicType::ts_uint, 2,1, TextureType::none };
static BasicTypeInfo info_uvec3{ BasicTypeCategory::vector, BasicType::ts_uint, 3,1, TextureType::none };
static BasicTypeInfo info_uvec4{ BasicTypeCategory::vector, BasicType::ts_uint, 4,1, TextureType::none };

static BasicTypeInfo info_mat2{ BasicTypeCategory::matrix, BasicType::ts_float, 2,2 , TextureType::none };
static BasicTypeInfo info_mat3{ BasicTypeCategory::matrix, BasicType::ts_float, 3,3 , TextureType::none };
static BasicTypeInfo info_mat4{ BasicTypeCategory::matrix, BasicType::ts_float, 4,4 , TextureType::none };

static BasicTypeInfo info_mat2x2{ BasicTypeCategory::matrix, BasicType::ts_float, 2,2 , TextureType::none };
static BasicTypeInfo info_mat2x3{ BasicTypeCategory::matrix, BasicType::ts_float, 2,3 , TextureType::none };
static BasicTypeInfo info_mat2x4{ BasicTypeCategory::matrix, BasicType::ts_float, 2,4 , TextureType::none };

static BasicTypeInfo info_mat3x2{ BasicTypeCategory::matrix, BasicType::ts_float, 3,2 , TextureType::none };
static BasicTypeInfo info_mat3x3{ BasicTypeCategory::matrix, BasicType::ts_float, 3,3 , TextureType::none };
static BasicTypeInfo info_mat3x4{ BasicTypeCategory::matrix, BasicType::ts_float, 3,4 , TextureType::none };

static BasicTypeInfo info_mat4x2{ BasicTypeCategory::matrix, BasicType::ts_float, 4,2 , TextureType::none };
static BasicTypeInfo info_mat4x3{ BasicTypeCategory::matrix, BasicType::ts_float, 4,3 , TextureType::none };
static BasicTypeInfo info_mat4x4{ BasicTypeCategory::matrix, BasicType::ts_float, 4,4 , TextureType::none };

static BasicTypeInfo info_sampler1D{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::normal };
static BasicTypeInfo info_sampler2D{ BasicTypeCategory::sampler, BasicType::ts_float, 2,1 , TextureType::normal };
static BasicTypeInfo info_sampler3D{ BasicTypeCategory::sampler, BasicType::ts_float, 3,1 , TextureType::normal };

static BasicTypeInfo info_samplerCube{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::cube };
static BasicTypeInfo info_samplerCubeShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::cube_shadow };

static BasicTypeInfo info_sampler1DShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::normal_shadow };
static BasicTypeInfo info_sampler2DShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::normal_shadow };

static BasicTypeInfo info_sampler1DArray{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array };
static BasicTypeInfo info_sampler2DArray{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array };

static BasicTypeInfo info_sampler1DArrayShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array_shadow };
static BasicTypeInfo info_sampler2DArrayShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array_shadow };

static BasicTypeInfo info_isampler1D{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::normal };
static BasicTypeInfo info_isampler2D{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::normal };
static BasicTypeInfo info_isampler3D{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::normal };

static BasicTypeInfo info_isamplerCube{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::cube };

static BasicTypeInfo info_isampler1DArray{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::array };
static BasicTypeInfo info_isampler2DArray{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::array };

static BasicTypeInfo info_usampler1D{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::normal };
static BasicTypeInfo info_usampler2D{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::normal };
static BasicTypeInfo info_usampler3D{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::normal };

static BasicTypeInfo info_usamplerCube{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::cube };

static BasicTypeInfo info_usampler1DArray{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::array };
static BasicTypeInfo info_usampler2DArray{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::array };

static BasicTypeInfo info_sampler2DRect{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::rect };
static BasicTypeInfo info_sampler2DRectShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::rect_shadow };

static BasicTypeInfo info_isampler2DRect{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::rect };
static BasicTypeInfo info_usampler2DRect{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::rect };

static BasicTypeInfo info_samplerBuffer{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::buffer };
static BasicTypeInfo info_isamplerBuffer{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::buffer };
static BasicTypeInfo info_usamplerBuffer{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::buffer };

static BasicTypeInfo info_sampler2DMS{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::multisample };
static BasicTypeInfo info_isampler2DMS{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::multisample };
static BasicTypeInfo info_usampler2DMS{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::multisample };

static BasicTypeInfo info_sampler2DMSArray{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::multisample_array };
static BasicTypeInfo info_isampler2DMSArray{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::multisample_array };
static BasicTypeInfo info_usampler2DMSArray{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::multisample_array };

static BasicTypeInfo info_invalid{ BasicTypeCategory::invalid, BasicType::invalid, 1,1 , TextureType::none };

const BasicTypeInfo& Ceng::GLSL::GetTypeInfo(BasicType::value type)
{
	switch (type)
	{
	case BasicType::ts_void:
		return info_ts_void;
	case BasicType::ts_float:
		return info_ts_float;
	case BasicType::ts_int:
		return info_ts_int;
	case BasicType::ts_uint:
		return info_ts_uint;
	case BasicType::ts_bool:
		return info_ts_bool;
	case BasicType::vec2:
		return info_vec2;
	case BasicType::vec3:
		return info_vec3;
	case BasicType::vec4:
		return info_vec4;
	case BasicType::bvec2:
		return info_bvec2;
	case BasicType::bvec3:
		return info_bvec3;
	case BasicType::bvec4:
		return info_bvec4;
	case BasicType::ivec2:
		return info_ivec2;
	case BasicType::ivec3:
		return info_ivec3;
	case BasicType::ivec4:
		return info_ivec4;
	case BasicType::uvec2:
		return info_uvec2;
	case BasicType::uvec3:
		return info_uvec3;
	case BasicType::uvec4:
		return info_uvec4;
	case BasicType::mat2:
		return info_mat2;
	case BasicType::mat3:
		return info_mat3;
	case BasicType::mat4:
		return info_mat4;
	case BasicType::mat2x2:
		return info_mat2x2;
	case BasicType::mat2x3:
		return info_mat2x3;
	case BasicType::mat2x4:
		return info_mat2x4;
	case BasicType::mat3x2:
		return info_mat3x2;
	case BasicType::mat3x3:
		return info_mat3x3;
	case BasicType::mat3x4:
		return info_mat3x4;
	case BasicType::mat4x2:
		return info_mat4x2;
	case BasicType::mat4x3:
		return info_mat4x3;
	case BasicType::mat4x4:
		return info_mat4x4;
	case BasicType::sampler1D:
		return info_sampler1D;
	case BasicType::sampler2D:
		return info_sampler2D;
	case BasicType::sampler3D:
		return info_sampler3D;
	case BasicType::samplerCube:
		return info_samplerCube;
	case BasicType::sampler1DShadow:
		return info_sampler1DShadow;
	case BasicType::sampler2DShadow:
		return info_sampler2DShadow;
	case BasicType::samplerCubeShadow:
		return info_samplerCubeShadow;
	case BasicType::sampler1DArray:
		return info_sampler1DArray;
	case BasicType::sampler2DArray:
		return info_sampler2DArray;
	case BasicType::sampler1DArrayShadow:
		return info_sampler1DArrayShadow;
	case BasicType::sampler2DArrayShadow:
		return info_sampler2DArrayShadow;
	case BasicType::isampler1D:
		return info_isampler1D;
	case BasicType::isampler2D:
		return info_isampler2D;
	case BasicType::isampler3D:
		return info_isampler3D;
	case BasicType::isamplerCube:
		return info_isamplerCube;
	case BasicType::isampler1DArray:
		return info_isampler1DArray;
	case BasicType::isampler2DArray:
		return info_isampler2DArray;
	case BasicType::usampler1D:
		return info_usampler1D;
	case BasicType::usampler2D:
		return info_usampler2D;
	case BasicType::usampler3D:
		return info_usampler3D;
	case BasicType::usamplerCube:
		return info_usamplerCube;
	case BasicType::usampler1DArray:
		return info_usampler1DArray;
	case BasicType::usampler2DArray:
		return info_usampler2DArray;
	case BasicType::sampler2DRect:
		return info_sampler2DRect;
	case BasicType::sampler2DRectShadow:
		return info_sampler2DRectShadow;
	case BasicType::isampler2DRect:
		return info_isampler2DRect;
	case BasicType::usampler2DRect:
		return info_usampler2DRect;
	case BasicType::samplerBuffer:
		return info_samplerBuffer;
	case BasicType::isamplerBuffer:
		return info_isamplerBuffer;
	case BasicType::usamplerBuffer:
		return info_usamplerBuffer;
	case BasicType::sampler2DMS:
		return info_sampler2DMS;
	case BasicType::isampler2DMS:
		return info_isampler2DMS;
	case BasicType::usampler2DMS:
		return info_usampler2DMS;
	case BasicType::sampler2DMSArray:
		return info_sampler2DMSArray;
	case BasicType::isampler2DMSArray:
		return info_isampler2DMSArray;
	case BasicType::usampler2DMSArray:
		return info_usampler2DMSArray;
	case BasicType::invalid:
	default:
		return info_invalid;
	}
}
