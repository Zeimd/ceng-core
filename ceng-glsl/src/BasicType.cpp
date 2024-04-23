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

static BasicTypeInfo ts_void{ BasicTypeCategory::scalar, BasicType::ts_void, 1,1, TextureType::none };
static BasicTypeInfo ts_float{ BasicTypeCategory::scalar, BasicType::ts_float, 1,1, TextureType::none };
static BasicTypeInfo ts_int{ BasicTypeCategory::scalar, BasicType::ts_int, 1,1, TextureType::none };
static BasicTypeInfo ts_uint{ BasicTypeCategory::scalar, BasicType::ts_uint, 1,1, TextureType::none };
static BasicTypeInfo ts_bool{ BasicTypeCategory::scalar, BasicType::ts_bool, 1,1, TextureType::none };

static BasicTypeInfo vec2{ BasicTypeCategory::vector, BasicType::ts_float, 2,1, TextureType::none };
static BasicTypeInfo vec3{ BasicTypeCategory::vector, BasicType::ts_float, 3,1, TextureType::none };
static BasicTypeInfo vec4{ BasicTypeCategory::vector, BasicType::ts_float, 4,1, TextureType::none };

static BasicTypeInfo bvec2{ BasicTypeCategory::vector, BasicType::ts_bool, 2,1, TextureType::none };
static BasicTypeInfo bvec3{ BasicTypeCategory::vector, BasicType::ts_bool, 3,1, TextureType::none };
static BasicTypeInfo bvec4{ BasicTypeCategory::vector, BasicType::ts_bool, 4,1, TextureType::none };

static BasicTypeInfo ivec2{ BasicTypeCategory::vector, BasicType::ts_int, 2,1, TextureType::none };
static BasicTypeInfo ivec3{ BasicTypeCategory::vector, BasicType::ts_int, 3,1, TextureType::none };
static BasicTypeInfo ivec4{ BasicTypeCategory::vector, BasicType::ts_int, 4,1, TextureType::none };

static BasicTypeInfo uvec2{ BasicTypeCategory::vector, BasicType::ts_uint, 2,1, TextureType::none };
static BasicTypeInfo uvec3{ BasicTypeCategory::vector, BasicType::ts_uint, 3,1, TextureType::none };
static BasicTypeInfo uvec4{ BasicTypeCategory::vector, BasicType::ts_uint, 4,1, TextureType::none };

static BasicTypeInfo mat2{ BasicTypeCategory::matrix, BasicType::ts_float, 2,2 , TextureType::none };
static BasicTypeInfo mat3{ BasicTypeCategory::matrix, BasicType::ts_float, 3,3 , TextureType::none };
static BasicTypeInfo mat4{ BasicTypeCategory::matrix, BasicType::ts_float, 4,4 , TextureType::none };

static BasicTypeInfo mat2x2{ BasicTypeCategory::matrix, BasicType::ts_float, 2,2 , TextureType::none };
static BasicTypeInfo mat2x3{ BasicTypeCategory::matrix, BasicType::ts_float, 2,3 , TextureType::none };
static BasicTypeInfo mat2x4{ BasicTypeCategory::matrix, BasicType::ts_float, 2,4 , TextureType::none };

static BasicTypeInfo mat3x2{ BasicTypeCategory::matrix, BasicType::ts_float, 3,2 , TextureType::none };
static BasicTypeInfo mat3x3{ BasicTypeCategory::matrix, BasicType::ts_float, 3,3 , TextureType::none };
static BasicTypeInfo mat3x4{ BasicTypeCategory::matrix, BasicType::ts_float, 3,4 , TextureType::none };

static BasicTypeInfo mat4x2{ BasicTypeCategory::matrix, BasicType::ts_float, 4,2 , TextureType::none };
static BasicTypeInfo mat4x3{ BasicTypeCategory::matrix, BasicType::ts_float, 4,3 , TextureType::none };
static BasicTypeInfo mat4x4{ BasicTypeCategory::matrix, BasicType::ts_float, 4,4 , TextureType::none };

static BasicTypeInfo sampler1D{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::normal };
static BasicTypeInfo sampler2D{ BasicTypeCategory::sampler, BasicType::ts_float, 2,1 , TextureType::normal };
static BasicTypeInfo sampler3D{ BasicTypeCategory::sampler, BasicType::ts_float, 3,1 , TextureType::normal };

static BasicTypeInfo samplerCube{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::cube };
static BasicTypeInfo samplerCubeShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::cube_shadow };

static BasicTypeInfo sampler1DShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::normal_shadow };
static BasicTypeInfo sampler2DShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::normal_shadow };

static BasicTypeInfo sampler1DArray{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array };
static BasicTypeInfo sampler2DArray{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array };

static BasicTypeInfo sampler1DArrayShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array_shadow };
static BasicTypeInfo sampler2DArrayShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::array_shadow };

static BasicTypeInfo isampler1D{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::normal };
static BasicTypeInfo isampler2D{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::normal };
static BasicTypeInfo isampler3D{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::normal };

static BasicTypeInfo isamplerCube{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::cube };

static BasicTypeInfo isampler1DArray{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::array };
static BasicTypeInfo isampler2DArray{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::array };

static BasicTypeInfo usampler1D{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::normal };
static BasicTypeInfo usampler2D{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::normal };
static BasicTypeInfo usampler3D{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::normal };

static BasicTypeInfo usamplerCube{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::cube };

static BasicTypeInfo usampler1DArray{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::array };
static BasicTypeInfo usampler2DArray{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::array };

static BasicTypeInfo sampler2DRect{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::rect };
static BasicTypeInfo sampler2DRectShadow{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::rect_shadow };

static BasicTypeInfo isampler2DRect{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::rect };
static BasicTypeInfo usampler2DRect{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::rect };

static BasicTypeInfo samplerBuffer{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::buffer };
static BasicTypeInfo isamplerBuffer{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::buffer };
static BasicTypeInfo usamplerBuffer{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::buffer };

static BasicTypeInfo sampler2DMS{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::multisample };
static BasicTypeInfo isampler2DMS{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::multisample };
static BasicTypeInfo usampler2DMS{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::multisample };

static BasicTypeInfo sampler2DMSArray{ BasicTypeCategory::sampler, BasicType::ts_float, 1,1 , TextureType::multisample_array };
static BasicTypeInfo isampler2DMSArray{ BasicTypeCategory::sampler, BasicType::ts_int, 1,1 , TextureType::multisample_array };
static BasicTypeInfo usampler2DMSArray{ BasicTypeCategory::sampler, BasicType::ts_uint, 1,1 , TextureType::multisample_array };

static BasicTypeInfo invalid{ BasicTypeCategory::invalid, BasicType::invalid, 1,1 , TextureType::none };

const BasicTypeInfo& GetTypeInfo(BasicType::value type)
{
	switch (type)
	{
	case BasicType::ts_void:
		return ts_void;
	case BasicType::ts_float:
		return ts_float;
	case BasicType::ts_int:
		return ts_int;
	case BasicType::ts_uint:
		return ts_uint;
	case BasicType::ts_bool:
		return ts_bool;
	case BasicType::vec2:
		return vec2;
	case BasicType::vec3:
		return vec3;
	case BasicType::vec4:
		return vec4;
	case BasicType::bvec2:
		return bvec2;
	case BasicType::bvec3:
		return bvec3;
	case BasicType::bvec4:
		return bvec4;
	case BasicType::ivec2:
		return ivec2;
	case BasicType::ivec3:
		return ivec3;
	case BasicType::ivec4:
		return ivec4;
	case BasicType::uvec2:
		return uvec2;
	case BasicType::uvec3:
		return uvec3;
	case BasicType::uvec4:
		return uvec4;
	case BasicType::mat2:
		return mat2;
	case BasicType::mat3:
		return mat3;
	case BasicType::mat4:
		return mat4;
	case BasicType::mat2x2:
		return mat2x2;
	case BasicType::mat2x3:
		return mat2x3;
	case BasicType::mat2x4:
		return mat2x4;
	case BasicType::mat3x2:
		return mat3x2;
	case BasicType::mat3x3:
		return mat3x3;
	case BasicType::mat3x4:
		return mat3x4;
	case BasicType::mat4x2:
		return mat4x2;
	case BasicType::mat4x3:
		return mat4x3;
	case BasicType::mat4x4:
		return mat4x4;
	case BasicType::sampler1D:
		return sampler1D;
	case BasicType::sampler2D:
		return sampler2D;
	case BasicType::sampler3D:
		return sampler3D;
	case BasicType::samplerCube:
		return samplerCube;
	case BasicType::sampler1DShadow:
		return sampler1DShadow;
	case BasicType::sampler2DShadow:
		return sampler2DShadow;
	case BasicType::samplerCubeShadow:
		return samplerCubeShadow;
	case BasicType::sampler1DArray:
		return sampler1DArray;
	case BasicType::sampler2DArray:
		return sampler2DArray;
	case BasicType::sampler1DArrayShadow:
		return sampler1DArrayShadow;
	case BasicType::sampler2DArrayShadow:
		return sampler2DArrayShadow;
	case BasicType::isampler1D:
		return isampler1D;
	case BasicType::isampler2D:
		return isampler2D;
	case BasicType::isampler3D:
		return isampler3D;
	case BasicType::isamplerCube:
		return isamplerCube;
	case BasicType::isampler1DArray:
		return isampler1DArray;
	case BasicType::isampler2DArray:
		return isampler2DArray;
	case BasicType::usampler1D:
		return usampler1D;
	case BasicType::usampler2D:
		return usampler2D;
	case BasicType::usampler3D:
		return usampler3D;
	case BasicType::usamplerCube:
		return usamplerCube;
	case BasicType::usampler1DArray:
		return usampler1DArray;
	case BasicType::usampler2DArray:
		return usampler2DArray;
	case BasicType::sampler2DRect:
		return sampler2DRect;
	case BasicType::sampler2DRectShadow:
		return sampler2DRectShadow;
	case BasicType::isampler2DRect:
		return isampler2DRect;
	case BasicType::usampler2DRect:
		return usampler2DRect;
	case BasicType::samplerBuffer:
		return samplerBuffer;
	case BasicType::isamplerBuffer:
		return isamplerBuffer;
	case BasicType::usamplerBuffer:
		return usamplerBuffer;
	case BasicType::sampler2DMS:
		return sampler2DMS;
	case BasicType::isampler2DMS:
		return isampler2DMS;
	case BasicType::usampler2DMS:
		return usampler2DMS;
	case BasicType::sampler2DMSArray:
		return sampler2DMSArray;
	case BasicType::isampler2DMSArray:
		return isampler2DMSArray;
	case BasicType::usampler2DMSArray:
		return usampler2DMSArray;
	case BasicType::invalid:
	default:
		return invalid;
	}
}
