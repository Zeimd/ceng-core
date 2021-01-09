/*****************************************************************************
*
* gl32-uniform-mat4.h
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#include <string.h>

#include "../inc/gl32-uniform-mat4.h"

using namespace Ceng;

GL32_UniformMat4::GL32_UniformMat4() : GL32_ShaderConstant()
{
	values[0] = 1.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 0.0f;

	values[4] = 0.0f;
	values[5] = 1.0f;
	values[6] = 0.0f;
	values[7] = 0.0f;

	values[8] = 0.0f;
	values[9] = 0.0f;
	values[10] = 1.0f;
	values[11] = 0.0f;

	values[12] = 0.0f;
	values[13] = 0.0f;
	values[14] = 0.0f;
	values[15] = 1.0f;
}

GL32_UniformMat4::GL32_UniformMat4(GLint index, Ceng::GL32_ShaderProgram *program) : GL32_ShaderConstant(index, program)
{
	values[0] = 1.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 0.0f;

	values[4] = 0.0f;
	values[5] = 1.0f;
	values[6] = 0.0f;
	values[7] = 0.0f;

	values[8] = 0.0f;
	values[9] = 0.0f;
	values[10] = 1.0f;
	values[11] = 0.0f;

	values[12] = 0.0f;
	values[13] = 0.0f;
	values[14] = 0.0f;
	values[15] = 1.0f;

}

GL32_UniformMat4::~GL32_UniformMat4()
{
}

void GL32_UniformMat4::Release()
{
	delete this;
}

const CRESULT GL32_UniformMat4::SetFloat(const Ceng::FLOAT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetFloat2(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetFloat3(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetFloat4(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}


const CRESULT GL32_UniformMat4::SetInt(const Ceng::INT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetInt2(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetInt3(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetInt4(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetBool2(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetBool3(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformMat4::SetBool4(const Ceng::BOOL *source)
{
	return CE_OK;
}


const CRESULT GL32_UniformMat4::SetMatrix_4x4(const Ceng::FLOAT32 *source,const Ceng::BOOL transpose)
{
	memcpy(values, source, 16 * sizeof(Ceng::FLOAT32));

	gl_transpose = GL_FALSE;

	if (transpose == true)
	{
		gl_transpose = GL_TRUE;
	}

	MarkDirty();
	return CE_OK;
}

void GL32_UniformMat4::GL_UpdateThis()
{
	glUniformMatrix4fv(index,1,gl_transpose,values);
}