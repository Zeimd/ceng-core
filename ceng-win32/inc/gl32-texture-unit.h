/*****************************************************************************
*
* gl32-texture-unit.h
*
* Created By Jari Korkala 27/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_TEXTURE_UNIT_H
#define CENG_GL32_TEXTURE_UNIT_H

#include <gl/glew.h>

#include <ceng/datatypes/boolean.h>

namespace Ceng
{
	class ShaderResourceView;
	class SamplerState;

	class GL32_TextureUnit
	{
	public:
		Ceng::UINT32 unitIndex;

		Ceng::ShaderResourceView *resource;
		Ceng::ShaderResourceView *nextResource;

		Ceng::SamplerState *sampler;

		Ceng::BOOL dirty;

		Ceng::BOOL enabled;

	public:
		GL32_TextureUnit();

		GL32_TextureUnit(const Ceng::UINT32 unitIndex);

		~GL32_TextureUnit();

		void GL_Update();
	};
}

#endif