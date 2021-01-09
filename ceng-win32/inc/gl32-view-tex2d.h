/*****************************************************************************
*
* gl32-view-tex2d.h
*
* Created By Jari Korkala 27/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_VIEW_TEX2D_H
#define CENG_GL32_VIEW_TEX2D_H

#include <gl/glew.h>

#include "gl32-shader-resource-view.h"

namespace Ceng
{
	class GL32_Texture2D;

	class GL32_ShaderViewTex2D : public GL32_ShaderResourceView
	{
	public:
		GL32_Texture2D *texture;

		GLint baseMipLevel;
		GLint maxMipLevel;

	public:
		GL32_ShaderViewTex2D();
		GL32_ShaderViewTex2D(GL32_Texture2D *texture,const GLuint gl_textureID,const GLenum gl_textureType,const GLint baseMipLevel, const GLint maxMipLevel);
		virtual ~GL32_ShaderViewTex2D();
		virtual void Release() override;

		/**
		* Bind this resource to texture unit.
		*/
		virtual void GL_Bind() override;

		/**
		* Unbind this resource from texture unit.
		*/
		virtual void GL_Unbind() override;

		virtual void* ResourcePtr() override;
	};

}

#endif