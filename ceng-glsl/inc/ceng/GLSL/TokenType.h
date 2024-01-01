#ifndef CENG_GLSL_TOKEN_TYPE_H
#define CENG_GLSL_TOKEN_TYPE_H

namespace Ceng
{
	namespace TokenType
	{
		enum value
		{
			meta_end_of_line,
			meta_end_of_file,
			meta_uninitialized,
			meta_whitespace,

			preprocess_hash,
			preprocess_stringize,
			preprocess_concatenate_op,
			preprocess_comment,
			preprocess_comment_start,
			preprocess_comment_end,

			keyword_attribute,
			keyword_const,

			keyword_break,
			keyword_continue,
			keyword_do,
			keyword_else,
			keyword_for,
			keyword_if,
			keyword_discard,
			keyword_return,
			keyword_switch,
			keyword_case,
			keyword_default,
			keyword_struct,
			keyword_void,
			keyword_while,
			keyword_centroid,
			keyword_in,
			keyword_out,
			keyword_inout,
			keyword_uniform,
			keyword_varying,
			keyword_noperspective,
			keyword_flat,
			keyword_smooth,
			keyword_layout,
			keyword_invariant,
			keyword_high_precision,
			keyword_medium_precision,
			keyword_low_precision,
			keyword_precision,

			identifier,
			type_name,
			
			float_constant,
			int_constant,
			uint_constant,
			bool_constant,

			// ?:
			field_selection,

			// Left shift <<
			left_op,

			// Right shift >>
			right_op,

			// Increment ++
			inc_op,

			// Decrement --
			dec_op,
			
			// <=
			le_op,

			// >=
			ge_op,

			// ==
			eq_op,

			// !=
			ne_op,

			// &&
			and_op,

			// ||
			or_op,

			// ^^
			xor_op,
			
			// *=
			mul_assign,

			// /=
			div_assign,

			// +=
			add_assign,

			// %=
			mod_assign,

			// <<=
			left_assign,

			// >>=
			right_assign,

			// &=
			and_assign,

			// ^=
			xor_assign,

			// |=
			or_assign,

			// -=
			sub_assign,

			// (
			left_paren,

			// )
			right_paren,

			// [
			left_bracket,

			// ]
			right_bracket,

			// {
			left_brace,

			// }
			right_brace,

			// .
			dot,

			// ,
			comma,

			// :
			colon,

			// =
			equal,

			// ;
			semicolon,

			// !
			bang,

			// -
			dash,

			// ~
			tilde,

			// +
			plus,

			// *
			star,

			// /
			slash,

			// %
			percent,

			// <
			left_angle,

			// >
			right_angle,

			// |
			vertical_bar,

			// ^
			caret,

			// &
			ampersand,

			// ?
			question,


			type_bool,
			type_float,
			type_int,
			type_uint,
			
			type_bvec2,
			type_bvec3,
			type_bvec4,

			type_ivec2,
			type_ivec3,
			type_ivec4,

			type_uvec2,
			type_uvec3,
			type_uvec4,

			type_vec2,
			type_vec3,
			type_vec4,

			type_mat2,
			type_mat3,
			type_mat4,

			type_mat2x2,
			type_mat2x3,
			type_mat2x4,
			type_mat3x2,
			type_mat3x3,
			type_mat3x4,
			type_mat4x2,
			type_mat4x3,
			type_mat4x4,

			type_sampler1D,
			type_sampler2D,
			type_sampler3D,
			type_samplerCube,
			type_sampler1DShadow,
			type_sampler2DShadow,
			type_samplerCubeShadow,
			type_sampler1DArray,
			type_sampler2DArray,
			type_sampler1DArrayShadow,
			type_sampler2DArrayShadow,
			type_isampler1D,
			type_isampler2D,
			type_isampler3D,
			type_isamplerCube,
			type_isampler1DArray,
			type_isampler2DArray,
			type_usampler1D,
			type_usampler2D,
			type_usampler3D,
			type_usamplerCube,
			type_usampler1DArray,
			type_usampler2DArray,
			type_sampler2DRect,
			type_sampler2DRectShadow,
			type_isampler2DRect,
			type_usampler2DRect,
			type_samplerBuffer,
			type_isamplerBuffer,
			type_usamplerBuffer,
			type_sampler2DMS,
			type_isampler2DMS,
			type_usampler2DMS,
			type_sampler2DMSArray,
			type_isampler2DMSArray,
			type_usampler2DMSArray,
		};
	}
}

#endif