/*****************************************************************************
*
* gl32-uniform-float3.cpp
*
* Created By Jari Korkala 25/10/2015
*
*
*****************************************************************************/

#include "../inc/gl32-uniform-float3.h"

using namespace Ceng;

GL32_UniformFloat3::GL32_UniformFloat3() : GL32_ShaderConstant()
{
	values[0] = 0.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
}

GL32_UniformFloat3::GL32_UniformFloat3(GLint index, Ceng::GL32_ShaderProgram *program) : GL32_ShaderConstant(index, program)
{
	values[0] = 0.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
}

GL32_UniformFloat3::~GL32_UniformFloat3()
{
}

void GL32_UniformFloat3::Release()
{
	delete this;
}

const CRESULT GL32_UniformFloat3::SetFloat(const Ceng::FLOAT32 value)
{
	values[0] = value;
	values[1] = 0.0f;
	values[2] = 0.0f;
	
	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetFloat2(const Ceng::FLOAT32 *source)
{
	values[0] = source[0];
	values[1] = source[1];
	values[2] = 0.0f;

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetFloat3(const Ceng::FLOAT32 *source)
{
	values[0] = source[0];
	values[1] = source[1];
	values[2] = source[2];

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetFloat4(const Ceng::FLOAT32 *source)
{
	values[0] = source[0];
	values[1] = source[1];
	values[2] = source[2];

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetInt(const Ceng::INT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetInt2(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetInt3(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetInt4(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetBool2(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetBool3(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetBool4(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat3::SetMatrix_4x4(const Ceng::FLOAT32 *source, const Ceng::BOOL transpose)
{
	return CE_OK;
}

void GL32_UniformFloat3::GL_UpdateThis()
{
	glUniform3fv(index, 1, values);
}