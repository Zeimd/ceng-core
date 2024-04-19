#include "TypeSpecifierNoArray.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void TypeSpecifierNoArray::Release()
{
	delete this;
}

TypeSpecifierNoArray::TypeSpecifierNoArray(GLSL::BasicType::value basicType)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), dataType(TypeSelector::basic_type), basicType(basicType)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(TokenType::value tokenType)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), dataType(TypeSelector::basic_type)
{
	basicType = FromTokenType(tokenType);
}

TypeSpecifierNoArray::TypeSpecifierNoArray(const SymbolLink& link)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), dataType(TypeSelector::type_name), link(link)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(std::shared_ptr<StructSpecifier>& structSpec)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), dataType(TypeSelector::struct_specifier), structSpec(structSpec)
{

}

GLSL::BasicType::value TypeSpecifierNoArray::FromTokenType(TokenType::value tokenType)
{
	switch (tokenType)
	{
	case TokenType::keyword_void:
		return GLSL::BasicType::ts_void;
	case TokenType::type_bool:
		return GLSL::BasicType::ts_bool;
	case TokenType::type_bvec2:
		return GLSL::BasicType::bvec2;
	case TokenType::type_bvec3:
		return GLSL::BasicType::bvec3;
	case TokenType::type_bvec4:
		return GLSL::BasicType::bvec4;
	case TokenType::type_int:
		return GLSL::BasicType::ts_int;
	case TokenType::type_ivec2:
		return GLSL::BasicType::ivec2;
	case TokenType::type_ivec3:
		return GLSL::BasicType::ivec3;
	case TokenType::type_ivec4:
		return GLSL::BasicType::ivec4;
	case TokenType::type_uint:
		return GLSL::BasicType::ts_uint;
	case TokenType::type_uvec2:
		return GLSL::BasicType::uvec2;
	case TokenType::type_uvec3:
		return GLSL::BasicType::uvec3;
	case TokenType::type_uvec4:
		return GLSL::BasicType::uvec4;
	case TokenType::type_float:
		return GLSL::BasicType::ts_float;
	case TokenType::type_vec2:
		return GLSL::BasicType::vec2;
	case TokenType::type_vec3:
		return GLSL::BasicType::vec3;
	case TokenType::type_vec4:
		return GLSL::BasicType::vec4;
	case TokenType::type_isampler1D:
		return GLSL::BasicType::isampler1D;
	case TokenType::type_isampler1DArray:
		return GLSL::BasicType::isampler1DArray;
	case TokenType::type_isampler2D:
		return GLSL::BasicType::isampler2D;
	case TokenType::type_isampler2DArray:
		return GLSL::BasicType::isampler2DArray;
	case TokenType::type_isampler2DMS:
		return GLSL::BasicType::isampler2DMS;
	case TokenType::type_isampler2DMSArray:
		return GLSL::BasicType::isampler2DMSArray;
	case TokenType::type_isampler2DRect:
		return GLSL::BasicType::isampler2DRect;
	case TokenType::type_isampler3D:
		return GLSL::BasicType::isampler3D;
	case TokenType::type_isamplerCube:
		return GLSL::BasicType::isamplerCube;
	case TokenType::type_isamplerBuffer:
		return GLSL::BasicType::isamplerBuffer;
	case TokenType::type_sampler1D:
		return GLSL::BasicType::sampler1D;
	case TokenType::type_sampler1DArray:
		return GLSL::BasicType::sampler1DArray;
	case TokenType::type_sampler1DArrayShadow:
		return GLSL::BasicType::sampler1DArrayShadow;
	case TokenType::type_sampler1DShadow:
		return GLSL::BasicType::sampler1DShadow;
	case TokenType::type_sampler2D:
		return GLSL::BasicType::sampler2D;
	case TokenType::type_sampler2DArray:
		return GLSL::BasicType::sampler2DArray;
	case TokenType::type_sampler2DArrayShadow:
		return GLSL::BasicType::sampler2DArrayShadow;
	case TokenType::type_sampler2DMS:
		return GLSL::BasicType::sampler2DMS;
	case TokenType::type_sampler2DMSArray:
		return GLSL::BasicType::sampler2DMSArray;
	case TokenType::type_sampler2DRect:
		return GLSL::BasicType::sampler2DRect;
	case TokenType::type_sampler2DRectShadow:
		return GLSL::BasicType::sampler2DRectShadow;
	case TokenType::type_sampler2DShadow:
		return GLSL::BasicType::sampler2DShadow;
	case TokenType::type_sampler3D:
		return GLSL::BasicType::sampler3D;
	case TokenType::type_samplerCube:
		return GLSL::BasicType::samplerCube;
	case TokenType::type_samplerCubeShadow:
		return GLSL::BasicType::samplerCubeShadow;
	case TokenType::type_samplerBuffer:
		return GLSL::BasicType::samplerBuffer;
	case TokenType::type_usampler1D:
		return GLSL::BasicType::usampler1D;
	case TokenType::type_usampler1DArray:
		return GLSL::BasicType::usampler1DArray;
	case TokenType::type_usampler2D:
		return GLSL::BasicType::usampler2D;
	case TokenType::type_usampler2DArray:
		return GLSL::BasicType::usampler2DArray;
	case TokenType::type_usampler2DMS:
		return GLSL::BasicType::usampler2DMS;
	case TokenType::type_usampler2DMSArray:
		return GLSL::BasicType::usampler2DMSArray;
	case TokenType::type_usampler2DRect:
		return GLSL::BasicType::usampler2DRect;
	case TokenType::type_usampler3D:
		return GLSL::BasicType::usampler3D;
	case TokenType::type_usamplerCube:
		return GLSL::BasicType::usamplerCube;
	case TokenType::type_usamplerBuffer:
		return GLSL::BasicType::usamplerBuffer;
	};

	return GLSL::BasicType::invalid;
}

Ceng::StringUtf8 TypeSpecifierNoArray::ToString(unsigned int indentLevel) const
{
	switch (dataType)
	{
	case TypeSelector::type_name:
		return *link.Get()->Name();
	case TypeSelector::struct_specifier:
		return structSpec->ToString(indentLevel);		
	default:
		return GLSL::BasicType::ToString(basicType);
	}
}

void TypeSpecifierNoArray::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_TypeSpecifierNoArray(*this);
}

bool TypeSpecifierNoArray::IsIntegerType() const
{
	switch (dataType)
	{
	case TypeSelector::type_name:
	case TypeSelector::struct_specifier:
		return false;
	default:
		break;
	}

	switch(basicType)
	{
	case GLSL::BasicType::ts_int:
	case GLSL::BasicType::ts_uint:
		return true;
	default:
		return false;
	}
}