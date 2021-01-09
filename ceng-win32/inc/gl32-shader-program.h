/*****************************************************************************
*
* gl32-shader-program.h
*
* Created By Jari Korkala 25/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_SHADER_PROGRAM_H
#define CENG_GL32_SHADER_PROGRAM_H

#include <gl/glew.h>

#include <list>

#include <ceng/interfaces/shader-program.h>

#include <ceng/datatypes/ce-string.h>

#include "gl32-shader-const.h"

namespace Ceng
{
	struct UniformData
	{
		Ceng::StringUtf8 name;
		GLuint index;
		GLint size;
		GLenum type;
	};

	class VertexShader;
	class PixelShader;

	class GL32_ShaderProgram : public Ceng::ShaderProgram
	{
	public:
		GLuint programID;

		std::vector<UniformData> uniforms;

		std::vector<GL32_ShaderConstant*> uniformUpdates;

		Ceng::StringUtf8 log;
		Ceng::BOOL linked;

		Ceng::BOOL active;

	public:
		GL32_ShaderProgram();
		GL32_ShaderProgram(const GLuint programID, std::vector<UniformData> &&uniforms, Ceng::StringUtf8 &&log, const Ceng::BOOL linked);
		virtual ~GL32_ShaderProgram();

		static const Ceng::CRESULT GetInstance(Ceng::VertexShader *vertexShader, Ceng::PixelShader *pixelShader,GL32_ShaderProgram **program);

		virtual void Release() override;

		virtual const Ceng::CRESULT GetConstant(const char *variableName,Ceng::ShaderConstant **handle) override;

		virtual const Ceng::CRESULT GetLog(Ceng::StringUtf8 **log) override;

		virtual const Ceng::BOOL Linked() override;

		static const Ceng::CRESULT GatherUniforms(const GLuint programID, std::vector<UniformData> &uniforms);

		const Ceng::CRESULT AddUniformUpdate(GL32_ShaderConstant *uniform);

		const Ceng::CRESULT GL_UpdateUniforms();

		const Ceng::BOOL IsActive();
	};
}

#endif