
#include "cr-shader-program.h"

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