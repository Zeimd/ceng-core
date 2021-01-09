/*****************************************************************************
*
* gl32-vertex-shader.h
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_VERTEX_SHADER_H
#define CENG_GL32_VERTEX_SHADER_H

#include <gl/glew.h>

#include <ceng/datatypes/ce-string.h>

#include <ceng/interfaces/vertex-shader.h>

namespace Ceng
{

	class GL32_VertexShader : public Ceng::VertexShader
	{
	public:

		GLuint shaderID;

		Ceng::StringUtf8 shaderLog;
		Ceng::BOOL compiled;

	public:

		GL32_VertexShader();
		GL32_VertexShader(const GLuint shaderID, Ceng::StringUtf8 &&shaderLog,const Ceng::BOOL compiled);
		virtual ~GL32_VertexShader();

		virtual void Release() override;

		static const Ceng::CRESULT GetInstance(const Ceng::StringUtf8 &shaderText,GL32_VertexShader **output);

		virtual CRESULT GetConstant(const char *variableName,
			Ceng::ShaderConstant **handle) override;

		virtual const Ceng::CRESULT GetLog(Ceng::StringUtf8 **log) override;

		virtual const Ceng::BOOL Compiled() override;
	};
}

#endif