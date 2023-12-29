
#include "cr-shader-program.h"

#include "cr-vertex-shader.h"
#include "cr-pixel-shader.h"

#include "cr-uniform-mat4.h"
#include "cr-uniform-uint.h"

using namespace Ceng;

Ceng::CRESULT CR_ShaderProgram::GetInstance(CR_VertexShader* vShader, CR_PixelShader* pShader, CR_ShaderProgram** out_program)
{
	if (vShader == nullptr || pShader == nullptr || out_program == nullptr)
	{
		return CE_ERR_INVALID_PARAM;
	}

	CR_ShaderProgram* prog = new CR_ShaderProgram();

	if (prog == nullptr)
	{
		return CE_ERR_OUT_OF_MEMORY;
	}

	prog->vShader = vShader;
	prog->pShader = pShader;

	*out_program = prog;

	return Ceng::CE_OK;
}

void CR_ShaderProgram::Release()
{
	delete this;
}

const Ceng::CRESULT CR_ShaderProgram::GetConstant(const char* variableName, Ceng::ShaderConstant** handle)
{
	CRESULT cresult;

	Ceng::SHADER_DATATYPE::value type;
	Ceng::UINT32 index;

	ShaderWrapper* wrapper;

	cresult = vShader->GetConstant(variableName, index, type);
	if (cresult == Ceng::CE_OK)
	{
		wrapper = &vShader->wrapper;
	}
	else
	{
		cresult = pShader->GetConstant(variableName, index, type);
		if (cresult == Ceng::CE_OK)
		{
			wrapper = &pShader->wrapper;
		}
		else
		{
			return CE_ERR_FAIL;
		}
	}

	CR_ShaderConstant* uniform;

	switch (type)
	{
	case Ceng::SHADER_DATATYPE::UINT:

		try
		{
			uniform = new CR_UniformUint(index, wrapper);
		}
		catch (std::bad_alloc& ba)
		{
			return CE_ERR_OUT_OF_MEMORY;
		}
		break;

	case Ceng::SHADER_DATATYPE::FLOAT4x4:

		try
		{
			uniform = new CR_UniformMat4(index, wrapper);
		}
		catch (std::bad_alloc& ba)
		{
			return CE_ERR_OUT_OF_MEMORY;
		}
		break;
	default:
		return CE_ERR_UNIMPLEMENTED;
	}

	*handle = uniform;

	return CE_OK;
}

const Ceng::CRESULT CR_ShaderProgram::GetLog(Ceng::StringUtf8** log)
{
	*log = new StringUtf8();

	return Ceng::CE_OK;
}

const Ceng::BOOL CR_ShaderProgram::Linked()
{
	return true;
}