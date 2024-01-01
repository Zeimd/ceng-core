#include "TypeSpecifierNoArray.h"

using namespace Ceng;

/*
TypeSpecifierNoArray::TypeSpecifierNoArray(const TypeSpecifierNoArray& other)
	: type(other.type),structSpec(other.structSpec),name(other.name)
{

}
*/

TypeSpecifierNoArray::TypeSpecifierNoArray(TypeSpecifierNoArray::TypeSelector type)
	:type(type)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(TokenType::value tokenType)
{
	type = FromTokenType(tokenType);
}

TypeSpecifierNoArray::TypeSpecifierNoArray(const Ceng::StringUtf8& name)
	:type(TypeSelector::typeName), name(name)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(const StructSpecifier& structSpec)
	: type(TypeSelector::struct_specifier), structSpec(std::move(structSpec))
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
	case TokenType::type_isampler1D:
		return TypeSelector::isampler1D;
	case TokenType::type_isampler1DArray:
		return TypeSelector::isampler1DArray;
	case TokenType::type_isampler2D:
		return TypeSelector::isampler2D;
	case TokenType::type_isampler2DArray:
		return TypeSelector::isampler2DArray;
	case TokenType::type_isampler2DMS:
		return TypeSelector::isampler2DMS;
	case TokenType::type_isampler2DMSArray:
		return TypeSelector::isampler2DMSArray;
	case TokenType::type_isampler2DRect:
		return TypeSelector::isampler2DRect;
	case TokenType::type_isampler3D:
		return TypeSelector::isampler3D;
	case TokenType::type_isamplerCube:
		return TypeSelector::isamplerCube;
	case TokenType::type_isamplerBuffer:
		return TypeSelector::isamplerBuffer;
	case TokenType::type_sampler1D:
		return TypeSelector::sampler1D;
	case TokenType::type_sampler1DArray:
		return TypeSelector::sampler1DArray;
	case TokenType::type_sampler1DArrayShadow:
		return TypeSelector::sampler1DArrayShadow;
	case TokenType::type_sampler1DShadow:
		return TypeSelector::sampler1DShadow;
	case TokenType::type_sampler2D:
		return TypeSelector::sampler2D;
	case TokenType::type_sampler2DArray:
		return TypeSelector::sampler2DArray;
	case TokenType::type_sampler2DArrayShadow:
		return TypeSelector::sampler2DArrayShadow;
	case TokenType::type_sampler2DMS:
		return TypeSelector::sampler2DMS;
	case TokenType::type_sampler2DMSArray:
		return TypeSelector::sampler2DMSArray;
	case TokenType::type_sampler2DRect:
		return TypeSelector::sampler2DRect;
	case TokenType::type_sampler2DRectShadow:
		return TypeSelector::sampler2DRectShadow;
	case TokenType::type_sampler2DShadow:
		return TypeSelector::sampler2DShadow;
	case TokenType::type_sampler3D:
		return TypeSelector::sampler3D;
	case TokenType::type_samplerCube:
		return TypeSelector::samplerCube;
	case TokenType::type_samplerCubeShadow:
		return TypeSelector::samplerCubeShadow;
	case TokenType::type_samplerBuffer:
		return TypeSelector::samplerBuffer;
	case TokenType::type_usampler1D:
		return TypeSelector::usampler1D;
	case TokenType::type_usampler1DArray:
		return TypeSelector::usampler1DArray;
	case TokenType::type_usampler2D:
		return TypeSelector::usampler2D;
	case TokenType::type_usampler2DArray:
		return TypeSelector::usampler2DArray;
	case TokenType::type_usampler2DMS:
		return TypeSelector::usampler2DMS;
	case TokenType::type_usampler2DMSArray:
		return TypeSelector::usampler2DMSArray;
	case TokenType::type_usampler2DRect:
		return TypeSelector::usampler2DRect;
	case TokenType::type_usampler3D:
		return TypeSelector::usampler3D;
	case TokenType::type_usamplerCube:
		return TypeSelector::usamplerCube;
	case TokenType::type_usamplerBuffer:
		return TypeSelector::usamplerBuffer;
	};

	return TypeSelector::invalid;
}

