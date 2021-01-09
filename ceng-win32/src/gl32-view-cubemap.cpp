/*****************************************************************************
*
* gl32-view-cubemap.cpp
*
* Created By Jari Korkala 20/11/2015
*
*****************************************************************************/

#include "../inc/gl32-view-cubemap.h"
#include "../inc/gl32-cubemap.h"

using namespace Ceng;

GL32_ShaderViewCubemap::GL32_ShaderViewCubemap()
{
}

GL32_ShaderViewCubemap::GL32_ShaderViewCubemap(GL32_Cubemap *cubemap,const GLint baseMipLevel, const GLint maxMipLevel)
	: cubemap(cubemap),baseMipLevel(baseMipLevel),maxMipLevel(maxMipLevel)
{
}

GL32_ShaderViewCubemap::~GL32_ShaderViewCubemap()
{
}

void GL32_ShaderViewCubemap::Release()
{
	delete this;
}

void GL32_ShaderViewCubemap::GL_Bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->gl_textureID);
}

void GL32_ShaderViewCubemap::GL_Unbind()
{

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void* GL32_ShaderViewCubemap::ResourcePtr()
{
	return (void*)cubemap;
}