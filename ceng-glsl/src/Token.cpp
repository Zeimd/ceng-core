#include <ceng/GLSL/Token.h>

using namespace Ceng;

Token::Token() : type(TokenType::meta_uninitialized)
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category)
	: position(file,line,position),leftSpace(leftSpace),rightSpace(rightSpace),startLine(startLine),endLine(endLine),
		type(type), category(category)
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const Ceng::StringUtf8& name)
	: position(file, line, position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), category(category), name(name)
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const Ceng::StringUtf8& name, bool value)
	: position(file, line, position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), category(category), name(name)
{
	this->value.boolVal = value;
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const Ceng::StringUtf8& name, Ceng::UINT32 value)
	: position(file, line, position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), category(category), name(name)
{
	this->value.intVal = value;
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const Ceng::StringUtf8& name, Ceng::FLOAT32 value)
	: position(file, line, position), leftSpace(leftSpace), rightSpace(rightSpace), startLine(startLine), endLine(endLine),
	type(type), category(category), name(name)
{
	this->value.floatVal = value;
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const char* name)
	: Token(file, line, position, leftSpace, rightSpace, startLine, endLine, type, category, Ceng::StringUtf8(name))
{

}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const char* name, bool value)
	: Token(file, line, position, leftSpace, rightSpace, startLine, endLine, type, category, Ceng::StringUtf8(name), value)
{
	
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const char* name, Ceng::UINT32 value)
	: Token(file, line, position, leftSpace, rightSpace, startLine, endLine, type, category, Ceng::StringUtf8(name), value)
{
	
}

Token::Token(const std::shared_ptr<const Ceng::StringUtf8>& file, const Ceng::UINT32 line, const Ceng::UINT32 position,
	bool leftSpace, bool rightSpace, bool startLine, bool endLine, Ceng::TokenType::value type, Ceng::TokenCategory::value category,
	const char* name, Ceng::FLOAT32 value)
	: Token(file,line,position,leftSpace,rightSpace,startLine,endLine,type, category,Ceng::StringUtf8(name),value)
{
	
}

Ceng::StringUtf8 Token::ToString() const
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
	case TokenType::inc_op:
		return "++";
	case TokenType::dec_op:
		return "--";
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
	case TokenType::type_isampler1D:
		return "isampler1D";
	case TokenType::type_isampler1DArray:
		return "isampler1DArray";
	case TokenType::type_isampler2D:
		return "isampler2D";
	case TokenType::type_isampler2DArray:
		return "isampler2DArray";
	case TokenType::type_isampler2DMS:
		return "isampler2DMS";
	case TokenType::type_isampler2DMSArray:
		return "isampler2DMSArray";
	case TokenType::type_isampler2DRect:
		return "isampler2DRect";
	case TokenType::type_isampler3D:
		return "isampler3D";
	case TokenType::type_isamplerCube:
		return "isamplerCube";
	case TokenType::type_isamplerBuffer:
		return "isamplerBuffer";
	case TokenType::type_sampler1D:
		return "sampler1D";
	case TokenType::type_sampler1DArray:
		return "sampler1Darray";
	case TokenType::type_sampler1DArrayShadow:
		return "sampler1DArrayShadow";
	case TokenType::type_sampler1DShadow:
		return "sampler1DShadow";
	case TokenType::type_sampler2D:
		return "sampler2D";
	case TokenType::type_sampler2DArray:
		return "sampler2DArray";
	case TokenType::type_sampler2DArrayShadow:
		return "sampler2DArrayShadow";
	case TokenType::type_sampler2DMS:
		return "sampler2DMS";
	case TokenType::type_sampler2DMSArray:
		return "sampler2DMSArray";
	case TokenType::type_sampler2DRect:
		return "sampler2DRect";
	case TokenType::type_sampler2DRectShadow:
		return "sampler2DRectShadow";
	case TokenType::type_sampler2DShadow:
		return "sampler2DShadow";
	case TokenType::type_sampler3D:
		return "sampler3D";
	case TokenType::type_samplerCube:
		return "samplerCube";
	case TokenType::type_samplerCubeShadow:
		return "samplerCubeShadow";
	case TokenType::type_samplerBuffer:
		return "samplerBuffer";
	case TokenType::type_usampler1D:
		return "usampler1D";
	case TokenType::type_usampler1DArray:
		return "usampler1DArray";
	case TokenType::type_usampler2D:
		return "usampler2D";
	case TokenType::type_usampler2DArray:
		return "usampler2DArray";
	case TokenType::type_usampler2DMS :
		return "usampler2DMS";
	case TokenType::type_usampler2DMSArray:
		return "usampler2DMSArray";
	case TokenType::type_usampler2DRect:
		return "usampler2DRect";
	case TokenType::type_usampler3D:
		return "usampler3D";
	case TokenType::type_usamplerCube:
		return "usamplerCube";
	case TokenType::type_usamplerBuffer:
		return "usamplerBuffer";
	case TokenType::type_name:
		return name;
	case TokenType::identifier:
		return name;
	case TokenType::bool_constant:
		if (value.boolVal)
		{
			return "true";
		}
		else
		{
			return "false";
		}
		break;
	case TokenType::int_constant:
		return value.intVal;
	case TokenType::float_constant:
		return value.floatVal;
	case TokenType::meta_end_of_line:
		return '\n';
	case TokenType::meta_end_of_file:
		return "<EOF>";
	case TokenType::preprocess_comment:
		return "//";
	case TokenType::preprocess_comment_start:
		return "/*";
	case TokenType::preprocess_comment_end:
		return "*/";
	case TokenType::preprocess_hash:
	case TokenType::preprocess_stringize:
		return "#";
	case TokenType::preprocess_concatenate_op:
		return "##";
	case TokenType::meta_uninitialized:
		return "<< token type uninitialized >>";
	default:
		return "<< unhandled token type >>";
	};
}

Ceng::StringUtf8 Token::ToDiagnosticString() const
{
	Ceng::StringUtf8 text;

	text += '@';
	text += position.line;
	text += ':';
	text += position.column;
	text += '@';

	if (leftSpace)
	{
		text += '\\';
	}
	if (startLine)
	{
		text += '\"';
	}

	switch (type)
	{
	case TokenType::keyword_attribute:
		text += "attribute";
		break;
	case TokenType::keyword_const:
		text += "const";
		break;
	case TokenType::keyword_break:
		text += "break";
		break;
	case TokenType::keyword_continue:
		text += "continue";
		break;
	case TokenType::keyword_do:
		text += "do";
		break;
	case TokenType::keyword_centroid:
		text += "centroid";
		break;
	case TokenType::keyword_case:
		text += "case";
		break;
	case TokenType::keyword_default:
		text += "default";
		break;
	case TokenType::keyword_discard:
		text += "discard";
		break;
	case TokenType::keyword_else:
		text += "else";
		break;
	case TokenType::keyword_flat:
		text += "flat";
		break;
	case TokenType::keyword_for:
		text += "for";
		break;
	case TokenType::keyword_high_precision:
		text += "highp";
		break;
	case TokenType::keyword_medium_precision:
		text += "mediump";
		break;
	case TokenType::keyword_low_precision:
		text += "lowp";
		break;
	case TokenType::keyword_if:
		text += "if";
		break;
	case TokenType::keyword_in:
		text += "in"; 
		break;
	case TokenType::keyword_inout:
		text += "inout";
		break;
	case TokenType::keyword_invariant:
		text += "invariant";
		break;
	case TokenType::keyword_layout:
		text += "layout";
		break;
	case TokenType::keyword_noperspective:
		text += "noperspective";
		break;
	case TokenType::keyword_out:
		text += "out";
		break;
	case TokenType::keyword_precision:
		text += "precision";
		break;
	case TokenType::keyword_return:
		text += "return";
		break;
	case TokenType::keyword_smooth:
		text += "smooth";
		break;
	case TokenType::keyword_struct:
		text += "struct";
		break;
	case TokenType::keyword_switch:
		text += "switch";
		break;
	case TokenType::keyword_uniform:
		text += "uniform";
		break;
	case TokenType::keyword_varying:
		text += "varying";
		break;
	case TokenType::keyword_void:
		text += "void";
		break;
	case TokenType::keyword_while:
		text += "while";
		break;
	case TokenType::ampersand:
		text += "&";
		break;
	case TokenType::equal:
		text += "=";
		break;
	case TokenType::left_angle:
		text += "<";
		break;
	case TokenType::right_angle:
		text += ">";
		break;
	case TokenType::left_paren:
		text += "(";
		break;
	case TokenType::right_paren:
		text += ")";
		break;
	case TokenType::left_brace:
		text += "{";
		break;
	case TokenType::right_brace:
		text += "}";
		break;
	case TokenType::left_bracket:
		text += "[";
		break;
	case TokenType::right_bracket:
		text += "]";
		break;
	case TokenType::bang:
		text += "!";
		break;
	case TokenType::caret:
		text += "^";
		break;
	case TokenType::colon:
		text += ":";
		break;
	case TokenType::semicolon:
		text += ";";
		break;
	case TokenType::dot:
		text += ".";
		break;
	case TokenType::comma:
		text += ",";
		break;
	case TokenType::vertical_bar:
		text += "|";
		break;
	case TokenType::left_op:
		text += "<<";
		break;
	case TokenType::right_op:
		text += ">>";
		break;
	case TokenType::le_op:
		text += "<=";
		break;
	case TokenType::ge_op:
		text += ">=";
		break;
	case TokenType::eq_op:
		text += "==";
		break;
	case TokenType::ne_op:
		text += "!=";
		break;
	case TokenType::and_op:
		text += "&&";
		break;
	case TokenType::or_op:
		text += "||";
		break;
	case TokenType::xor_op:
		text += "^^";
		break;
	case TokenType::plus:
		text += "+";
		break;
	case TokenType::slash:
		text += "/";
		break;
	case TokenType::star:
		text += "*";
		break;
	case TokenType::dash:
		text += "-";
		break;
	case TokenType::tilde:
		text += "~";
		break;
	case TokenType::field_selection:
		text += "?:";
		break;
	case TokenType::add_assign:
		text += "+=";
		break;
	case TokenType::sub_assign:
		text += "-=";
		break;
	case TokenType::div_assign:
		text += "/=";
		break;
	case TokenType::mod_assign:
		text += "%=";
		break;
	case TokenType::and_assign:
		text += "&=";
		break;
	case TokenType::or_assign:
		text += "|=";
		break;
	case TokenType::xor_assign:
		text += "^=";
		break;
	case TokenType::mul_assign:
		text += "*=";
		break;
	case TokenType::left_assign:
		text += "<<=";
		break;
	case TokenType::right_assign:
		text += ">>=";
		break;
	case TokenType::percent:
		text += "%";
		break;
	case TokenType::question:
		text += "?";
		break;
	case TokenType::type_bool:
		text += "bool";
		break;
	case TokenType::type_bvec2:
		text += "bvec2";
		break;
	case TokenType::type_bvec3:
		text += "bvec3";
		break;
	case TokenType::type_bvec4:
		text += "bvec4";
		break;
	case TokenType::type_int:
		text += "int";
		break;
	case TokenType::type_ivec2:
		text += "ivec2";
		break;
	case TokenType::type_ivec3:
		text += "ivec3";
		break;
	case TokenType::type_ivec4:
		text += "ivec4";
		break;
	case TokenType::type_uint:
		text += "uint";
		break;
	case TokenType::type_uvec2:
		text += "uvec2";
		break;
	case TokenType::type_uvec3:
		text += "uvec3";
		break;
	case TokenType::type_uvec4:
		text += "uvec4";
		break;
	case TokenType::type_float:
		text += "float";
		break;
	case TokenType::type_vec2:
		text += "vec2";
		break;
	case TokenType::type_vec3:
		text += "vec3";
		break;
	case TokenType::type_vec4:
		text += "vec4";
		break;
	case TokenType::type_isampler1D:
		text += "isampler1D";
		break;
	case TokenType::type_isampler1DArray:
		text += "isampler1DArray";
		break;
	case TokenType::type_isampler2D:
		text += "isampler2D";
		break;
	case TokenType::type_isampler2DArray:
		text += "isampler2DArray";
		break;
	case TokenType::type_isampler2DMS:
		text += "isampler2DMS";
		break;
	case TokenType::type_isampler2DMSArray:
		text += "isampler2DMSArray";
		break;
	case TokenType::type_isampler2DRect:
		text += "isampler2DRect";
		break;
	case TokenType::type_isampler3D:
		text += "isampler3D";
		break;
	case TokenType::type_isamplerCube:
		text += "isamplerCube";
		break;
	case TokenType::type_isamplerBuffer:
		text += "isamplerBuffer";
		break;
	case TokenType::type_sampler1D:
		text += "sampler1D";
		break;
	case TokenType::type_sampler1DArray:
		text += "sampler1Darray";
		break;
	case TokenType::type_sampler1DArrayShadow:
		text += "sampler1DArrayShadow";
		break;
	case TokenType::type_sampler1DShadow:
		text += "sampler1DShadow";
		break;
	case TokenType::type_sampler2D:
		text += "sampler2D";
		break;
	case TokenType::type_sampler2DArray:
		text += "sampler2DArray";
		break;
	case TokenType::type_sampler2DArrayShadow:
		text += "sampler2DArrayShadow";
		break;
	case TokenType::type_sampler2DMS:
		text += "sampler2DMS";
		break;
	case TokenType::type_sampler2DMSArray:
		text += "sampler2DMSArray";
		break;
	case TokenType::type_sampler2DRect:
		text += "sampler2DRect";
		break;
	case TokenType::type_sampler2DRectShadow:
		text += "sampler2DRectShadow";
		break;
	case TokenType::type_sampler2DShadow:
		text += "sampler2DShadow";
		break;
	case TokenType::type_sampler3D:
		text += "sampler3D";
		break;
	case TokenType::type_samplerCube:
		text += "samplerCube";
		break;
	case TokenType::type_samplerCubeShadow:
		text += "samplerCubeShadow";
		break;
	case TokenType::type_samplerBuffer:
		text += "samplerBuffer";
		break;
	case TokenType::type_usampler1D:
		text += "usampler1D";
		break;
	case TokenType::type_usampler1DArray:
		text += "usampler1DArray";
		break;
	case TokenType::type_usampler2D:
		text += "usampler2D";
		break;
	case TokenType::type_usampler2DArray:
		text += "usampler2DArray";
		break;
	case TokenType::type_usampler2DMS:
		text += "usampler2DMS";
		break;
	case TokenType::type_usampler2DRect:
		text += "usampler2DRect";
		break;
	case TokenType::type_usampler3D:
		text += "usampler3D";
		break;
	case TokenType::type_usamplerCube:
		text += "usamplerCube";
		break;
	case TokenType::type_usamplerBuffer:
		text += "usamplerBuffer";
		break;
	case TokenType::type_name:
		text += "typename:";
		text += name;
		break;
	case TokenType::identifier:
		text += "id:";
		text += name;
		break;
	case TokenType::bool_constant:
		if (value.boolVal)
		{
			text += "true";
		}
		else
		{
			text += "false";
		}
		break;
	case TokenType::int_constant:
		text += value.intVal;
		break;
	case TokenType::float_constant:
		text += value.floatVal;
		break;
	case TokenType::meta_end_of_line:
		text += '\\n';
		break;
	case TokenType::meta_end_of_file:
		text += "<EOF>";
		break;
	case TokenType::preprocess_comment:
		text += "//";
		break;
	case TokenType::preprocess_comment_start:
		text += "/*";
		break;
	case TokenType::preprocess_comment_end:
		text += "*/";
		break;
	case TokenType::preprocess_hash:
	case TokenType::preprocess_stringize:
		text += "#";
		break;
	case TokenType::preprocess_concatenate_op:
		text += "##";
		break;
	case TokenType::meta_uninitialized:
		text += "<< token type uninitialized >>";
		break;
	default:
		text += "<< unhandled token type >>";
		break;
	};

	if (rightSpace)
	{
		text += '\\';
	}
	if (endLine)
	{
		text += '$';
	}

	return text;
}
