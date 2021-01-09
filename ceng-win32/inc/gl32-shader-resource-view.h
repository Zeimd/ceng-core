/*****************************************************************************
*
* gl32-shader-resource-view.h
*
* Created By Jari Korkala 27/10/2015
*
* Base class for OpenGL shader resources.
*
*****************************************************************************/

#ifndef CENG_GL32_SHADER_RESOURCE_VIEW_H
#define CENG_GL32_SHADER_RESOURCE_VIEW_H

#include <ceng/interfaces/shader-resource-view.h>

namespace Ceng
{
	class GL32_ShaderResourceView : public Ceng::ShaderResourceView
	{
	public:
		GLuint gl_textureID;
		GLenum gl_textureType;
	public:
		GL32_ShaderResourceView()
		{
		}
		virtual ~GL32_ShaderResourceView()
		{
		}

		/**
		 * Bind this resource to texture unit.
		 */
		virtual void GL_Bind() = 0;

		/**
		 * Unbind this resource from texture unit.
		 */
		virtual void GL_Unbind() = 0;

		/**
		 * Returns pointer to source resource for pipeline consistency
		 * tests.
		 */
		virtual void* ResourcePtr() = 0;
	};
}

#endif