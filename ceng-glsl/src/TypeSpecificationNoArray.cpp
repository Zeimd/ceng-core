#include "TypeSpecifierNoArray.h"

using namespace Ceng;

void TypeSpecifierNoArray::Release()
{
	delete this;
}

TypeSpecifierNoArray::TypeSpecifierNoArray(TypeSpecifierNoArray::TypeSelector type)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), type(type)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(TokenType::value tokenType)
	: INonTerminal(NonTerminalType::type_specifier_nonarray)
{
	type = FromTokenType(tokenType);
}

TypeSpecifierNoArray::TypeSpecifierNoArray(const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), type(TypeSelector::typeName), name(name)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(std::shared_ptr<StructSpecifier>& structSpec)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), type(TypeSelector::struct_specifier), structSpec(structSpec)
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

#define CASE_TO_TEXT(x) case TypeSelector::x: return #x;

Ceng::StringUtf8 TypeSpecifierNoArray::ToString(unsigned int indentLevel) const
{
	switch (type)
	{
	case ts_void:
		return "void";
	case ts_float:
		return "float";
	case ts_int:
		return "int";
	case ts_uint:
		return "uint";
	case ts_bool:
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
		CASE_TO_TEXT(typeName);
		CASE_TO_TEXT(invalid);
	case struct_specifier:
		return structSpec->ToString(indentLevel);		
	default:
		return "TypeSpecifierNoArray::unhandled case";
	}
}

#undef CASE_TO_TEXT