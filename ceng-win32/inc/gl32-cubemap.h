/*****************************************************************************
*
* gl32-cubemap.h
*
* Created By Jari Korkala 20/11/2015
*
*****************************************************************************/

#ifndef CENG_GL32_CUBEMAP_H
#define CENG_GL32_CUBEMAP_H

#include <gl/glew.h>

#include <ceng/datatypes/tex2d-desc.h>

#include <ceng/interfaces/cubemap.h>

#include "gl32-texture-2d.h"



namespace Ceng
{
	class SubResourceData;

	class GL32_Cubemap : public Ceng::Cubemap, public GL32_Texture2D
	{
	public:

	public:
		GL32_Cubemap();

		GL32_Cubemap(const GLuint gl_textureID, const GL32_TextureFormat &gl_format, 
			const Ceng::UINT32 width,const Ceng::UINT32 height,const Ceng::IMAGE_FORMAT::value imageFormat,
			const Ceng::BOOL sRGB,const GLint mipLevels);

		virtual ~GL32_Cubemap();

		virtual void Release() override;

		virtual const CRESULT GL_GenerateMipmaps() override;

		virtual const CRESULT GetBufferData2D(Ceng::BufferData2D *dataPtr) override;

		static const Ceng::CRESULT GetInstance(const Texture2dDesc &desc,
			const SubResourceData *initialData,Ceng::GL32_Cubemap **texturePtr);

		static const Ceng::CRESULT GenerateCubemap(const Texture2dDesc &desc, const GL32_TextureFormat &format,
			GLint &mipLevels, const SubResourceData *initialData);

		virtual const Ceng::CRESULT GetShaderViewCubemap(const Ceng::ShaderResourceViewDesc &desc, 
			Ceng::ShaderResourceView **resourceView) override;

		virtual const Ceng::CRESULT GetSubResourceData(const Ceng::CubemapFace::value face, const Ceng::UINT32 mipLevel, 
			const Ceng::IMAGE_FORMAT::value destFormat, void *destPtr) override;

		virtual const Ceng::CRESULT SetSubResourceData(const Ceng::CubemapFace::value face, const Ceng::UINT32 mipLevel, 
			const Ceng::IMAGE_FORMAT::value sourceFormat, void *sourcePtr) override;
	};
}

#endif