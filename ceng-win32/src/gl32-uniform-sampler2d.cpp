/*****************************************************************************
*
* gl32-uniform-sampler2d.cpp
*
* Created By Jari Korkala 26/10/2015
*
*****************************************************************************/

#include "../inc/gl32-uniform-sampler2d.h"

using namespace Ceng;

GL32_UniformSampler2D::GL32_UniformSampler2D() : GL32_ShaderConstant()
{
	value = 0;
}

GL32_UniformSampler2D::GL32_UniformSampler2D(GLint index, Ceng::GL32_ShaderProgram *program) : GL32_ShaderConstant(index, program)
{
	value = 0;
}

GL32_UniformSampler2D::~GL32_UniformSampler2D()
{
}

void GL32_UniformSampler2D::Release()
{
	delete this;
}

const CRESULT GL32_UniformSampler2D::SetFloat(const Ceng::FLOAT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetFloat2(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetFloat3(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetFloat4(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetInt(const Ceng::INT32 value)
{
	this->value = value;

	MarkDirty();
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetInt2(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetInt3(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetInt4(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetBool2(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetBool3(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetBool4(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformSampler2D::SetMatrix_4x4(const Ceng::FLOAT32 *source, const Ceng::BOOL transpose)
{
	return CE_OK;
}

void GL32_UniformSampler2D::GL_UpdateThis()
{
	glUniform1i(index,value);

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		if (result == GL_INVALID_OPERATION)
		{
			return;
		}
	}
}