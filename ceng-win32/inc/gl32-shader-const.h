/*****************************************************************************
*
* gl32-shader-const.h
*
* Created By Jari Korkala 25/10/2015
*
*
*****************************************************************************/

#ifndef CENG_GL32_SHADER_CONST_H
#define CENG_GL32_SHADER_CONST_H

#include <gl/glew.h>

#include <ceng/interfaces/shader-const.h>

namespace Ceng
{
	class GL32_RenderContext;
	class GL32_ShaderProgram;

	class GL32_ShaderConstant : public ShaderConstant
	{
	private:
		Ceng::BOOL dirty;
		Ceng::GL32_ShaderProgram *program;

	protected:
		
		GLint index;
	public:
		GL32_ShaderConstant();

		GL32_ShaderConstant(GLint index,Ceng::GL32_ShaderProgram *program);

		virtual ~GL32_ShaderConstant();

		virtual void Release() override;

		void MarkDirty();

		void GL_Update();
		void GL_ForceUpdate();

		virtual void GL_UpdateThis() = 0;
	};
}

#endif