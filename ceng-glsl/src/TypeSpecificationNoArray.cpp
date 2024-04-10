#include "TypeSpecifierNoArray.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void TypeSpecifierNoArray::Release()
{
	delete this;
}

TypeSpecifierNoArray::TypeSpecifierNoArray(GLSL::DataType::value datatype)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), datatype(datatype)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(TokenType::value tokenType)
	: INonTerminal(NonTerminalType::type_specifier_nonarray)
{
	datatype = FromTokenType(tokenType);
}

TypeSpecifierNoArray::TypeSpecifierNoArray(const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), datatype(GLSL::DataType::type_name), name(name)
{

}

TypeSpecifierNoArray::TypeSpecifierNoArray(std::shared_ptr<StructSpecifier>& structSpec)
	: INonTerminal(NonTerminalType::type_specifier_nonarray), datatype(GLSL::DataType::struct_specifier), structSpec(structSpec)
{

}

GLSL::DataType::value TypeSpecifierNoArray::FromTokenType(TokenType::value tokenType)
{
	switch (tokenType)
	{
	case TokenType::keyword_void:
		return GLSL::DataType::ts_void;
	case TokenType::type_bool:
		return GLSL::DataType::ts_bool;
	case TokenType::type_bvec2:
		return GLSL::DataType::bvec2;
	case TokenType::type_bvec3:
		return GLSL::DataType::bvec3;
	case TokenType::type_bvec4:
		return GLSL::DataType::bvec4;
	case TokenType::type_int:
		return GLSL::DataType::ts_int;
	case TokenType::type_ivec2:
		return GLSL::DataType::ivec2;
	case TokenType::type_ivec3:
		return GLSL::DataType::ivec3;
	case TokenType::type_ivec4:
		return GLSL::DataType::ivec4;
	case TokenType::type_uint:
		return GLSL::DataType::ts_uint;
	case TokenType::type_uvec2:
		return GLSL::DataType::uvec2;
	case TokenType::type_uvec3:
		return GLSL::DataType::uvec3;
	case TokenType::type_uvec4:
		return GLSL::DataType::uvec4;
	case TokenType::type_float:
		return GLSL::DataType::ts_float;
	case TokenType::type_vec2:
		return GLSL::DataType::vec2;
	case TokenType::type_vec3:
		return GLSL::DataType::vec3;
	case TokenType::type_vec4:
		return GLSL::DataType::vec4;
	case TokenType::type_isampler1D:
		return GLSL::DataType::isampler1D;
	case TokenType::type_isampler1DArray:
		return GLSL::DataType::isampler1DArray;
	case TokenType::type_isampler2D:
		return GLSL::DataType::isampler2D;
	case TokenType::type_isampler2DArray:
		return GLSL::DataType::isampler2DArray;
	case TokenType::type_isampler2DMS:
		return GLSL::DataType::isampler2DMS;
	case TokenType::type_isampler2DMSArray:
		return GLSL::DataType::isampler2DMSArray;
	case TokenType::type_isampler2DRect:
		return GLSL::DataType::isampler2DRect;
	case TokenType::type_isampler3D:
		return GLSL::DataType::isampler3D;
	case TokenType::type_isamplerCube:
		return GLSL::DataType::isamplerCube;
	case TokenType::type_isamplerBuffer:
		return GLSL::DataType::isamplerBuffer;
	case TokenType::type_sampler1D:
		return GLSL::DataType::sampler1D;
	case TokenType::type_sampler1DArray:
		return GLSL::DataType::sampler1DArray;
	case TokenType::type_sampler1DArrayShadow:
		return GLSL::DataType::sampler1DArrayShadow;
	case TokenType::type_sampler1DShadow:
		return GLSL::DataType::sampler1DShadow;
	case TokenType::type_sampler2D:
		return GLSL::DataType::sampler2D;
	case TokenType::type_sampler2DArray:
		return GLSL::DataType::sampler2DArray;
	case TokenType::type_sampler2DArrayShadow:
		return GLSL::DataType::sampler2DArrayShadow;
	case TokenType::type_sampler2DMS:
		return GLSL::DataType::sampler2DMS;
	case TokenType::type_sampler2DMSArray:
		return GLSL::DataType::sampler2DMSArray;
	case TokenType::type_sampler2DRect:
		return GLSL::DataType::sampler2DRect;
	case TokenType::type_sampler2DRectShadow:
		return GLSL::DataType::sampler2DRectShadow;
	case TokenType::type_sampler2DShadow:
		return GLSL::DataType::sampler2DShadow;
	case TokenType::type_sampler3D:
		return GLSL::DataType::sampler3D;
	case TokenType::type_samplerCube:
		return GLSL::DataType::samplerCube;
	case TokenType::type_samplerCubeShadow:
		return GLSL::DataType::samplerCubeShadow;
	case TokenType::type_samplerBuffer:
		return GLSL::DataType::samplerBuffer;
	case TokenType::type_usampler1D:
		return GLSL::DataType::usampler1D;
	case TokenType::type_usampler1DArray:
		return GLSL::DataType::usampler1DArray;
	case TokenType::type_usampler2D:
		return GLSL::DataType::usampler2D;
	case TokenType::type_usampler2DArray:
		return GLSL::DataType::usampler2DArray;
	case TokenType::type_usampler2DMS:
		return GLSL::DataType::usampler2DMS;
	case TokenType::type_usampler2DMSArray:
		return GLSL::DataType::usampler2DMSArray;
	case TokenType::type_usampler2DRect:
		return GLSL::DataType::usampler2DRect;
	case TokenType::type_usampler3D:
		return GLSL::DataType::usampler3D;
	case TokenType::type_usamplerCube:
		return GLSL::DataType::usamplerCube;
	case TokenType::type_usamplerBuffer:
		return GLSL::DataType::usamplerBuffer;
	};

	return GLSL::DataType::invalid;
}

Ceng::StringUtf8 TypeSpecifierNoArray::ToString(unsigned int indentLevel) const
{
	switch (datatype)
	{
	case GLSL::DataType::type_name:
		return name;
	case GLSL::DataType::struct_specifier:
		return structSpec->ToString(indentLevel);		
	default:
		return GLSL::DataType::ToString(datatype);
	}
}

void TypeSpecifierNoArray::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_TypeSpecifierNoArray(*this);
}

bool TypeSpecifierNoArray::IsIntegerType() const
{
	switch (datatype)
	{
	case GLSL::DataType::ts_int:
	case GLSL::DataType::ts_uint:
		return true;
	default:
		return false;
	}
}