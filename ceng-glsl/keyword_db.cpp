
#include "keyword_db.h"

std::unordered_map<const char*, Ceng::TokenType::value> keywords =
{
	{"attribute",{TokenType::keyword_attribute,TokenCategory::undefined}},
	{"const",{TokenType::keyword_const,TokenCategory::undefined}},
	{"break",{TokenType::keyword_break,TokenCategory::undefined}},
	{"continue",{TokenType::keyword_continue,TokenCategory::undefined}},
	{"do",{TokenType::keyword_do,TokenCategory::undefined}},
	{"else",{TokenType::keyword_else,TokenCategory::undefined}},
	{"for",{TokenType::keyword_for,TokenCategory::undefined}},
	{"if",{TokenType::keyword_if,TokenCategory::undefined}},
	{"discard",{TokenType::keyword_discard,TokenCategory::undefined}},
	{"return",{TokenType::keyword_return,TokenCategory::undefined}},
	{"switch",{TokenType::keyword_switch,TokenCategory::undefined}},
	{"case",{TokenType::keyword_case,TokenCategory::undefined}},
	{"struct",{TokenType::keyword_struct,TokenCategory::undefined}},
	{"default",{TokenType::keyword_default,TokenCategory::undefined}},
	{"void",{TokenType::keyword_void,TokenCategory::undefined}},
	{"while",{TokenType::keyword_while,TokenCategory::undefined}},
	{"centroid",{TokenType::keyword_centroid,TokenCategory::undefined}},
	{"in",{TokenType::keyword_in,TokenCategory::undefined}},
	{"out",{TokenType::keyword_out,TokenCategory::undefined}},
	{"inout",{TokenType::keyword_inout,TokenCategory::undefined}},
	{"uniform",{TokenType::keyword_uniform,TokenCategory::undefined}},
	{"varying",{TokenType::keyword_varying,TokenCategory::undefined}},
	{"noperspective",{TokenType::keyword_noperspective,TokenCategory::undefined}},
	{"flat",{TokenType::keyword_flat,TokenCategory::undefined}},
	{"smooth",{TokenType::keyword_smooth,TokenCategory::undefined}},
	{"layout",{TokenType::keyword_layout,TokenCategory::undefined}},
	{"invariant",{TokenType::keyword_invariant,TokenCategory::undefined}},
	{"highp",{TokenType::keyword_high_precision,TokenCategory::undefined}},
	{"mediump",{TokenType::keyword_medium_precision,TokenCategory::undefined}},
	{"lowp",{TokenType::keyword_low_precision,TokenCategory::undefined}},
	{"precision",{TokenType::keyword_precision,TokenCategory::undefined}},

	{"bool",{TokenType::type_bool,TokenCategory::undefined}},
	{"float",{TokenType::type_float,TokenCategory::undefined}},
	{"int",{TokenType::type_int,TokenCategory::undefined}},
	{"uint",{TokenType::type_uint,TokenCategory::undefined}},

	{"bvec2",{TokenType::type_bvec2,TokenCategory::undefined}},
	{"bvec3",{TokenType::type_bvec3,TokenCategory::undefined}},
	{"bvec4",{TokenType::type_bvec4,TokenCategory::undefined}},

	{"ivec2",{TokenType::type_ivec2,TokenCategory::undefined}},
	{"ivec3",{TokenType::type_ivec3,TokenCategory::undefined}},
	{"ivec4",{TokenType::type_ivec4,TokenCategory::undefined}},

	{"uvec2",{TokenType::type_uvec2,TokenCategory::undefined}},
	{"uvec3",{TokenType::type_uvec3,TokenCategory::undefined}},
	{"uvec4",{TokenType::type_uvec4,TokenCategory::undefined}},

	{"vec2",{TokenType::type_vec2,TokenCategory::undefined}},
	{"vec3",{TokenType::type_vec3,TokenCategory::undefined}},
	{"vec4",{TokenType::type_vec4,TokenCategory::undefined}},

	{"mat2",{TokenType::type_mat2,TokenCategory::undefined}},
	{"mat3",{TokenType::type_mat3,TokenCategory::undefined}},
	{"mat4",{TokenType::type_mat4,TokenCategory::undefined}},

	{"mat2x2",{TokenType::type_mat2x2,TokenCategory::undefined}},
	{"mat2x3",{TokenType::type_mat2x3,TokenCategory::undefined}},
	{"mat2x4",{TokenType::type_mat2x4,TokenCategory::undefined}},
	{"mat3x2",{TokenType::type_mat3x2,TokenCategory::undefined}},
	{"mat3x3",{TokenType::type_mat3x3,TokenCategory::undefined}},
	{"mat3x4",{TokenType::type_mat3x4,TokenCategory::undefined}},
	{"mat4x2",{TokenType::type_mat4x2,TokenCategory::undefined}},
	{"mat4x3",{TokenType::type_mat4x3,TokenCategory::undefined}},
	{"mat4x4",{TokenType::type_mat4x4,TokenCategory::undefined}},

	{"sampler1D",{TokenType::type_sampler1d,TokenCategory::undefined}},
	{"sampler2D",{TokenType::type_sampler2d,TokenCategory::undefined}},
	{"sampler3D",{TokenType::type_sampler3d,TokenCategory::undefined}},
	{"samplerCube",{TokenType::type_samplerCube,TokenCategory::undefined}},

	{"sampler1DShadow",{TokenType::type_sampler1d_shadow,TokenCategory::undefined}},
	{"sampler2DShadow",{TokenType::type_sampler2d_shadow,TokenCategory::undefined}},
	{"samplerCubeShadow",{TokenType::type_samplercube_shadow,TokenCategory::undefined}},

	{"sampler1DArray",{TokenType::type_sampler1d_array,TokenCategory::undefined}},
	{"sampler2DArray",{TokenType::type_sampler2d_array,TokenCategory::undefined}},

	{"sampler1DArrayShadow",{TokenType::type_sampler1d_array_shadow,TokenCategory::undefined}},
	{"sampler2DArrayShadow",{TokenType::type_sampler2d_array_shadow,TokenCategory::undefined}},

	{"isampler1D",{TokenType::type_isampler1d,TokenCategory::undefined}},
	{"isampler2D",{TokenType::type_isampler2d,TokenCategory::undefined}},
	{"isampler3D",{TokenType::type_isampler3d,TokenCategory::undefined}},
	{"isamplerCube",{TokenType::type_isamplerCube,TokenCategory::undefined}},

	{"isampler1DArray",{TokenType::type_isampler1d_array,TokenCategory::undefined}},
	{"isampler2DArray",{TokenType::type_isampler2d_array,TokenCategory::undefined}},

	{"usampler1D",{TokenType::type_usampler1d,TokenCategory::undefined}},
	{"usampler2D",{TokenType::type_usampler2d,TokenCategory::undefined}},
	{"usampler3D",{TokenType::type_usampler3d,TokenCategory::undefined}},
	{"usamplerCube",{TokenType::type_usamplerCube,TokenCategory::undefined}},

	{"usampler1DArray",{TokenType::type_usampler1d_array,TokenCategory::undefined}},
	{"usampler2DArray",{TokenType::type_usampler2d_array,TokenCategory::undefined}},

	{"sampler2DRect",{TokenType::type_sampler2d_rect,TokenCategory::undefined}},
	{"sampler2DRectShadow",{TokenType::type_sampler2d_rect_shadow,TokenCategory::undefined} },
	{"isampler2DRect",{TokenType::type_isampler2d_rect,TokenCategory::undefined} },
	{"usampler2DRect",{TokenType::type_usampler2d_rect,TokenCategory::undefined} },

	{"samplerBuffer",{TokenType::type_sampler_buffer,TokenCategory::undefined} },
	{ "isamplerBuffer",{TokenType::type_isampler_buffer,TokenCategory::undefined} },
	{ "usamplerBuffer",{TokenType::type_usampler_buffer,TokenCategory::undefined} },

	{ "sampler2DMS",{TokenType::type_sampler2d_ms,TokenCategory::undefined} },
	{ "isampler2DMS",{TokenType::type_isampler2d_ms,TokenCategory::undefined} },
	{ "usampler2DMS",{TokenType::type_usampler2d_ms,TokenCategory::undefined} },

	{ "sampler2DMSArray",{TokenType::type_sampler2d_ms_array,TokenCategory::undefined} },
	{ "isampler2DMSArray",{TokenType::type_isampler2d_ms_array,TokenCategory::undefined} },
	{ "usampler2DMSArray",{TokenType::type_usampler2d_ms_array,TokenCategory::undefined} },
};