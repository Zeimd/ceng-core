#include "cr-uniform-mat4.h"

using namespace Ceng;

CR_UniformMat4::CR_UniformMat4() : CR_ShaderConstant()
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

CR_UniformMat4::CR_UniformMat4(Ceng::UINT32 index, Ceng::ShaderWrapper* wrapper) : CR_ShaderConstant(index, wrapper)
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

CR_UniformMat4::~CR_UniformMat4()
{
}

void CR_UniformMat4::Release()
{
	delete this;
}

const CRESULT CR_UniformMat4::SetFloat(const Ceng::FLOAT32 value)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetFloat2(const Ceng::FLOAT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetFloat3(const Ceng::FLOAT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetFloat4(const Ceng::FLOAT32* source)
{
	return CE_OK;
}


const CRESULT CR_UniformMat4::SetInt(const Ceng::INT32 value)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetInt2(const Ceng::INT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetInt3(const Ceng::INT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetInt4(const Ceng::INT32* source)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetBool(const Ceng::BOOL value)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetBool2(const Ceng::BOOL* source)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetBool3(const Ceng::BOOL* source)
{
	return CE_OK;
}

const CRESULT CR_UniformMat4::SetBool4(const Ceng::BOOL* source)
{
	return CE_OK;
}


const CRESULT CR_UniformMat4::SetMatrix_4x4(const Ceng::FLOAT32* source, const Ceng::BOOL transpose)
{
	memcpy(values, source, 16 * sizeof(Ceng::FLOAT32));
	MarkDirty();
	wrapper->WriteUniform(index, values);
	return CE_OK;
}

void CR_UniformMat4::UpdateThis()
{
	//glUniformMatrix4fv(index, 1, gl_transpose, values);
}