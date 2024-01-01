
#include "keyword_db.h"

std::unordered_map<const char*, Ceng::TokenType::value> keywords =
{
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

	{"attribute",{TokenType::keyword_attribute,TokenCategory::qualifier}},
	{"const",{TokenType::keyword_const,TokenCategory::qualifier}},
	{"centroid",{TokenType::keyword_centroid,TokenCategory::qualifier}},
	{"in",{TokenType::keyword_in,TokenCategory::qualifier}},
	{"out",{TokenType::keyword_out,TokenCategory::qualifier}},
	{"inout",{TokenType::keyword_inout,TokenCategory::qualifier}},
	{"uniform",{TokenType::keyword_uniform,TokenCategory::qualifier}},
	{"varying",{TokenType::keyword_varying,TokenCategory::qualifier}},
	{"noperspective",{TokenType::keyword_noperspective,TokenCategory::qualifier}},
	{"flat",{TokenType::keyword_flat,TokenCategory::qualifier}},
	{"smooth",{TokenType::keyword_smooth,TokenCategory::qualifier}},
	{"layout",{TokenType::keyword_layout,TokenCategory::qualifier}},
	{"invariant",{TokenType::keyword_invariant,TokenCategory::qualifier}},
	{"highp",{TokenType::keyword_high_precision,TokenCategory::qualifier}},
	{"mediump",{TokenType::keyword_medium_precision,TokenCategory::qualifier}},
	{"lowp",{TokenType::keyword_low_precision,TokenCategory::qualifier}},
	{"precision",{TokenType::keyword_precision,TokenCategory::qualifier}},

	{"bool",{TokenType::type_bool,TokenCategory::data_type}},
	{"float",{TokenType::type_float,TokenCategory::data_type}},
	{"int",{TokenType::type_int,TokenCategory::data_type}},
	{"uint",{TokenType::type_uint,TokenCategory::data_type}},

	{"bvec2",{TokenType::type_bvec2,TokenCategory::data_type}},
	{"bvec3",{TokenType::type_bvec3,TokenCategory::data_type}},
	{"bvec4",{TokenType::type_bvec4,TokenCategory::data_type}},

	{"ivec2",{TokenType::type_ivec2,TokenCategory::data_type}},
	{"ivec3",{TokenType::type_ivec3,TokenCategory::data_type}},
	{"ivec4",{TokenType::type_ivec4,TokenCategory::data_type}},

	{"uvec2",{TokenType::type_uvec2,TokenCategory::data_type}},
	{"uvec3",{TokenType::type_uvec3,TokenCategory::data_type}},
	{"uvec4",{TokenType::type_uvec4,TokenCategory::data_type}},

	{"vec2",{TokenType::type_vec2,TokenCategory::data_type}},
	{"vec3",{TokenType::type_vec3,TokenCategory::data_type}},
	{"vec4",{TokenType::type_vec4,TokenCategory::data_type}},

	{"mat2",{TokenType::type_mat2,TokenCategory::data_type}},
	{"mat3",{TokenType::type_mat3,TokenCategory::data_type}},
	{"mat4",{TokenType::type_mat4,TokenCategory::data_type}},

	{"mat2x2",{TokenType::type_mat2x2,TokenCategory::data_type}},
	{"mat2x3",{TokenType::type_mat2x3,TokenCategory::data_type}},
	{"mat2x4",{TokenType::type_mat2x4,TokenCategory::data_type}},
	{"mat3x2",{TokenType::type_mat3x2,TokenCategory::data_type}},
	{"mat3x3",{TokenType::type_mat3x3,TokenCategory::data_type}},
	{"mat3x4",{TokenType::type_mat3x4,TokenCategory::data_type}},
	{"mat4x2",{TokenType::type_mat4x2,TokenCategory::data_type}},
	{"mat4x3",{TokenType::type_mat4x3,TokenCategory::data_type}},
	{"mat4x4",{TokenType::type_mat4x4,TokenCategory::data_type}},

	{"sampler1D",{TokenType::type_sampler1d,TokenCategory::data_type}},
	{"sampler2D",{TokenType::type_sampler2d,TokenCategory::data_type}},
	{"sampler3D",{TokenType::type_sampler3d,TokenCategory::data_type}},
	{"samplerCube",{TokenType::type_samplerCube,TokenCategory::data_type}},

	{"sampler1DShadow",{TokenType::type_sampler1d_shadow,TokenCategory::data_type}},
	{"sampler2DShadow",{TokenType::type_sampler2d_shadow,TokenCategory::data_type}},
	{"samplerCubeShadow",{TokenType::type_samplercube_shadow,TokenCategory::data_type}},

	{"sampler1DArray",{TokenType::type_sampler1d_array,TokenCategory::data_type}},
	{"sampler2DArray",{TokenType::type_sampler2d_array,TokenCategory::data_type}},

	{"sampler1DArrayShadow",{TokenType::type_sampler1d_array_shadow,TokenCategory::data_type}},
	{"sampler2DArrayShadow",{TokenType::type_sampler2d_array_shadow,TokenCategory::data_type}},

	{"isampler1D",{TokenType::type_isampler1d,TokenCategory::data_type}},
	{"isampler2D",{TokenType::type_isampler2d,TokenCategory::data_type}},
	{"isampler3D",{TokenType::type_isampler3d,TokenCategory::data_type}},
	{"isamplerCube",{TokenType::type_isamplerCube,TokenCategory::data_type}},

	{"isampler1DArray",{TokenType::type_isampler1d_array,TokenCategory::data_type}},
	{"isampler2DArray",{TokenType::type_isampler2d_array,TokenCategory::data_type}},

	{"usampler1D",{TokenType::type_usampler1d,TokenCategory::data_type}},
	{"usampler2D",{TokenType::type_usampler2d,TokenCategory::data_type}},
	{"usampler3D",{TokenType::type_usampler3d,TokenCategory::data_type}},
	{"usamplerCube",{TokenType::type_usamplerCube,TokenCategory::data_type}},

	{"usampler1DArray",{TokenType::type_usampler1d_array,TokenCategory::data_type}},
	{"usampler2DArray",{TokenType::type_usampler2d_array,TokenCategory::data_type}},

	{"sampler2DRect",{TokenType::type_sampler2d_rect,TokenCategory::data_type}},
	{"sampler2DRectShadow",{TokenType::type_sampler2d_rect_shadow,TokenCategory::data_type} },
	{"isampler2DRect",{TokenType::type_isampler2d_rect,TokenCategory::data_type} },
	{"usampler2DRect",{TokenType::type_usampler2d_rect,TokenCategory::data_type} },

	{"samplerBuffer",{TokenType::type_sampler_buffer,TokenCategory::data_type} },
	{ "isamplerBuffer",{TokenType::type_isampler_buffer,TokenCategory::data_type} },
	{ "usamplerBuffer",{TokenType::type_usampler_buffer,TokenCategory::data_type} },

	{ "sampler2DMS",{TokenType::type_sampler2d_ms,TokenCategory::data_type} },
	{ "isampler2DMS",{TokenType::type_isampler2d_ms,TokenCategory::data_type} },
	{ "usampler2DMS",{TokenType::type_usampler2d_ms,TokenCategory::data_type} },

	{ "sampler2DMSArray",{TokenType::type_sampler2d_ms_array,TokenCategory::data_type} },
	{ "isampler2DMSArray",{TokenType::type_isampler2d_ms_array,TokenCategory::data_type} },
	{ "usampler2DMSArray",{TokenType::type_usampler2d_ms_array,TokenCategory::data_type} },
};