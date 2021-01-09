/*****************************************************************************
*
* gl32-view-cubemap.h
*
* Created By Jari Korkala 20/11/2015
*
*****************************************************************************/

#ifndef CENG_GL32_VIEW_CUBEMAP_H
#define CENG_GL32_VIEW_CUBEMAP_H

#include <gl/glew.h>

#include "gl32-shader-resource-view.h"

namespace Ceng
{
	class GL32_Cubemap;

	class GL32_ShaderViewCubemap : public GL32_ShaderResourceView
	{
	public:
		GL32_Cubemap *cubemap;

		GLint baseMipLevel;
		GLint maxMipLevel;

	public:
		GL32_ShaderViewCubemap();
		GL32_ShaderViewCubemap(GL32_Cubemap *texture,const GLint baseMipLevel, const GLint maxMipLevel);

		virtual ~GL32_ShaderViewCubemap();

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