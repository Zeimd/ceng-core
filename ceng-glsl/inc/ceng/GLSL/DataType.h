#ifndef CENG_GLSL_DATATYPE_H
#define CENG_GLSL_DATATYPE_H

namespace Ceng
{
	namespace GLSL
	{
		namespace DataType
		{
			enum value
			{
				ts_void,
				ts_float,
				ts_int,
				ts_uint,
				ts_bool,
				vec2,
				vec3,
				vec4,
				bvec2,
				bvec3,
				bvec4,
				ivec2,
				ivec3,
				ivec4,
				uvec2,
				uvec3,
				uvec4,
				mat2,
				mat3,
				mat4,
				mat2x2,
				mat2x3,
				mat2x4,
				mat3x2,
				mat3x3,
				mat3x4,
				mat4x2,
				mat4x3,
				mat4x4,
				sampler1D,
				sampler2D,
				sampler3D,
				samplerCube,
				sampler1DShadow,
				sampler2DShadow,
				samplerCubeShadow,
				sampler1DArray,
				sampler2DArray,
				sampler1DArrayShadow,
				sampler2DArrayShadow,
				isampler1D,
				isampler2D,
				isampler3D,
				isamplerCube,
				isampler1DArray,
				isampler2DArray,
				usampler1D,
				usampler2D,
				usampler3D,
				usamplerCube,
				usampler1DArray,
				usampler2DArray,
				sampler2DRect,
				sampler2DRectShadow,
				isampler2DRect,
				usampler2DRect,
				samplerBuffer,
				isamplerBuffer,
				usamplerBuffer,
				sampler2DMS,
				isampler2DMS,
				usampler2DMS,
				sampler2DMSArray,
				isampler2DMSArray,
				usampler2DMSArray,
				struct_specifier,
				type_name,
				invalid,
			};

			const char* ToString(DataType::value type);
		}
	}
}

#endif