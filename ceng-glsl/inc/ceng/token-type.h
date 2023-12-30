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

			field_selection,
			left_op,
			right_op,
			inc_op,
			dec_op,
			
			le_op,
			ge_op,
			eq_op,
			ne_op,

			and_op,
			or_op,
			xor_op,
			
			// *=
			mul_assign,

			// /=
			div_assign,

			// +=
			add_assign,

			// %=
			mod_assign,

			// TBC
			left_assign,

			// TBC
			right_assign,

			// &=
			and_assign,

			// ^=
			xor_assign,

			// |=
			or_assign,

			// -=
			sub_assign,

			// Char: (
			left_paren,

			// Char: )
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

			type_sampler1d,
			type_sampler2d,
			type_sampler3d,
			type_samplercube,
			type_sampler1d_shadow,
			type_sampler2d_shadow,
			type_samplercube_shadow,
			type_sampler1d_array,
			type_sampler2d_array,
			type_sampler1d_array_shadow,
			type_sampler2d_array_shadow,
			type_isampler1d,
			type_isampler2d,
			type_isampler3d,
			type_isamplercube,
			type_isampler1d_array,
			type_isampler2d_array,
			type_usampler1d,
			type_usampler2d,
			type_usampler3d,
			type_usamplercube,
			type_usampler1d_array,
			type_usampler2d_array,
			type_sampler2d_rect,
			type_sampler2d_rect_shadow,
			type_isampler2d_rect,
			type_usampler2d_rect,
			type_sampler_buffer,
			type_isampler_buffer,
			type_usampler_buffer,
			type_sampler2d_ms,
			type_isampler2d_ms,
			type_usampler2d_ms,
			type_sampler2d_ms_array,
			type_isampler2d_ms_array,
			type_usampler2d_ms_array,
		};
	}
}

#endif