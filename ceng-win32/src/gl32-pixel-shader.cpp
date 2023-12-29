/*****************************************************************************
*
* gl32-pixel-shader.cpp
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#include "../inc/gl32-pixel-shader.h"

using namespace Ceng;

GL32_PixelShader::GL32_PixelShader()
{
}

GL32_PixelShader::GL32_PixelShader(const GLuint shaderID, Ceng::StringUtf8 &&shaderLog, const Ceng::BOOL compiled)
	: shaderID(shaderID), shaderLog(shaderLog), compiled(compiled)
{

}

GL32_PixelShader::~GL32_PixelShader()
{
	glDeleteShader(shaderID);
}

void GL32_PixelShader::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_PixelShader::GetInstance(const Ceng::StringUtf8 &shaderText, GL32_PixelShader **output)
{
	GLuint shaderID;

	shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	const char *stringPtr = shaderText.ToCString();
	GLint length = shaderText.Length();

	glShaderSource(shaderID, 1, &stringPtr, &length);

	result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glDeleteShader(shaderID);
		return CE_ERR_FAIL;
	}

	glCompileShader(shaderID);

	result = glGetError();
	if (result != GL_NO_ERROR)
	{
		glDeleteShader(shaderID);
		return CE_ERR_FAIL;
	}

	Ceng::BOOL compiled = true;
	Ceng::StringUtf8 shaderLog;

	GLint gl_compiled;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &gl_compiled);

	if (gl_compiled != GL_TRUE)
	{
		compiled = false;

		GLint logSize;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);

		std::vector<char> tempLog(logSize);

		glGetShaderInfoLog(shaderID, logSize, nullptr, &tempLog[0]);

		shaderLog = &tempLog[0];
	}

	*output = new GL32_PixelShader(shaderID, std::move(shaderLog), compiled);

	return CE_OK;
}

/*
CRESULT GL32_PixelShader::GetConstant(const char *variableName, Ceng::ShaderConstant **handle)
{
	return CE_OK;
}
*/

const Ceng::CRESULT GL32_PixelShader::GetLog(Ceng::StringUtf8 **log)
{
	*log = new StringUtf8(shaderLog);
	return CE_OK;
}

const Ceng::BOOL GL32_PixelShader::Compiled()
{
	return compiled;
}
