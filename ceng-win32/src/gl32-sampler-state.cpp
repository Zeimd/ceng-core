/*****************************************************************************
*
* gl32-sampler-state.cpp
*
* Created By Jari Korkala 27/10/2015
*
*****************************************************************************/

#include "../inc/gl32-sampler-state.h"

using namespace Ceng;

GL32_SamplerState::GL32_SamplerState()
{
}

GL32_SamplerState::GL32_SamplerState(const GLuint gl_samplerID) : gl_samplerID(gl_samplerID)
{
}

GL32_SamplerState::~GL32_SamplerState()
{
	glDeleteSamplers(1, &gl_samplerID);
}

void GL32_SamplerState::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_SamplerState::GetInstance(const SamplerStateDesc &desc, GL32_SamplerState **output)
{
	GLuint gl_samplerID;

	glGenSamplers(1, &gl_samplerID);

	GLenum gl_result = glGetError();
	if (gl_result != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	GLint gl_mode;

	// U wrapping mode

	CRESULT cresult = TranslateWrapMode(desc.addressU,&gl_mode);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	glSamplerParameteri(gl_samplerID, GL_TEXTURE_WRAP_S, gl_mode);

	// V wrapping mode

	cresult = TranslateWrapMode(desc.addressV, &gl_mode);
	if (cresult != CE_OK) return cresult;

	glSamplerParameteri(gl_samplerID, GL_TEXTURE_WRAP_T, gl_mode);

	// W wrapping mode

	cresult = TranslateWrapMode(desc.addressW, &gl_mode);
	if (cresult != CE_OK) return cresult;

	glSamplerParameteri(gl_samplerID, GL_TEXTURE_WRAP_R, gl_mode);

	// Minification filter

	cresult = TranslateMinFilter(desc.minFilter, &gl_mode);
	if (cresult != CE_OK) return cresult;

	glSamplerParameteri(gl_samplerID, GL_TEXTURE_MIN_FILTER, gl_mode);

	// Magnification filter

	cresult = TranslateMagFilter(desc.magFilter, &gl_mode);
	if (cresult != CE_OK) return cresult;

	glSamplerParameteri(gl_samplerID, GL_TEXTURE_MAG_FILTER, gl_mode);

	*output = new GL32_SamplerState(gl_samplerID);

	return CE_OK;
}

const Ceng::CRESULT GL32_SamplerState::TranslateWrapMode(const Ceng::TextureAddressMode::value mode,GLint *gl_mode)
{
	switch (mode)
	{
	case Ceng::TextureAddressMode::clamp:
		*gl_mode = GL_CLAMP_TO_EDGE;
		break;
	case Ceng::TextureAddressMode::wrap:
		*gl_mode = GL_REPEAT;
		break;
	case Ceng::TextureAddressMode::mirror:
		*gl_mode = GL_MIRRORED_REPEAT;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_SamplerState::TranslateMinFilter(const Ceng::TextureMinFilter::value mode, GLint *gl_mode)
{
	switch (mode)
	{
	case Ceng::TextureMinFilter::nearest:
		*gl_mode = GL_NEAREST;
		break;
	case Ceng::TextureMinFilter::nearest_mip_nearest:
		*gl_mode = GL_NEAREST_MIPMAP_NEAREST;
		break;
	case Ceng::TextureMinFilter::nearest_mip_linear:
		*gl_mode = GL_NEAREST_MIPMAP_LINEAR;
		break;
	case Ceng::TextureMinFilter::linear:
		*gl_mode = GL_LINEAR;
		break;
	case Ceng::TextureMinFilter::linear_mip_nearest:
		*gl_mode = GL_LINEAR_MIPMAP_NEAREST;
		break;
	case Ceng::TextureMinFilter::linear_mip_linear:
		*gl_mode = GL_LINEAR_MIPMAP_LINEAR;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_SamplerState::TranslateMagFilter(const Ceng::TextureMagFilter::value mode, GLint *gl_mode)
{
	switch (mode)
	{
	case Ceng::TextureMagFilter::nearest:
		*gl_mode = GL_NEAREST;
		break;
	case Ceng::TextureMagFilter::linear:
		*gl_mode = GL_LINEAR;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

void GL32_SamplerState::GetSamplerDesc(SamplerStateDesc &desc)
{

}