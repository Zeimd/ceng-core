#include <ceng/type-spec-no-arr.h>

using namespace Ceng;

TypeSpecifierNoArray::TypeSpecifierNoArray(TypeSpecifierNoArray::TypeSelector type)
	:type(type)
{

}

TypeSpecifierNoArray::TypeSelector TypeSpecifierNoArray::FromTokenType(TokenType::value tokenType)
{
	switch (tokenType)
	{
	case TokenType::type_bool:
		return TypeSelector::ts_bool;
	case TokenType::type_bvec2:
		return TypeSelector::bvec2;
	case TokenType::type_bvec3:
		return TypeSelector::bvec3;
	case TokenType::type_bvec4:
		return TypeSelector::bvec4;
	case TokenType::type_int:
		return TypeSelector::ts_int;
	case TokenType::type_ivec2:
		return TypeSelector::ivec2;
	case TokenType::type_ivec3:
		return TypeSelector::ivec3;
	case TokenType::type_ivec4:
		return TypeSelector::ivec4;
	case TokenType::type_uint:
		return TypeSelector::ts_uint;
	case TokenType::type_uvec2:
		return TypeSelector::uvec2;
	case TokenType::type_uvec3:
		return TypeSelector::uvec3;
	case TokenType::type_uvec4:
		return TypeSelector::uvec4;
	case TokenType::type_float:
		return TypeSelector::ts_float;
	case TokenType::type_vec2:
		return TypeSelector::vec2;
	case TokenType::type_vec3:
		return TypeSelector::vec3;
	case TokenType::type_vec4:
		return TypeSelector::vec4;
	case TokenType::type_isampler1d:
		return TypeSelector::isampler1D;
	case TokenType::type_isampler1d_array:
		return TypeSelector::isampler1DArray;
	case TokenType::type_isampler2d:
		return TypeSelector::isampler2D;
	case TokenType::type_isampler2d_array:
		return TypeSelector::isampler2DArray;
	case TokenType::type_isampler2d_ms:
		return TypeSelector::isampler2DMS;
	case TokenType::type_isampler2d_ms_array:
		return TypeSelector::isampler2DMSArray;
	case TokenType::type_isampler2d_rect:
		return TypeSelector::isampler2DRect;
	case TokenType::type_isampler3d:
		return TypeSelector::isampler3D;
	case TokenType::type_isamplercube:
		return TypeSelector::isamplerCube;
	case TokenType::type_isampler_buffer:
		return TypeSelector::isamplerBuffer;
	case TokenType::type_sampler1d:
		return TypeSelector::sampler1D;
	case TokenType::type_sampler1d_array:
		return TypeSelector::sampler1DArray;
	case TokenType::type_sampler1d_array_shadow:
		return TypeSelector::sampler1DArrayShadow;
	case TokenType::type_sampler1d_shadow:
		return TypeSelector::sampler1DShadow;
	case TokenType::type_sampler2d:
		return TypeSelector::sampler2D;
	case TokenType::type_sampler2d_array:
		return TypeSelector::sampler2DArray;
	case TokenType::type_sampler2d_array_shadow:
		return TypeSelector::sampler2DArrayShadow;
	case TokenType::type_sampler2d_ms:
		return TypeSelector::sampler2DMS;
	case TokenType::type_sampler2d_ms_array:
		return TypeSelector::sampler2DMSArray;
	case TokenType::type_sampler2d_rect:
		return TypeSelector::sampler2DRect;
	case TokenType::type_sampler2d_rect_shadow:
		return TypeSelector::sampler2DRectShadow;
	case TokenType::type_sampler2d_shadow:
		return TypeSelector::sampler2DShadow;
	case TokenType::type_sampler3d:
		return TypeSelector::sampler3D;
	case TokenType::type_samplercube:
		return TypeSelector::samplerCube;
	case TokenType::type_samplercube_shadow:
		return TypeSelector::samplerCubeShadow;
	case TokenType::type_sampler_buffer:
		return TypeSelector::samplerBuffer;
	case TokenType::type_usampler1d:
		return TypeSelector::usampler1D;
	case TokenType::type_usampler1d_array:
		return TypeSelector::usampler1DArray;
	case TokenType::type_usampler2d:
		return TypeSelector::usampler2D;
	case TokenType::type_usampler2d_array:
		return TypeSelector::usampler2DArray;
	case TokenType::type_usampler2d_ms:
		return TypeSelector::usampler2DMS;
	case TokenType::type_usampler2d_ms_array:
		return TypeSelector::usampler2DMSArray;
	case TokenType::type_usampler2d_rect:
		return TypeSelector::usampler2DRect;
	case TokenType::type_usampler3d:
		return TypeSelector::usampler3D;
	case TokenType::type_usamplercube:
		return TypeSelector::usamplerCube;
	case TokenType::type_usampler_buffer:
		return TypeSelector::usamplerBuffer;
	};

	return TypeSelector::invalid;
}

TypeSpecifierNoArray::TypeSpecifierNoArray(TokenType::value tokenType)
{
	type = FromTokenType(tokenType);
}

TypeSpecifierNoArray::TypeSpecifierNoArray(const Ceng::StringUtf8& name)
	:type(TypeSelector::typeName),name(name)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(std::unique_ptr<StructSpecifier>&& structSpec)
	:type(TypeSelector::struct_specifier),structSpec(std::move(structSpec))
{

}