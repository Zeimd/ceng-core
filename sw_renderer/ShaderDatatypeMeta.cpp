#include "ShaderDatatypeMeta.h"

namespace Ceng
{
	/**
	 *  Size of each Ceng::SHADER_DATATYPE in bytes.
	 *
	 *  NOTE: Order must correspond to that of Ceng::SHADER_DATATYPE enumeration.
	 */
	const UINT32 CR_SHADER_DATA_TYPE_SIZE[] =
	{
		0 ,  // UNKNOWN

		4 , // FLOAT
		8 , // FLOAT2
		12 , // FLOAT3
		16 , // FLOAT4

		8 , // DOUBLE
		16 , // DOUBLE2
		24 , // DOUBLE3
		32 , // DOUBLE4

		4 , // UINT
		8 , // UINT2
		12 , // UINT3
		16 , // UINT4

		4 , // INT
		8 , // INT2
		12 , // INT3
		16 , // INT4

		4 , // BOOL
		8 , // BOOL2
		12 , // BOOL3
		16 , // BOOL4

		64 , // FLOAT4x4
		36 , // FLOAT3x3
		16 , // FLOAT2x2

		128 , // DOUBLE4x4
		72 , // DOUBLE3x3
		32 , // DOUBLE2x2

		64 , // UINT4x4
		36 , // UINT3x3
		16 , // UINT2x2

		64 , // INT4x4
		36 , // INT3x3
		16 , // INT2x2

		64 , // BOOL4x4
		36 , // BOOL3x3
		16 , // BOOL2x2

		4 , // sampler1d
		4 , // sampler2d
		4 , // sampler3d

		4, // samplerCube
	};

	const UINT32 CR_SHADER_DATA_TYPE_ALIGNMENT[] =
	{
		0 ,  // UNKNOWN

		4 , // FLOAT
		8 , // FLOAT2
		16 , // FLOAT3
		16 , // FLOAT4

		8 , // DOUBLE
		16 , // DOUBLE2
		32 , // DOUBLE3
		32 , // DOUBLE4

		4 , // UINT
		8 , // UINT2
		16 , // UINT3
		16 , // UINT4

		4 , // INT
		8 , // INT2
		16 , // INT3
		16 , // INT4

		4 , // BOOL
		8 , // BOOL2
		16 , // BOOL3
		16 , // BOOL4

		16 , // FLOAT4x4
		16 , // FLOAT3x3
		16 , // FLOAT2x2

		32 , // DOUBLE4x4
		32 , // DOUBLE3x3
		32 , // DOUBLE2x2

		16 , // UINT4x4
		16 , // UINT3x3
		16 , // UINT2x2

		16 , // INT4x4
		16 , // INT3x3
		16 , // INT2x2

		16 , // BOOL4x4
		16 , // BOOL3x3
		16 , // BOOL2x2

		4 , // sampler1d
		4 , // sampler2d
		4 , // sampler3d

		4, // samplerCube
	};

	// Is the shader datatype valid as pixel shader input
	const Ceng::BOOL CR_PSHADER_VALID_INPUT_TYPE[] =
	{
		false ,  // UNKNOWN

		true , // FLOAT
		true , // FLOAT2
		true , // FLOAT3
		true , // FLOAT4

		true , // DOUBLE
		true , // DOUBLE2
		true , // DOUBLE3
		true , // DOUBLE4

		true , // UINT
		true , // UINT2
		true , // UINT3
		true , // UINT4

		true , // INT
		true , // INT2
		true , // INT3
		true , // INT4

		false , // BOOL
		false , // BOOL2
		false , // BOOL3
		false , // BOOL4

		true , // FLOAT4x4
		true , // FLOAT3x3
		true , // FLOAT2x2

		true , // DOUBLE4x4
		true , // DOUBLE3x3
		true , // DOUBLE2x2

		true , // UINT4x4
		true , // UINT3x3
		true , // UINT2x2

		true , // INT4x4
		true , // INT3x3
		true , // INT2x2

		false , // BOOL4x4
		false , // BOOL3x3
		false , // BOOL2x2

		false , // sampler1d
		false , // sampler2d
		false , // sampler3d

		false, // samplerCube
	};

	// Is the shader datatype valid as pixel shader input
	const Ceng::BOOL CR_SHADER_VALID_UNIFORM_TYPE[] =
	{
		false ,  // UNKNOWN

		true , // FLOAT
		true , // FLOAT2
		true , // FLOAT3
		true , // FLOAT4

		true , // DOUBLE
		true , // DOUBLE2
		true , // DOUBLE3
		true , // DOUBLE4

		true , // UINT
		true , // UINT2
		true , // UINT3
		true , // UINT4

		true , // INT
		true , // INT2
		true , // INT3
		true , // INT4

		true , // BOOL
		true , // BOOL2
		true , // BOOL3
		true , // BOOL4

		true , // FLOAT4x4
		true , // FLOAT3x3
		true , // FLOAT2x2

		true , // DOUBLE4x4
		true , // DOUBLE3x3
		true , // DOUBLE2x2

		true , // UINT4x4
		true , // UINT3x3
		true , // UINT2x2

		true , // INT4x4
		true , // INT3x3
		true , // INT2x2

		true , // BOOL4x4
		true , // BOOL3x3
		true , // BOOL2x2

		true , // sampler1d
		true , // sampler2d
		true , // sampler3d

		true, // samplerCube
	};

	// Indicates the datatype the uniform has in the uniform buffer (and to the client).
	// This is mainly used by sampler types.
	const SHADER_DATATYPE::value CR_SHADER_UNIFORM_EFFECTIVE_TYPE[] =
	{
		SHADER_DATATYPE::UNKNOWN ,  // UNKNOWN

		SHADER_DATATYPE::FLOAT , // FLOAT
		SHADER_DATATYPE::FLOAT2 , // FLOAT2
		SHADER_DATATYPE::FLOAT3 , // FLOAT3
		SHADER_DATATYPE::FLOAT4 , // FLOAT4

		SHADER_DATATYPE::DOUBLE , // DOUBLE
		SHADER_DATATYPE::DOUBLE2 , // DOUBLE2
		SHADER_DATATYPE::DOUBLE3 , // DOUBLE3
		SHADER_DATATYPE::DOUBLE4 , // DOUBLE4

		SHADER_DATATYPE::UINT , // UINT
		SHADER_DATATYPE::UINT2 , // UINT2
		SHADER_DATATYPE::UINT3 , // UINT3
		SHADER_DATATYPE::UINT4 , // UINT4

		SHADER_DATATYPE::INT , // INT
		SHADER_DATATYPE::INT2 , // INT2
		SHADER_DATATYPE::INT3 , // INT3
		SHADER_DATATYPE::INT4 , // INT4

		SHADER_DATATYPE::BOOL , // BOOL
		SHADER_DATATYPE::BOOL2 , // BOOL2
		SHADER_DATATYPE::BOOL3 , // BOOL3
		SHADER_DATATYPE::BOOL4 , // BOOL4

		SHADER_DATATYPE::FLOAT4x4 , // FLOAT4x4
		SHADER_DATATYPE::FLOAT3x3 , // FLOAT3x3
		SHADER_DATATYPE::FLOAT2x2 , // FLOAT2x2

		SHADER_DATATYPE::DOUBLE4x4 , // DOUBLE4x4
		SHADER_DATATYPE::DOUBLE3x3 , // DOUBLE3x3
		SHADER_DATATYPE::DOUBLE2x2 , // DOUBLE2x2

		SHADER_DATATYPE::UINT4x4 , // UINT4x4
		SHADER_DATATYPE::UINT3x3 , // UINT3x3
		SHADER_DATATYPE::UINT2x2 , // UINT2x2

		SHADER_DATATYPE::INT4x4 , // INT4x4
		SHADER_DATATYPE::INT3x3 , // INT3x3
		SHADER_DATATYPE::INT2x2 , // INT2x2

		SHADER_DATATYPE::BOOL4x4 , // BOOL4x4
		SHADER_DATATYPE::BOOL3x3 , // BOOL3x3
		SHADER_DATATYPE::BOOL2x2 , // BOOL2x2

		SHADER_DATATYPE::UINT , // sampler1d
		SHADER_DATATYPE::UINT , // sampler2d
		SHADER_DATATYPE::UINT , // sampler3d

		SHADER_DATATYPE::UINT , // samplerCube
	};

	// For debug purposes
	const char* CR_SHADER_DATA_TYPE_NAME[] =
	{
		"SHADER_DATATYPE::UNKNOWN" ,  // UNKNOWN

		"SHADER_DATATYPE::FLOAT" , // FLOAT
		"SHADER_DATATYPE::FLOAT2" , // FLOAT2
		"SHADER_DATATYPE::FLOAT3" , // FLOAT3
		"SHADER_DATATYPE::FLOAT4" , // FLOAT4

		"SHADER_DATATYPE::DOUBLE" , // DOUBLE
		"SHADER_DATATYPE::DOUBLE2" , // DOUBLE2
		"SHADER_DATATYPE::DOUBLE3" , // DOUBLE3
		"SHADER_DATATYPE::DOUBLE4" , // DOUBLE4

		"SHADER_DATATYPE::UINT" , // UINT
		"SHADER_DATATYPE::UINT2" , // UINT2
		"SHADER_DATATYPE::UINT3" , // UINT3
		"SHADER_DATATYPE::UINT4" , // UINT4

		"SHADER_DATATYPE::INT" , // INT
		"SHADER_DATATYPE::INT2" , // INT2
		"SHADER_DATATYPE::INT3" , // INT3
		"SHADER_DATATYPE::INT4" , // INT4

		"SHADER_DATATYPE::BOOL" , // BOOL
		"SHADER_DATATYPE::BOOL2" , // BOOL2
		"SHADER_DATATYPE::BOOL3" , // BOOL3
		"SHADER_DATATYPE::BOOL4" , // BOOL4

		"SHADER_DATATYPE::FLOAT4x4" , // FLOAT4x4
		"SHADER_DATATYPE::FLOAT3x3" , // FLOAT3x3
		"SHADER_DATATYPE::FLOAT2x2" , // FLOAT2x2

		"SHADER_DATATYPE::DOUBLE4x4" , // DOUBLE4x4
		"SHADER_DATATYPE::DOUBLE3x3" , // DOUBLE3x3
		"SHADER_DATATYPE::DOUBLE2x2" , // DOUBLE2x2

		"SHADER_DATATYPE::UINT4x4" , // UINT4x4
		"SHADER_DATATYPE::UINT3x3" , // UINT3x3
		"SHADER_DATATYPE::UINT2x2" , // UINT2x2

		"SHADER_DATATYPE::INT4x4" , // INT4x4
		"SHADER_DATATYPE::INT3x3" , // INT3x3
		"SHADER_DATATYPE::INT2x2" , // INT2x2

		"SHADER_DATATYPE::BOOL4x4" , // BOOL4x4
		"SHADER_DATATYPE::BOOL3x3" , // BOOL3x3
		"SHADER_DATATYPE::BOOL2x2" , // BOOL2x2

		"SHADER_DATATYPE::sampler1d" , // sampler1d
		"SHADER_DATATYPE::sampler2d" , // sampler2d
		"SHADER_DATATYPE::sampler3d" , // sampler3d

		"SHADER_DATATYPE::samplerCube" , // samplerCube
	};
}

