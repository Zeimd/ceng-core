/*****************************************************************************
*
* gl32-uniform-float.cpp
*
* Created By Jari Korkala 25/10/2015
*
*
*****************************************************************************/

#include "../inc/gl32-uniform-float.h"

using namespace Ceng;

GL32_UniformFloat::GL32_UniformFloat() : GL32_ShaderConstant()
{
	value;
}

GL32_UniformFloat::GL32_UniformFloat(GLint index, Ceng::GL32_ShaderProgram *program) : GL32_ShaderConstant(index, program)
{
	value;
}

GL32_UniformFloat::~GL32_UniformFloat()
{
}

void GL32_UniformFloat::Release()
{
	delete this;
}

const CRESULT GL32_UniformFloat::SetFloat(const Ceng::FLOAT32 value)
{
	this->value = value;

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetFloat2(const Ceng::FLOAT32 *source)
{
	value = source[0];

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetFloat3(const Ceng::FLOAT32 *source)
{
	value = source[0];

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetFloat4(const Ceng::FLOAT32 *source)
{
	value = source[0];

	MarkDirty();

	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetInt(const Ceng::INT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetInt2(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetInt3(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetInt4(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetBool2(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetBool3(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetBool4(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformFloat::SetMatrix_4x4(const Ceng::FLOAT32 *source, const Ceng::BOOL transpose)
{
	return CE_OK;
}

void GL32_UniformFloat::GL_UpdateThis()
{
	glUniform1f(index,value);
}