
#include "cr-shader-program.h"

#include "cr-vertex-shader.h"
#include "cr-pixel-shader.h"

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

	CR_ShaderConstant* uniform;

	cresult = vShader->GetConstant(variableName, &uniform);
	if (cresult == Ceng::CE_OK)
	{
		*handle = uniform;
		return CE_OK;
	}

	cresult = pShader->GetConstant(variableName, &uniform);
	if (cresult == Ceng::CE_OK)
	{
		*handle = uniform;
		return CE_OK;
	}

	return CE_ERR_UNIMPLEMENTED;
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