/*****************************************************************************
*
* gl32-vertex-shader.h
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#include "../inc/gl32-vertex-shader.h"

using namespace Ceng;

GL32_VertexShader::GL32_VertexShader()
{
}

GL32_VertexShader::GL32_VertexShader(const GLuint shaderID, Ceng::StringUtf8 &&shaderLog,const Ceng::BOOL compiled)
	: shaderID(shaderID),shaderLog(shaderLog),compiled(compiled)
{

}

GL32_VertexShader::~GL32_VertexShader()
{
	glDeleteShader(shaderID);
}

void GL32_VertexShader::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_VertexShader::GetInstance(const Ceng::StringUtf8 &shaderText,GL32_VertexShader **output)
{
	GLuint shaderID;

	shaderID = glCreateShader(GL_VERTEX_SHADER);

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

	GLint gl_compiled;

	Ceng::BOOL compiled = true;
	Ceng::StringUtf8 shaderLog;

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

	*output = new GL32_VertexShader(shaderID, std::move(shaderLog),compiled);

	return CE_OK;
}

CRESULT GL32_VertexShader::GetConstant(const char *variableName, Ceng::ShaderConstant **handle)
{
	glGetUniformLocation(shaderID, variableName);

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		*handle = nullptr;
		return CE_ERR_FAIL;
	}



	return CE_OK;
}

const Ceng::CRESULT GL32_VertexShader::GetLog(Ceng::StringUtf8 **log)
{
	*log = new StringUtf8(shaderLog);
	return CE_OK;
}

const Ceng::BOOL GL32_VertexShader::Compiled()
{
	return compiled;
}
