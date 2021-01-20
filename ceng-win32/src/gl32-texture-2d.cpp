/*****************************************************************************
*
* gl32-texture-2d.cpp
*
* Created By Jari Korkala 26/10/2015
*
*****************************************************************************/

#include <ceng/datatypes/sub-resource-data.h>
#include <ceng/datatypes/shader-resource-view-desc.h>

#include <ceng/datatypes/render-target-view-desc.h>

#include <ceng/datatypes/bufferdata-2d.h>

#include "../inc/gl32-texture-2d.h"
#include "../inc/gl32-view-tex2d.h"
#include "../inc/gl32-target-tex2d.h"

using namespace Ceng;

GL32_Texture2D::GL32_Texture2D()
{
}

GL32_Texture2D::GL32_Texture2D(const GLuint gl_textureID, const GL32_TextureFormat &gl_format, 
	const Ceng::UINT32 width, const Ceng::UINT32 height,
	const Ceng::IMAGE_FORMAT::value imageFormat,const Ceng::BOOL sRGB,
	const GLint mipLevels)
	: gl_textureID(gl_textureID),gl_format(gl_format),width(width),
	height(height),imageFormat(imageFormat),sRGB(sRGB),mipLevels(mipLevels)
{
}

GL32_Texture2D::~GL32_Texture2D()
{
	glDeleteTextures(1,&gl_textureID);
}

void GL32_Texture2D::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_Texture2D::GetInstance(const Texture2dDesc &desc, const SubResourceData *initialData, 
	GL32_Texture2D **output)
{
	GLuint gl_textureID=0;
	GLenum gl_result = 0;

	GL32_TextureFormat gl_format;

	CRESULT cresult = TranslateFormat(desc,&gl_format);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	// Don't allow more mipmaps than possible

	GLint mipLevels = MaxMipLevel(desc.width, desc.height);
	
	if (desc.mipLevels != 0)
	{
		if (desc.mipLevels > Ceng::UINT32(mipLevels))
		{
			return CE_ERR_INVALID_PARAM;
		}
		mipLevels = desc.mipLevels;
	}
	else
	{
		mipLevels = 1;
	}

	glGenTextures(1, &gl_textureID);

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		switch (gl_result)
		{
		case GL_INVALID_ENUM:
			return CE_ERR_INVALID_PARAM;
		case GL_INVALID_VALUE:
			return CE_ERR_INVALID_PARAM;
		case GL_INVALID_OPERATION:
			return CE_ERR_FAIL;
		case GL_OUT_OF_MEMORY:
			return CE_ERR_OUT_OF_VIDEO_MEMORY;
		};

		return CE_ERR_FAIL;
	}

	// Set correct pixel store options

	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Store current texture unit state
	GLint gl_previousTex;
	GLint gl_previousType;

	GetPreviousTexBinding(gl_previousType, gl_previousTex);

	glBindTexture(GL_TEXTURE_2D, gl_textureID);

	cresult = GenerateTexture(desc, gl_format, mipLevels, initialData);

	glBindTexture(gl_previousType, gl_previousTex);

	if (cresult != CE_OK)
	{
		glDeleteTextures(1, &gl_textureID);
		return cresult;
	}
	
	*output = new GL32_Texture2D(gl_textureID, gl_format, desc.width,desc.height,desc.format,desc.sRGB, mipLevels);

	if (gl_format.compressed == false)
	{
		if (desc.optionFlags & Ceng::BufferOptions::generate_mip_maps)
		{
			cresult = (*output)->GenerateMipmaps();
			return cresult;
		}
	}

	return CE_OK;
}

const GLint GL32_Texture2D::MaxMipLevel(const Ceng::UINT32 width, const Ceng::UINT32 height)
{
	// Calculate maximum number of mipmaps
	GLint mipLevels = 1;

	do
	{
		Ceng::UINT32 mipWidth = width >> mipLevels;
		Ceng::UINT32 mipHeight = height >> mipLevels;

		if (mipWidth == 0 && mipHeight == 0)
		{
			break;
		}

		++mipLevels;
	} while (1);

	return mipLevels;
}

const Ceng::CRESULT GL32_Texture2D::GenerateTexture(const Texture2dDesc &desc, const GL32_TextureFormat &gl_format,
	GLint &mipLevels,const SubResourceData *initialData)
{
	GLenum gl_result=0;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, mipLevels - 1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, mipLevels - 1);

	if (initialData == nullptr)
	{
		if (desc.optionFlags & BufferOptions::generate_mip_maps)
		{
			return CE_ERR_INVALID_PARAM;
		}

		// Allocate texture space
		for (GLint k = 0; k < mipLevels; ++k)
		{
			Ceng::INT32 width = desc.width >> k;
			if (width < 1) width = 1;

			Ceng::INT32 height = desc.height >> k;
			if (height < 1) height = 1;

			if (gl_format.compressed == true)
			{
				glCompressedTexImage2D(GL_TEXTURE_2D, k, gl_format.internalFormat, width,
					height, 0, initialData[k].compressedSize, nullptr);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, k, gl_format.internalFormat, width,
					height, 0, gl_format.format, gl_format.type, nullptr);
			}

			gl_result = glGetError();
			if (gl_result != GL_NO_ERROR)
			{
				switch (gl_result)
				{
				case GL_INVALID_ENUM:
					return CE_ERR_INVALID_PARAM;
				case GL_INVALID_VALUE:
					return CE_ERR_INVALID_PARAM;
				case GL_INVALID_OPERATION:
					return CE_ERR_FAIL;
				case GL_OUT_OF_MEMORY:
					return CE_ERR_OUT_OF_VIDEO_MEMORY;
				};

				return CE_ERR_FAIL;
			}
		}
	}
	else
	{	
		if (gl_format.compressed || (desc.optionFlags & BufferOptions::generate_mip_maps)==0)
		{
			// Allocate texture space and load initial data if available
			for (GLint k = 0; k < mipLevels; ++k)
			{
				Ceng::INT32 width = desc.width >> k;
				if (width < 1) width = 1;

				Ceng::INT32 height = desc.height >> k;
				if (height < 1) height = 1;

				if (gl_format.compressed == true)
				{
					glCompressedTexImage2D(GL_TEXTURE_2D, k, gl_format.internalFormat, width, height, 0,
						initialData[k].compressedSize, initialData[k].sourcePtr);
				}
				else
				{
					glTexImage2D(GL_TEXTURE_2D, k, gl_format.internalFormat, width,
						height, 0, gl_format.format, gl_format.type, initialData[k].sourcePtr);
				}

				gl_result = glGetError();
				if (gl_result != GL_NO_ERROR)
				{
					switch (gl_result)
					{
					case GL_INVALID_ENUM:
						return CE_ERR_INVALID_PARAM;
					case GL_INVALID_VALUE:
						return CE_ERR_INVALID_PARAM;
					case GL_INVALID_OPERATION:
						return CE_ERR_FAIL;
					case GL_OUT_OF_MEMORY:
						return CE_ERR_OUT_OF_VIDEO_MEMORY;
					};

					return CE_ERR_FAIL;
				}
			}
		}
		else
		{
			// Create highest quality mip level
			glTexImage2D(GL_TEXTURE_2D, 0, gl_format.internalFormat, desc.width, desc.height,
				0, gl_format.format, gl_format.type, initialData->sourcePtr);

			gl_result = glGetError();
			if (gl_result != GL_NO_ERROR)
			{
				switch (gl_result)
				{
				case GL_INVALID_ENUM:
					return CE_ERR_INVALID_PARAM;
				case GL_INVALID_VALUE:
					return CE_ERR_INVALID_PARAM;
				case GL_INVALID_OPERATION:
					return CE_ERR_FAIL;
				case GL_OUT_OF_MEMORY:
					return CE_ERR_OUT_OF_VIDEO_MEMORY;
				};

				return CE_ERR_FAIL;
			}

			// Allocate texture space
			for (GLint k = 1; k < mipLevels; ++k)
			{
				Ceng::INT32 width = desc.width >> k;
				if (width < 1) width = 1;

				Ceng::INT32 height = desc.height >> k;
				if (height < 1) height = 1;

				glTexImage2D(GL_TEXTURE_2D, k, gl_format.internalFormat, width,
					height, 0, gl_format.format, gl_format.type, nullptr);

				gl_result = glGetError();
				if (gl_result != GL_NO_ERROR)
				{
					switch (gl_result)
					{
					case GL_INVALID_ENUM:
						return CE_ERR_INVALID_PARAM;
					case GL_INVALID_VALUE:
						return CE_ERR_INVALID_PARAM;
					case GL_INVALID_OPERATION:
						return CE_ERR_FAIL;
					case GL_OUT_OF_MEMORY:
						return CE_ERR_OUT_OF_VIDEO_MEMORY;
					};

					return CE_ERR_FAIL;
				}
			}
		}
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_Texture2D::GetInstance(const GL_Texture2dDesc &desc, const SubResourceData *initialData,
	GL32_Texture2D **output)
{
	CRESULT cresult;

	GLuint gl_textureID=0;
	GLenum gl_result=0;

	GLint mipLevels = 0;

	GL32_TextureFormat gl_format;

	gl_format.compressed = IsCompressed(desc.gl_internalFormat);

	gl_format.format = desc.gl_format;
	gl_format.internalFormat = desc.gl_internalFormat;
	gl_format.type = desc.gl_type;

	if (gl_format.compressed)
	{
		if (desc.sRGB == true)
		{
			GLenum newFormat;

			cresult = CompressedSRGB(gl_format.internalFormat, &newFormat);
			if (cresult != CE_OK)
			{
				return cresult;
			}

			gl_format.internalFormat = newFormat;
		}		

		cresult = IsSupported(gl_format.internalFormat);
		if (cresult != CE_OK)
		{
			return cresult;
		}
	}
	else
	{

	}

	mipLevels = desc.mipLevels;
	if (mipLevels == 0)
	{
		mipLevels = 1;
	}

	if ((desc.width >> (mipLevels - 1)) == 0 && (desc.height >> (mipLevels - 1)) == 0)
	{
		return CE_ERR_INVALID_PARAM;
	}

	glGenTextures(1, &gl_textureID);

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		switch (gl_result)
		{
		case GL_INVALID_ENUM:
			return CE_ERR_INVALID_PARAM;
		case GL_INVALID_VALUE:
			return CE_ERR_INVALID_PARAM;
		case GL_INVALID_OPERATION:
			return CE_ERR_FAIL;
		case GL_OUT_OF_MEMORY:
			return CE_ERR_OUT_OF_VIDEO_MEMORY;
		};

		return CE_ERR_FAIL;
	}

	Texture2dDesc defDesc;

	defDesc.width = desc.width;
	defDesc.height = desc.height;

	defDesc.arraySize = desc.arraySize;

	defDesc.mipLevels = desc.mipLevels;

	defDesc.multisampleDesc.count = desc.multisampleDesc.count;
	defDesc.multisampleDesc.quality = desc.multisampleDesc.quality;

	defDesc.bindFlags = desc.bindFlags;
	defDesc.cpuAccessFlags = desc.cpuAccessFlags;
	defDesc.optionFlags = desc.optionFlags;

	defDesc.format = IMAGE_FORMAT::UNKNOWN;

	defDesc.sRGB = desc.sRGB;

	// Store current texture unit state
	GLint gl_previousTex;
	GLint gl_previousType;

	GetPreviousTexBinding(gl_previousType, gl_previousTex);

	glBindTexture(GL_TEXTURE_2D, gl_textureID);

	cresult = GenerateTexture(defDesc, gl_format, mipLevels, initialData);

	// Restore texture unit state
	glBindTexture(gl_previousType,gl_previousTex);

	if (cresult != CE_OK)
	{
		glDeleteTextures(1, &gl_textureID);
		return cresult;
	}

	*output = new GL32_Texture2D(gl_textureID, gl_format, desc.width,desc.height,Ceng::IMAGE_FORMAT::UNKNOWN, desc.sRGB,mipLevels);

	if (!gl_format.compressed && (desc.optionFlags & Ceng::BufferOptions::generate_mip_maps))
	{
		return (*output)->GenerateMipmaps();
	}

	return CE_OK;
}

void GL32_Texture2D::GetPreviousTexBinding(GLint &gl_type, GLint &gl_texture)
{
	GLint gl_textureID=0;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &gl_textureID);

	if (gl_textureID != 0)
	{
		gl_type = GL_TEXTURE_2D;
		gl_texture = gl_textureID;
		return;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP, &gl_textureID);

	if (gl_textureID != 0)
	{
		gl_type = GL_TEXTURE_CUBE_MAP;
		gl_texture = gl_textureID;
		return;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_1D, &gl_textureID);

	if (gl_textureID != 0)
	{
		gl_type = GL_TEXTURE_1D;
		gl_texture = gl_textureID;
		return;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_1D_ARRAY, &gl_textureID);

	if (gl_textureID != 0)
	{
		gl_type = GL_TEXTURE_1D_ARRAY;
		gl_texture = gl_textureID;
		return;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D_ARRAY, &gl_textureID);

	if (gl_textureID != 0)
	{
		gl_type = GL_TEXTURE_2D_ARRAY;
		gl_texture = gl_textureID;
		return;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_CUBE_MAP_ARRAY, &gl_textureID);

	if (gl_textureID != 0)
	{
		gl_type = GL_TEXTURE_CUBE_MAP_ARRAY;
		gl_texture = gl_textureID;
		return;
	}

	gl_type = GL_TEXTURE_2D;
	gl_texture = 0;
}

const Ceng::CRESULT GL32_Texture2D::CompressedSRGB(const GLenum internalFormat,GLenum *new_format)
{
	switch (internalFormat)
	{
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
		*new_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
		break;
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
		*new_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
		break;
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
		*new_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT;
		break;
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		*new_format = GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT;
		break;
	case GL_COMPRESSED_RGB8_ETC2:
		*new_format = GL_COMPRESSED_SRGB8_ETC2;
		break;
	case GL_COMPRESSED_RGBA8_ETC2_EAC:
		*new_format = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC;
		break;
		
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_Texture2D::TranslateFormat(const Texture2dDesc &desc, GL32_TextureFormat *gl_format)
{
	// Check compressed formats first

	switch (desc.format)
	{
	case Ceng::IMAGE_FORMAT::dxt1:
		gl_format->internalFormat = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
		break;
	case Ceng::IMAGE_FORMAT::dxt3:
		gl_format->internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case Ceng::IMAGE_FORMAT::dxt5:
		gl_format->internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	case Ceng::IMAGE_FORMAT::bc4_r_snorm:
		gl_format->internalFormat = GL_COMPRESSED_SIGNED_RED_RGTC1;
		break;
	case Ceng::IMAGE_FORMAT::bc4_r_unorm:
		gl_format->internalFormat = GL_COMPRESSED_RED_RGTC1;
		break;
	case Ceng::IMAGE_FORMAT::bc5_rg_snorm:
		gl_format->internalFormat = GL_COMPRESSED_SIGNED_RG_RGTC2;
		break;
	case Ceng::IMAGE_FORMAT::bc5_rg_unorm:
		gl_format->internalFormat = GL_COMPRESSED_RG_RGTC2;
		break;
	case Ceng::IMAGE_FORMAT::bc6_rgb_float:
		gl_format->internalFormat = GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB;
		break;
	case Ceng::IMAGE_FORMAT::bc6_rgb_unsigned_float:
		gl_format->internalFormat = GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB;
		break;
	case Ceng::IMAGE_FORMAT::bc7_rgba_unorm:
		gl_format->internalFormat = GL_COMPRESSED_RGBA_BPTC_UNORM_ARB;
		break;
	case Ceng::IMAGE_FORMAT::bc7_srgb_alpha_unorm:
		gl_format->internalFormat = GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB;
		break;
	case Ceng::IMAGE_FORMAT::etc1_rgb:
		//if (!glewIsSupported("OES_compressed_ETC1_RGB8_texture"))
		//{
			return CE_ERR_NOT_SUPPORTED;
		//}

		//gl_format->internalFormat = GL_COMPRESSED_;
		break;
	case Ceng::IMAGE_FORMAT::etc2_rgb8:
		gl_format->internalFormat = GL_COMPRESSED_RGB8_ETC2;
		break;
	case Ceng::IMAGE_FORMAT::etc2_srgb8:
		gl_format->internalFormat = GL_COMPRESSED_SRGB8_ETC2;
		break;
	case Ceng::IMAGE_FORMAT::etc2_rgb8_a1:
		gl_format->internalFormat = GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2;
		break;
	case Ceng::IMAGE_FORMAT::etc2_srgb8_a1:
		gl_format->internalFormat = GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2;
		break;
	case Ceng::IMAGE_FORMAT::etc2_rgba8:
		gl_format->internalFormat = GL_COMPRESSED_RGBA8_ETC2_EAC;
		break;
	case Ceng::IMAGE_FORMAT::etc2_srgb8_a8:
		gl_format->internalFormat = GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC;
		break;
	case Ceng::IMAGE_FORMAT::eac_r11_unsigned:
		gl_format->internalFormat = GL_COMPRESSED_R11_EAC;
		break;
	case Ceng::IMAGE_FORMAT::eac_r11_signed:
		gl_format->internalFormat = GL_COMPRESSED_SIGNED_R11_EAC;
		break;
	case Ceng::IMAGE_FORMAT::eac_rg11_unsigned:
		gl_format->internalFormat = GL_COMPRESSED_RG11_EAC;
		break;
	case Ceng::IMAGE_FORMAT::eac_rg11_signed:
		gl_format->internalFormat = GL_COMPRESSED_SIGNED_RG11_EAC;
		break;
	case Ceng::IMAGE_FORMAT::normal_3dc:
		gl_format->internalFormat = GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT;
		//gl_format->internalFormat = GL_COMPRESSED_LUMINANCE_ALPHA_3DC_ATI;
		break;
	default:
		break;
	}

	gl_format->compressed = IsCompressed(gl_format->internalFormat);
	if (gl_format->compressed)
	{
		if (desc.sRGB == true)
		{
			GLenum newFormat;

			CRESULT cresult = CompressedSRGB(gl_format->internalFormat,&newFormat);
			if (cresult != CE_OK)
			{
				return cresult;
			}

			gl_format->internalFormat = newFormat;

		}

		CRESULT cresult = IsSupported(gl_format->internalFormat);
		return cresult;
	}

	GLint srgb_format;

	switch (desc.format)
	{
	case Ceng::IMAGE_FORMAT::C32_ARGB:
		gl_format->type = GL_UNSIGNED_BYTE;
		gl_format->format = GL_BGRA;
		gl_format->internalFormat = GL_RGBA8;
		srgb_format = GL_SRGB8_ALPHA8;
		break;
	case Ceng::IMAGE_FORMAT::C24_RGB:
		gl_format->type = GL_UNSIGNED_BYTE;
		gl_format->format = GL_BGR;
		gl_format->internalFormat = GL_RGB8;
		srgb_format = GL_SRGB8;
		break;
	case Ceng::IMAGE_FORMAT::C32_ABGR:
		gl_format->type = GL_UNSIGNED_BYTE;
		gl_format->format = GL_RGBA;
		gl_format->internalFormat = GL_RGBA8;
		srgb_format = GL_SRGB8_ALPHA8;
		break;
	case Ceng::IMAGE_FORMAT::C24_BGR:
		gl_format->type = GL_UNSIGNED_BYTE;
		gl_format->format = GL_RGB;
		gl_format->internalFormat = GL_RGB8;
		srgb_format = GL_SRGB8;
		break;
	case Ceng::IMAGE_FORMAT::CF16_ABGR:
		gl_format->type = GL_HALF_FLOAT;
		gl_format->format = GL_RGBA;
		gl_format->internalFormat = GL_RGBA16F;
		break;
	case Ceng::IMAGE_FORMAT::CF32_ABGR:
		gl_format->type = GL_FLOAT;
		gl_format->format = GL_RGBA;
		gl_format->internalFormat = GL_RGBA32F;
		break;
	case Ceng::IMAGE_FORMAT::D32F:
		gl_format->type = GL_FLOAT;
		gl_format->format = GL_DEPTH_COMPONENT;
		gl_format->internalFormat = GL_DEPTH_COMPONENT32F;
		break;
	case Ceng::IMAGE_FORMAT::D24_S8:
		gl_format->type = GL_UNSIGNED_BYTE;
		gl_format->format = GL_DEPTH_COMPONENT;
		gl_format->internalFormat = GL_DEPTH24_STENCIL8;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	if (desc.sRGB == true)
	{
		gl_format->internalFormat = srgb_format;
	}

	return CE_OK;
}

const Ceng::BOOL GL32_Texture2D::IsCompressed(const GLint internalFormat)
{
	switch (internalFormat)
	{
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT: 	// dxt1	
	case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT: // sRGB dxt1
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT: // sRGB dxt1a
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT: 	// dxt3
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT: // sRGB dxt3
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT: 	// dxt5
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT: // sRGB dxt5
	case GL_COMPRESSED_RGB8_ETC2: // etc2 rgb8
	case GL_COMPRESSED_SRGB8_ETC2: 	// sRGB etc2
	case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2: // etc2_alpha1
	case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2: // sRGB etc2_alpha1
	case GL_COMPRESSED_RGBA8_ETC2_EAC: // etc2 rgba8
	case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC: // sRGB etc2 rgb8 alpha8
	case GL_COMPRESSED_R11_EAC:
	case GL_COMPRESSED_SIGNED_R11_EAC:
	case GL_COMPRESSED_RG11_EAC:
	case GL_COMPRESSED_SIGNED_RG11_EAC:

	case GL_COMPRESSED_RED_RGTC1:
	case GL_COMPRESSED_SIGNED_RED_RGTC1:

	case GL_COMPRESSED_RG_RGTC2:
	case GL_COMPRESSED_SIGNED_RG_RGTC2:

	case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB: // bc6
	case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB: // bc6
	case GL_COMPRESSED_RGBA_BPTC_UNORM_ARB: // bc7
	case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB: // bc7

	case GL_COMPRESSED_LUMINANCE_ALPHA_3DC_ATI: // ATI 3Dc
	case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT: // ATI 3Dc
		
		return true;
	default:
		break;
	}

	return false;
}

const Ceng::CRESULT GL32_Texture2D::IsSupported(const GLint compressedFormat)
{
	switch (compressedFormat)
	{
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
	case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
		if (!glewIsSupported("GL_EXT_texture_compression_s3tc") && !glewIsSupported("GL_EXT_texture_compression_dxt1"))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		break;
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
		if (!glewIsSupported("GL_EXT_texture_compression_s3tc"))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		break;
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		if (!glewIsSupported("GL_EXT_texture_compression_s3tc"))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		break;
	case GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT_ARB: // bc6
	case GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT_ARB: // bc6
	case GL_COMPRESSED_RGBA_BPTC_UNORM_ARB: // bc7
	case GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM_ARB: // bc7
		if (!glewIsSupported("GL_ARB_texture_compression_bptc"))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		break;
	case GL_COMPRESSED_RGB8_ETC2:
	case GL_COMPRESSED_SRGB8_ETC2:
	case GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
	case GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
	case GL_COMPRESSED_RGBA8_ETC2_EAC:
	case GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC:
	case GL_COMPRESSED_R11_EAC:
	case GL_COMPRESSED_SIGNED_R11_EAC:
	case GL_COMPRESSED_RG11_EAC:
	case GL_COMPRESSED_SIGNED_RG11_EAC:
		if (!glewIsSupported("GL_ARB_ES3_compatibility"))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		break;
	case GL_COMPRESSED_LUMINANCE_ALPHA_3DC_ATI:
	case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT:
		if (!glewIsExtensionSupported("GL_EXT_texture_compression_latc"))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		break;
	case GL_COMPRESSED_RED_RGTC1:
	case GL_COMPRESSED_SIGNED_RED_RGTC1:
	case GL_COMPRESSED_RG_RGTC2:
	case GL_COMPRESSED_SIGNED_RG_RGTC2:
		if (!glewIsExtensionSupported("GL_ARB_texture_compression_rgtc"))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}

	return CE_OK;
}

const CRESULT GL32_Texture2D::GetBufferData2D(Ceng::BufferData2D *dataPtr)
{
	dataPtr->width = width;
	dataPtr->height = height;
	
	dataPtr->mipLevels = mipLevels;

	return CE_OK;
}

const BufferType::value GL32_Texture2D::GetResourceType()
{
	return BufferType::texture_2d;
}

const Ceng::CRESULT GL32_Texture2D::GetShaderViewTex2D(const Ceng::ShaderResourceViewDesc &desc, Ceng::ShaderResourceView **resourceView)
{
	/*
	if (desc.format != imageFormat)
	{
		return CE_ERR_NOT_SUPPORTED;
	}
	*/

	if (desc.tex2d.baseMipLevel > Ceng::UINT32(mipLevels))
	{
		return CE_ERR_INVALID_PARAM;
	}

	GLint maxMipLevel = desc.tex2d.maxMipLevel;

	if (maxMipLevel == -1)
	{
		maxMipLevel = mipLevels;
	}
	else if (desc.tex2d.maxMipLevel > Ceng::UINT32(mipLevels))
	{
		return CE_ERR_INVALID_PARAM;
	}

	*resourceView = (ShaderResourceView*)new GL32_ShaderViewTex2D(this,gl_textureID, GL_TEXTURE_2D,desc.tex2d.baseMipLevel, maxMipLevel);

	return CE_OK;
}

const Ceng::CRESULT GL32_Texture2D::GetRenderTargetView(const Ceng::RenderTargetViewDesc &desc,
	Ceng::RenderTargetView **targetView)
{
	if (desc.tex2d.mipSlice >= Ceng::UINT32(mipLevels))
	{
		return CE_ERR_INVALID_PARAM;
	}

	*targetView = (RenderTargetView*)new GL32_RenderTexture2D(this, desc.tex2d.mipSlice);

	return CE_OK;
}

const CRESULT GL32_Texture2D::GL_GenerateMipmaps()
{
	GLint gl_oldType;
	GLint gl_oldId;

	// Store old texture binding
	GetPreviousTexBinding(gl_oldType, gl_oldId);

	glBindTexture(GL_TEXTURE_2D, gl_textureID);

	glGenerateMipmap(GL_TEXTURE_2D);

	// Restore previous texture binding
	glBindTexture(gl_oldType, gl_oldId);

	return CE_OK;

}

const CRESULT GL32_Texture2D::GenerateMipmaps()
{
	if (gl_format.compressed == true)
	{
		return CE_OK;
	}

	if (sRGB == false ||
		glewIsSupported("GL_EXT_texture_sRGB_decode"))
	{
		return GL_GenerateMipmaps();
	}
	else
	{
		// Manual mipmap generation
		return GL_GenerateMipmaps();
	}

	return CE_OK;
}

const Ceng::CRESULT GL32_Texture2D::GetSubResourceData(const Ceng::UINT32 mipLevel, void *destPtr)
{
	return CE_OK;
}