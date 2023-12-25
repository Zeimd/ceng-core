/*****************************************************************************
*
* cr-shader-const.cpp
*
* Created By Jari Korkala 31/8/2014
*
* - Moved CR_ShaderConstHandle methods here from header.
*
*****************************************************************************/

#include "cr-shader-const.h"

#include "cr-vertex-shader.h"

using namespace Ceng;

CR_ShaderConstHandle::CR_ShaderConstHandle()
{
	index = 0;
	shader = nullptr;
}

CR_ShaderConstHandle::CR_ShaderConstHandle(const Ceng::UINT32 index,ShaderWrapper *shader)
{
	this->index = index;
	this->shader = shader;
}

CR_ShaderConstHandle::~CR_ShaderConstHandle()
{
}

void CR_ShaderConstHandle::Release()
{
	delete this;
}

const CRESULT CR_ShaderConstHandle::SetFloat(const Ceng::FLOAT32 value)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetFloat2(const Ceng::FLOAT32* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetFloat3(const Ceng::FLOAT32* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetFloat4(const Ceng::FLOAT32* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetInt(const Ceng::INT32 value)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetInt2(const Ceng::INT32* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetInt3(const Ceng::INT32* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetInt4(const Ceng::INT32* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetBool(const Ceng::BOOL value)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetBool2(const Ceng::BOOL* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetBool3(const Ceng::BOOL* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetBool4(const Ceng::BOOL* values)
{
	return CE_ERR_FAIL;
}

const CRESULT CR_ShaderConstHandle::SetMatrix_4x4(const Ceng::FLOAT32* values, const Ceng::BOOL transpose)
{
	return CE_ERR_FAIL;
}

/*
const CRESULT CR_ShaderConstHandle::GetValue(void *dest)
{
	if (shader != nullptr)
	{
		return shader->ReadUniform(index,dest);
	}

	return CE_ERR_FAIL;
}

	
const CRESULT CR_ShaderConstHandle::SetValue(void *source)
{
	if (shader != nullptr)
	{
		return shader->WriteUniform(index,source);			
	}

	return CE_ERR_FAIL;
}
*/