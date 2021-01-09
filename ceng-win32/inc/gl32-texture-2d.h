/*****************************************************************************
*
* gl32-texture-2d.h
*
* Created By Jari Korkala 26/10/2015
*
*****************************************************************************/

#ifndef CENG_GL32_TEXTURE_2D_H
#define CENG_GL32_TEXTURE_2D_H

#include <gl/glew.h>

#include <ceng/datatypes/boolean.h>

#include <ceng/datatypes/tex2d-desc.h>
#include <ceng/datatypes/tex2d-desc-gl.h>

#include <ceng/interfaces/texture-2d.h>

namespace Ceng
{
	class SubResourceData;

	class GL32_TextureFormat
	{
	public:
		Ceng::BOOL compressed;
		GLint internalFormat;
		GLenum format;
		GLenum type;
	};

	class GL32_Texture2D : public Texture2D
	{
	public:
		Ceng::UINT32 width;
		Ceng::UINT32 height;

		GLuint gl_textureID;

		GL32_TextureFormat gl_format;

		Ceng::BOOL sRGB;
		Ceng::IMAGE_FORMAT::value imageFormat;

		GLint mipLevels;

	public:
		GL32_Texture2D();
		GL32_Texture2D(const GLuint gl_textureID, const GL32_TextureFormat &gl_format,
			const Ceng::UINT32 width, const Ceng::UINT32 height,const Ceng::IMAGE_FORMAT::value imageFormat,
			const Ceng::BOOL sRGB,const GLint mipLevels);

		virtual ~GL32_Texture2D();

		virtual void Release() override;

		static const Ceng::CRESULT GetInstance(const Texture2dDesc &desc, const SubResourceData *initialData, GL32_Texture2D **output);

		static const Ceng::CRESULT GetInstance(const GL_Texture2dDesc &desc, const SubResourceData *initialData, GL32_Texture2D **output);

		static const Ceng::CRESULT TranslateFormat(const Texture2dDesc &desc, GL32_TextureFormat *gl_format);

		static const Ceng::CRESULT IsSupported(const GLint compressedFormat);

		static const Ceng::CRESULT IsSupported(const GLint type, const GLint format, const GLint internalFormat);

		static const Ceng::CRESULT CompressedSRGB(const GLenum internalFormat,GLenum *new_format);

		static const Ceng::BOOL GL32_Texture2D::IsCompressed(const GLint internalFormat);

		static const GLint MaxMipLevel(const Ceng::UINT32 width, const Ceng::UINT32 height);

		static const Ceng::CRESULT GenerateTexture(const Texture2dDesc &desc, const GL32_TextureFormat &format,
			GLint &mipLevels,const SubResourceData *initialData);

		static void GetPreviousTexBinding(GLint &gl_type, GLint &gl_texture);

		virtual const CRESULT GenerateMipmaps();

		virtual const CRESULT GL_GenerateMipmaps();

		virtual const CRESULT GetBufferData2D(Ceng::BufferData2D *dataPtr) override;

		virtual const BufferType::value GetResourceType() override;

		virtual const Ceng::CRESULT GetShaderViewTex2D(const Ceng::ShaderResourceViewDesc &desc, 
			Ceng::ShaderResourceView **resourceView) override;

		virtual const Ceng::CRESULT GetRenderTargetView(const Ceng::RenderTargetViewDesc &desc,
			Ceng::RenderTargetView **targetView) override;

		virtual const Ceng::CRESULT GetSubResourceData(const Ceng::UINT32 mipLevel, void *destPtr) override;
	};
}

#endif