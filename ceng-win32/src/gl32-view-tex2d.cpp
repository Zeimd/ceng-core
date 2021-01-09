/*****************************************************************************
*
* gl32-view-tex2d.cpp
*
* Created By Jari Korkala 27/10/2015
*
*****************************************************************************/

#include "../inc/gl32-view-tex2d.h"

using namespace Ceng;

GL32_ShaderViewTex2D::GL32_ShaderViewTex2D()
{
}

GL32_ShaderViewTex2D::GL32_ShaderViewTex2D(GL32_Texture2D *texture,const GLuint gl_textureID, const GLenum gl_textureType, const GLint baseMipLevel, const GLint maxMipLevel)
	: baseMipLevel(baseMipLevel),maxMipLevel(maxMipLevel),texture(texture)
{
	this->gl_textureID = gl_textureID;
	this->gl_textureType = gl_textureType;
}

GL32_ShaderViewTex2D::~GL32_ShaderViewTex2D()
{
}

void GL32_ShaderViewTex2D::Release()
{
	delete this;
}

void GL32_ShaderViewTex2D::GL_Bind()
{
	glBindTexture(GL_TEXTURE_2D, gl_textureID);
}

void GL32_ShaderViewTex2D::GL_Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void* GL32_ShaderViewTex2D::ResourcePtr()
{
	return (void*)texture;
}