/*****************************************************************************
*
* gl32-uniform-float4.cpp
*
* Created By Jari Korkala 25/10/2015
*
*
*****************************************************************************/

#include "../inc/gl32-uniform-float4.h"

using namespace Ceng;

GL32_UniformFloat4::GL32_UniformFloat4() : GL32_ShaderConstant()
{
	values[0] = 0.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 1.0f;
}

GL32_UniformFloat4::GL32_UniformFloat4(GLint index, Ceng::GL32_ShaderProgram *program) : GL32_ShaderConstant(index,program)
{
	values[0] = 0.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 1.0f;
}

GL32_UniformFloat4::~GL32_UniformFloat4()
{
}

void GL32_UniformFloat4::Release()
{
	delete this;
}

const CRESULT GL32_UniformFloat4::SetFloat(const Ceng::FLOAT32 value)
{
	values[0] = value;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 1.0f;

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetFloat2(const Ceng::FLOAT32 *source)
{
	values[0] = source[0];
	values[1] = source[1];
	values[2] = 0.0f;
	values[3] = 1.0f;

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetFloat3(const Ceng::FLOAT32 *source)
{
	values[0] = source[0];
	values[1] = source[1];
	values[2] = source[2];
	values[3] = 1.0f;

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetFloat4(const Ceng::FLOAT32 *source)
{
	values[0] = source[0];
	values[1] = source[1];
	values[2] = source[2];
	values[3] = source[3];

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetInt(const Ceng::INT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetInt2(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetInt3(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetInt4(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetBool2(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetBool3(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetBool4(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat4::SetMatrix_4x4(const Ceng::FLOAT32 *source, const Ceng::BOOL transpose)
{
	return CE_OK;
}

void GL32_UniformFloat4::GL_UpdateThis()
{
	glUniform4fv(index, 1, values);
}