/*****************************************************************************
*
* gl32-texture-unit.cpp
*
* Created By Jari Korkala 27/10/2015
*
*****************************************************************************/

#include "../inc/gl32-texture-unit.h"

#include "../inc/gl32-shader-resource-view.h"
#include "../inc/gl32-sampler-state.h"

using namespace Ceng;

GL32_TextureUnit::GL32_TextureUnit() : dirty(false),resource(nullptr),nextResource(nullptr),unitIndex(0),sampler(nullptr)
{
}

GL32_TextureUnit::GL32_TextureUnit(const Ceng::UINT32 unitIndex)
	: dirty(false),resource(nullptr),nextResource(nullptr),unitIndex(unitIndex),sampler(nullptr)
{
}

GL32_TextureUnit::~GL32_TextureUnit()
{
}

void GL32_TextureUnit::GL_Update()
{
	if (dirty == false)
	{
		return;
	}

	dirty = false;

	if (resource != nextResource)
	{
		glActiveTexture(GL_TEXTURE0 + unitIndex);

		if (resource != nullptr)
		{
			GL32_ShaderResourceView *gl_view = static_cast<GL32_ShaderResourceView*>(resource);

			gl_view->GL_Unbind();
		}

		if (nextResource != nullptr)
		{
			GL32_ShaderResourceView *gl_view = static_cast<GL32_ShaderResourceView*>(nextResource);

			gl_view->GL_Bind();
		}

		resource = nextResource;
	}

	if (sampler != nullptr)
	{
		GL32_SamplerState *gl_sampler = static_cast<GL32_SamplerState*>(sampler);

		glBindSampler(unitIndex, gl_sampler->gl_samplerID);

		/*
		GLenum result = glGetError();
		if (result != GL_NO_ERROR)
		{
			if (result == GL_INVALID_OPERATION)
			{
				return;
			}
			else if (result == GL_INVALID_VALUE)
			{
				return;
			}
		}
		*/
	}
	else
	{
		glBindSampler(unitIndex, 0);
	}
}
