/*****************************************************************************
*
* gl32-target-tex2d.cpp
*
* Created By Jari Korkala 9/11/2015
*
*****************************************************************************/

#include "../inc/gl32-target-tex2d.h"
#include "../inc/gl32-texture-2d.h"

using namespace Ceng;

GL32_RenderTexture2D::GL32_RenderTexture2D()
{
}

GL32_RenderTexture2D::GL32_RenderTexture2D(GL32_Texture2D *texture, const Ceng::UINT32 mipSlice)
	:texture(texture),mipSlice(mipSlice)
{

}

GL32_RenderTexture2D::~GL32_RenderTexture2D()
{
}

void GL32_RenderTexture2D::Release()
{
	delete this;
}

void GL32_RenderTexture2D::GL_Bind(const Ceng::UINT32 slot)
{
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, slot, GL_TEXTURE_2D, texture->gl_textureID, mipSlice);
	GLenum result = glGetError();

	if (result != GL_NO_ERROR)
	{
		return;
	}
}

void GL32_RenderTexture2D::GL_Unbind(const Ceng::UINT32 slot)
{
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, slot, GL_TEXTURE_2D, 0, mipSlice);
	GLenum result = glGetError();

	if (result != GL_NO_ERROR)
	{
		return;
	}
}

void* GL32_RenderTexture2D::ResourcePtr()
{
	return (void*)texture;
}