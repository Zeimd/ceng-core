/*****************************************************************************
*
* gl32-uniform-empty.cpp
*
* Created By Jari Korkala 4/11/2015
*
*****************************************************************************/

#include "../inc/gl32-uniform-empty.h"

using namespace Ceng;

GL32_UniformEmpty::GL32_UniformEmpty() : GL32_ShaderConstant()
{
}

GL32_UniformEmpty::~GL32_UniformEmpty()
{
}

void GL32_UniformEmpty::Release()
{
	delete this;
}

const CRESULT GL32_UniformEmpty::SetFloat(const Ceng::FLOAT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetFloat2(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetFloat3(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetFloat4(const Ceng::FLOAT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetInt(const Ceng::INT32 value)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetInt2(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetInt3(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetInt4(const Ceng::INT32 *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetBool2(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetBool3(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetBool4(const Ceng::BOOL *source)
{
	return CE_OK;
}

const CRESULT GL32_UniformEmpty::SetMatrix_4x4(const Ceng::FLOAT32 *source, const Ceng::BOOL transpose)
{
	return CE_OK;
}

void GL32_UniformEmpty::GL_UpdateThis()
{
}