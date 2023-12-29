#include "cr-uniform-uint.h"

using namespace Ceng;

CR_UniformUint::CR_UniformUint() : CR_ShaderConstant(),value(0)
{
	
}

CR_UniformUint::CR_UniformUint(Ceng::UINT32 index, Ceng::ShaderWrapper* wrapper) : CR_ShaderConstant(index, wrapper),value(0)
{
	
}

CR_UniformUint::~CR_UniformUint()
{
}

void CR_UniformUint::Release()
{
	delete this;
}

const CRESULT CR_UniformUint::SetFloat(const Ceng::FLOAT32 value)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetFloat2(const Ceng::FLOAT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetFloat3(const Ceng::FLOAT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetFloat4(const Ceng::FLOAT32* source)
{
	return CE_OK;
}


const CRESULT CR_UniformUint::SetInt(const Ceng::INT32 value)
{
	this->value = (Ceng::UINT32)value;

	MarkDirty();

	wrapper->WriteUniform(index, (void*)&value);

	return CE_OK;
}

const CRESULT CR_UniformUint::SetInt2(const Ceng::INT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetInt3(const Ceng::INT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetInt4(const Ceng::INT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetBool2(const Ceng::BOOL* source)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetBool3(const Ceng::BOOL* source)
{
	return CE_OK;
}

const CRESULT CR_UniformUint::SetBool4(const Ceng::BOOL* source)
{
	return CE_OK;
}


const CRESULT CR_UniformUint::SetMatrix_4x4(const Ceng::FLOAT32* source, const Ceng::BOOL transpose)
{
	return CE_OK;
}

void CR_UniformUint::UpdateThis()
{
	//glUniformMatrix4fv(index, 1, gl_transpose, values);
}