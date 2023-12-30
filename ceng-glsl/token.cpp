#include <ceng/token.h>

using namespace Ceng;

Token::Token() : type(TokenType::meta_uninitialized)
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type)
	: file(file),line(line),position(position),leftSpace(leftSpace),rightSpace(rightSpace),startLine(startLine),endLine(endLine),
		type(type)
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const Ceng::StringUtf8& name)
	: file(file), line(line), position(position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), name(name)
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const Ceng::StringUtf8& name, bool value)
	: file(file), line(line), position(position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), name(name)
{
	Ceng::UINT32* x = (Ceng::UINT32*)&literalData[0];

	*x = 0;

	if (value)
	{
		*x = 1;
	}
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const Ceng::StringUtf8& name, Ceng::UINT32 value)
	: file(file), line(line), position(position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), name(name)
{
	
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const Ceng::StringUtf8& name, Ceng::FLOAT32 value)
	: file(file), line(line), position(position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), name(name)
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const char* name)
	: Token(file, line, position, leftSpace, rightSpace, startLine, endLine, type, Ceng::StringUtf8(name))
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const char* name, bool value)
	: Token(file, line, position, leftSpace, rightSpace, startLine, endLine, type, Ceng::StringUtf8(name), value)
{
	SetBool(value);
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const char* name, Ceng::UINT32 value)
	: Token(file, line, position, leftSpace, rightSpace, startLine, endLine, type, Ceng::StringUtf8(name), value)
{
	SetInt(value);
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type,
	const char* name, Ceng::FLOAT32 value)
	: Token(file,line,position,leftSpace,rightSpace,startLine,endLine,type,Ceng::StringUtf8(name),value)
{
	SetFloat(value);
}

void Token::SetBool(bool value)
{
	Ceng::UINT32* x = (Ceng::UINT32*)&literalData[0];

	*x = 0;

	if (value)
	{
		*x = 1;
	}
}

void Token::SetInt(Ceng::INT32 value)
{
	Ceng::UINT32* x = (Ceng::UINT32*)&literalData[0];

	*x = value;
}

void Token::SetFloat(Ceng::FLOAT32 value)
{
	Ceng::FLOAT32* x = (Ceng::FLOAT32*)&literalData[0];

	*x = value;
}


Ceng::StringUtf8 Token::ToString()
{
	switch (type)
	{
	case TokenType::keyword_attribute:
		return "attribute";
	case TokenType::keyword_const:
		return "const";
	case TokenType::keyword_break:
		return "break";
	case TokenType::keyword_continue:
		return "continue";
	case TokenType::keyword_do:
		return "do";
	case TokenType::keyword_centroid:
		return "centroid";
	case TokenType::keyword_case:
		return "case";
	case TokenType::keyword_default:
		return "default";
	case TokenType::keyword_discard:
		return "discard";
	case TokenType::keyword_else:
		return "else";
	case TokenType::keyword_flat:
		return "flat";
	case TokenType::keyword_for:
		return "for";
	case TokenType::keyword_high_precision:
		return "highp";
	case TokenType::keyword_medium_precision:
		return "mediump";
	case TokenType::keyword_low_precision:
		return "lowp";
	case TokenType::keyword_if:
		return "if";
	case TokenType::keyword_in:
		return "in";
	case TokenType::keyword_inout:
		return "inout";
	case TokenType::keyword_invariant:
		return "invariant";
	case TokenType::keyword_layout:
		return "layout";
	case TokenType::keyword_noperspective:
		return "noperspective";
	case TokenType::keyword_out:
		return "out";
	case TokenType::keyword_precision:
		return "precision";
	case TokenType::keyword_return:
		return "return";
	case TokenType::keyword_smooth:
		return "smooth";
	case TokenType::keyword_struct:
		return "struct";
	case TokenType::keyword_switch:
		return "switch";
	case TokenType::keyword_uniform:
		return "uniform";
	case TokenType::keyword_varying:
		return "varying";
	case TokenType::keyword_void:
		return "void";
	case TokenType::keyword_while:
		return "while";
	case TokenType::ampersand:
		return "&";
	case TokenType::equal:
		return "=";
	case TokenType::left_angle:
		return "<";
	case TokenType::right_angle:
		return ">";
	case TokenType::left_paren:
		return "(";
	case TokenType::right_paren:
		return ")";
	case TokenType::left_brace:
		return "{";
	case TokenType::right_brace:
		return "}";
	case TokenType::left_bracket:
		return "[";
	case TokenType::right_bracket:
		return "]";
	case TokenType::bang:
		return "!";
	case TokenType::caret:
		return "^";
	case TokenType::colon:
		return ":";
	case TokenType::semicolon:
		return ";";
	case TokenType::dot:
		return ".";
	case TokenType::comma:
		return ",";
	case TokenType::vertical_bar:
		return "|";
	case TokenType::left_op:
		return "<<";
	case TokenType::right_op:
		return ">>";
	case TokenType::le_op:
		return "<=";
	case TokenType::ge_op:
		return ">=";
	case TokenType::eq_op:
		return "==";
	case TokenType::ne_op:
		return "!=";
	case TokenType::and_op:
		return "&&";
	case TokenType::or_op:
		return "||";
	case TokenType::xor_op:
		return "^^";
	case TokenType::plus:
		return "+";
	case TokenType::slash:
		return "/";
	case TokenType::star:
		return "*";
	case TokenType::dash:
		return "-";
	case TokenType::tilde:
		return "~";
	case TokenType::field_selection:
		return "?:";
	case TokenType::add_assign:
		return "+=";
	case TokenType::sub_assign:
		return "-=";
	case TokenType::div_assign:
		return "/=";
	case TokenType::mod_assign:
		return "%=";
	case TokenType::and_assign:
		return "&=";
	case TokenType::or_assign:
		return "|=";
	case TokenType::xor_assign:
		return "^=";
	case TokenType::mul_assign:
		return "*=";
	case TokenType::left_assign:
		return "<<=";
	case TokenType::right_assign:
		return ">>=";
	case TokenType::percent:
		return "%";
	case TokenType::question:
		return "?";
	case TokenType::type_bool:
		return "bool";
	case TokenType::type_bvec2:
		return "bvec2";
	case TokenType::type_bvec3:
		return "bvec3";
	case TokenType::type_bvec4:
		return "bvec4";
	case TokenType::type_int:
		return "int";
	case TokenType::type_ivec2:
		return "ivec2";
	case TokenType::type_ivec3:
		return "ivec3";
	case TokenType::type_ivec4:
		return "ivec4";
	case TokenType::type_uint:
		return "uint";
	case TokenType::type_uvec2:
		return "uvec2";
	case TokenType::type_uvec3:
		return "uvec3";
	case TokenType::type_uvec4:
		return "uvec4";
	case TokenType::type_float:
		return "float";
	case TokenType::type_vec2:
		return "vec2";
	case TokenType::type_vec3:
		return "vec3";
	case TokenType::type_vec4:
		return "vec4";
	case TokenType::type_isampler1d:
		return "isampler1D";
	case TokenType::type_isampler1d_array:
		return "isampler1DArray";
	case TokenType::type_isampler2d:
		return "isampler2D";
	case TokenType::type_isampler2d_array:
		return "isampler2DArray";
	case TokenType::type_isampler2d_ms:
		return "isampler2DMS";
	case TokenType::type_isampler2d_ms_array:
		return "isampler2DMSArray";
	case TokenType::type_isampler2d_rect:
		return "isampler2DRect";
	case TokenType::type_isampler3d:
		return "isampler3D";
	case TokenType::type_isamplercube:
		return "isamplerCube";
	case TokenType::type_isampler_buffer:
		return "isamplerBuffer";
	case TokenType::type_sampler1d:
		return "sampler1D";
	case TokenType::type_sampler1d_array:
		return "sampler1Darray";
	case TokenType::type_sampler1d_array_shadow:
		return "sampler1DArrayShadow";
	case TokenType::type_sampler1d_shadow:
		return "sampler1DShadow";
	case TokenType::type_sampler2d:
		return "sampler2D";
	case TokenType::type_sampler2d_array:
		return "sampler2DArray";
	case TokenType::type_sampler2d_array_shadow:
		return "sampler2DArrayShadow";
	case TokenType::type_sampler2d_ms:
		return "sampler2DMS";
	case TokenType::type_sampler2d_ms_array:
		return "sampler2DMSArray";
	case TokenType::type_sampler2d_rect:
		return "sampler2DRect";
	case TokenType::type_sampler2d_rect_shadow:
		return "sampler2DRectShadow";
	case TokenType::type_sampler2d_shadow:
		return "sampler2DShadow";
	case TokenType::type_sampler3d:
		return "sampler3D";
	case TokenType::type_samplercube:
		return "samplerCube";
	case TokenType::type_samplercube_shadow:
		return "samplerCubeShadow";
	case TokenType::type_sampler_buffer:
		return "samplerBuffer";
	case TokenType::type_usampler1d:
		return "usampler1D";
	case TokenType::type_usampler1d_array:
		return "usampler1DArray";
	case TokenType::type_usampler2d:
		return "usampler2D";
	case TokenType::type_usampler2d_array:
		return "usampler2DArray";
	case TokenType::type_usampler2d_ms:
		return "usampler2DMS";
	case TokenType::type_usampler2d_ms_array:
		return "usampler2DMSArray";
	case TokenType::type_usampler2d_rect:
		return "usampler2DRect";
	case TokenType::type_usampler3d:
		return "usampler3D";
	case TokenType::type_usamplercube:
		return "usamplerCube";
	case TokenType::type_usampler_buffer:
		return "usamplerBuffer";
	case TokenType::type_name:
		return name;
	case TokenType::identifier:
		return name;
	case TokenType::bool_constant:
		{
			Ceng::UINT32* boolValue = (Ceng::UINT32*)&literalData[0];

			if (*boolValue == 0)
			{
				return "false";
			}
			else
			{
				return "true";
			}
		}

		break;
	case TokenType::int_constant:
		{
			Ceng::UINT32* intValue = (Ceng::UINT32*)&literalData[0];

			return *intValue;
		}
	case TokenType::float_constant:
		{
			Ceng::FLOAT32* floatValue = (Ceng::FLOAT32*)&literalData[0];

			return *floatValue;
		}
	case TokenType::meta_end_of_line:
		return '\n';
	case TokenType::meta_end_of_file:
		return "\n";
	case TokenType::preprocess_comment:
		return "//";
	case TokenType::preprocess_comment_start:
		return "/*";
	case TokenType::preprocess_comment_end:
		return "*/";
	case TokenType::meta_uninitialized:
		return "<< token type uninitialized >>";
	default:
		return "<< unhandled token type >>";
	};
}
