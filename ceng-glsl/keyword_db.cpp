
#include "keyword_db.h"

std::unordered_map<const char*, Ceng::TokenType::value> keywords =
{
	{"attribute",TokenType::keyword_attribute},
	{"const",TokenType::keyword_const},
	{"break",TokenType::keyword_break},
	{"continue",TokenType::keyword_continue},
	{"do",TokenType::keyword_do},
	{"else",TokenType::keyword_else},
	{"for",TokenType::keyword_for},
	{"if",TokenType::keyword_if},
	{"discard",TokenType::keyword_discard},
	{"return",TokenType::keyword_return},
	{"switch",TokenType::keyword_switch},
	{"case",TokenType::keyword_case},
	{"struct",TokenType::keyword_struct},
	{"default",TokenType::keyword_default},
	{"void",TokenType::keyword_void},
	{"while",TokenType::keyword_while},
	{"centroid",TokenType::keyword_centroid},
	{"in",TokenType::keyword_in},
	{"out",TokenType::keyword_out},
	{"inout",TokenType::keyword_inout},
	{"uniform",TokenType::keyword_uniform},
	{"varying",TokenType::keyword_varying},
	{"noperspective",TokenType::keyword_noperspective},
	{"flat",TokenType::keyword_flat},
	{"smooth",TokenType::keyword_smooth},
	{"layout",TokenType::keyword_layout},
	{"invariant",TokenType::keyword_invariant},
	{"highp",TokenType::keyword_high_precision},
	{"mediump",TokenType::keyword_medium_precision},
	{"lowp",TokenType::keyword_low_precision},
	{"precision",TokenType::keyword_precision},

	{"bool",TokenType::type_bool},
	{"float",TokenType::type_float},
	{"int",TokenType::type_int},
	{"uint",TokenType::type_uint},

	{"bvec2",TokenType::type_bvec2},
	{"bvec3",TokenType::type_bvec3},
	{"bvec4",TokenType::type_bvec4},

	{"ivec2",TokenType::type_ivec2},
	{"ivec3",TokenType::type_ivec3},
	{"ivec4",TokenType::type_ivec4},

	{"uvec2",TokenType::type_uvec2},
	{"uvec3",TokenType::type_uvec3},
	{"uvec4",TokenType::type_uvec4},

	{"vec2",TokenType::type_vec2},
	{"vec3",TokenType::type_vec3},
	{"vec4",TokenType::type_vec4},

	{"mat2",TokenType::type_mat2},
	{"mat3",TokenType::type_mat3},
	{"mat4",TokenType::type_mat4},

	{"mat2x2",TokenType::type_mat2x2},
	{"mat2x3",TokenType::type_mat2x3},
	{"mat2x4",TokenType::type_mat2x4},
	{"mat3x2",TokenType::type_mat3x2},
	{"mat3x3",TokenType::type_mat3x3},
	{"mat3x4",TokenType::type_mat3x4},
	{"mat4x2",TokenType::type_mat4x2},
	{"mat4x3",TokenType::type_mat4x3},
	{"mat4x4",TokenType::type_mat4x4},

	{"sampler1D",TokenType::type_sampler1d},
	{"sampler2D",TokenType::type_sampler2d},
	{"sampler3D",TokenType::type_sampler3d},
	{"samplerCube",TokenType::type_samplerCube},

	{"sampler1DShadow",TokenType::type_sampler1d_shadow},
	{"sampler2DShadow",TokenType::type_sampler2d_shadow},
	{"samplerCubeShadow",TokenType::type_samplercube_shadow},

	{"sampler1DArray",TokenType::type_sampler1d_array},
	{"sampler2DArray",TokenType::type_sampler2d_array},

	{"sampler1DArrayShadow",TokenType::type_sampler1d_array_shadow},
	{"sampler2DArrayShadow",TokenType::type_sampler2d_array_shadow},

	{"isampler1D",TokenType::type_isampler1d},
	{"isampler2D",TokenType::type_isampler2d},
	{"isampler3D",TokenType::type_isampler3d},
	{"isamplerCube",TokenType::type_isamplerCube},

	{"isampler1DArray",TokenType::type_isampler1d_array},
	{"isampler2DArray",TokenType::type_isampler2d_array},

	{"usampler1D",TokenType::type_usampler1d},
	{"usampler2D",TokenType::type_usampler2d},
	{"usampler3D",TokenType::type_usampler3d},
	{"usamplerCube",TokenType::type_usamplerCube},

	{"usampler1DArray",TokenType::type_usampler1d_array},
	{"usampler2DArray",TokenType::type_usampler2d_array},

	{"sampler2DRect",TokenType::type_sampler2d_rect},
	{"sampler2DRectShadow",TokenType::type_sampler2d_rect_shadow},
	{"isampler2DRect",TokenType::type_isampler2d_rect },
	{"usampler2DRect",TokenType::type_usampler2d_rect },

	{"samplerBuffer",TokenType::type_sampler_buffer},
	{ "isamplerBuffer",TokenType::type_isampler_buffer },
	{ "usamplerBuffer",TokenType::type_usampler_buffer },

	{ "sampler2DMS",TokenType::type_sampler2d_ms },
	{ "isampler2DMS",TokenType::type_isampler2d_ms },
	{ "usampler2DMS",TokenType::type_usampler2d_ms },

	{ "sampler2DMSArray",TokenType::type_sampler2d_ms_array },
	{ "isampler2DMSArray",TokenType::type_isampler2d_ms_array },
	{ "usampler2DMSArray",TokenType::type_usampler2d_ms_array },
};