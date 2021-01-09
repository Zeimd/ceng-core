/*****************************************************************************
*
* gl32-cubemap.cpp
*
* Created By Jari Korkala 20/11/2015
*
*****************************************************************************/

#include <ceng/datatypes/sub-resource-data.h>
#include <ceng/datatypes/bufferdata-2d.h>

#include "../inc/gl32-cubemap.h"
#include "../inc/gl32-view-cubemap.h"

using namespace Ceng;

GL32_Cubemap::GL32_Cubemap()
{
}

GL32_Cubemap::GL32_Cubemap(const GLuint gl_textureID, const GL32_TextureFormat &gl_format, 
	const Ceng::UINT32 width, const Ceng::UINT32 height,const Ceng::IMAGE_FORMAT::value imageFormat,
	const Ceng::BOOL sRGB,const GLint mipLevels)
	: GL32_Texture2D(gl_textureID,gl_format,width,height,imageFormat,0,mipLevels)
{
}

GL32_Cubemap::~GL32_Cubemap()
{
}

void GL32_Cubemap::Release()
{
	delete this;
}

const Ceng::CRESULT GL32_Cubemap::GetInstance(const Texture2dDesc &desc,
	const SubResourceData *initialData, Ceng::GL32_Cubemap **output)
{
	GLuint gl_textureID=0;
	GLenum gl_result=0;

	GL32_TextureFormat gl_format;

	CRESULT cresult = TranslateFormat(desc, &gl_format);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	// Don't allow more mipmaps than possible

	GLint mipLevels = MaxMipLevel(desc.width, desc.height);

	if (desc.mipLevels != 0)
	{
		if (desc.mipLevels > mipLevels)
		{
			return CE_ERR_INVALID_PARAM;
		}
		mipLevels = desc.mipLevels;
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

	glBindTexture(GL_TEXTURE_CUBE_MAP, gl_textureID);

	GetPreviousTexBinding(gl_previousType, gl_previousTex);

	cresult = GenerateCubemap(desc, gl_format, mipLevels, initialData);

	// Restore texture unit state
	glBindTexture(gl_previousType, gl_previousTex);

	if (cresult != CE_OK)
	{
		glDeleteTextures(1, &gl_textureID);
		return cresult;
	}

	*output = new GL32_Cubemap(gl_textureID, gl_format, desc.width,desc.height,desc.format,desc.sRGB, mipLevels);

	if (desc.optionFlags & Ceng::BufferOptions::generate_mip_maps)
	{
		return (*output)->GenerateMipmaps();
	}

	return CE_OK;
}

const CRESULT GL32_Cubemap::GL_GenerateMipmaps()
{
	GLint gl_oldType;
	GLint gl_oldId;

	// Store old texture binding
	GetPreviousTexBinding(gl_oldType, gl_oldId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, gl_textureID);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	// Restore previous texture binding
	glBindTexture(gl_oldType, gl_oldId);

	return CE_OK;
}


const GLenum faceArray[] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

const Ceng::CRESULT GL32_Cubemap::GenerateCubemap(const Texture2dDesc &desc, const GL32_TextureFormat &gl_format,
	GLint &mipLevels, const SubResourceData *initialData)
{
	GLenum gl_result;

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
		for (Ceng::UINT32 face = 0; face < 6; ++face)
		{
			for (Ceng::UINT32 k = 0; k < mipLevels; ++k)
			{
				Ceng::INT32 width = desc.width >> k;
				if (width < 1) width = 1;

				Ceng::INT32 height = desc.height >> k;
				if (height < 1) height = 1;

				if (gl_format.compressed == true)
				{
					glCompressedTexImage2D(faceArray[face], k, gl_format.internalFormat, width,
						height, 0, initialData[k+mipLevels*face].compressedSize, nullptr);
				}
				else
				{
					glTexImage2D(faceArray[face], k, gl_format.internalFormat, width,
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
	}
	else
	{
		if (desc.optionFlags & BufferOptions::generate_mip_maps)
		{
			for (Ceng::UINT32 face = 0; face < 6; ++face)
			{
				// Create highest quality mip level
				glTexImage2D(faceArray[face], 0, gl_format.internalFormat, desc.width, desc.height,
					0, gl_format.format, gl_format.type, initialData[face].sourcePtr);

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
				for (Ceng::UINT32 k = 1; k < mipLevels; ++k)
				{
					Ceng::INT32 width = desc.width >> k;
					if (width < 1) width = 1;

					Ceng::INT32 height = desc.height >> k;
					if (height < 1) height = 1;

					glTexImage2D(faceArray[face], k, gl_format.internalFormat, width,
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
		else
		{
			// Allocate texture space and load initial data if available
			for (Ceng::UINT32 face = 0; face < 6; ++face)
			{
				for (Ceng::UINT32 k = 0; k < mipLevels; ++k)
				{
					Ceng::INT32 width = desc.width >> k;
					if (width < 1) width = 1;

					Ceng::INT32 height = desc.height >> k;
					if (height < 1) height = 1;

					if (gl_format.compressed == true)
					{
						glCompressedTexImage2D(faceArray[face], k, gl_format.internalFormat, width, height, 0,
							initialData[k].compressedSize, initialData[k+mipLevels*face].sourcePtr);
					}
					else
					{
						glTexImage2D(faceArray[face], k, gl_format.internalFormat, width,
							height, 0, gl_format.format, gl_format.type, initialData[k+mipLevels*face].sourcePtr);
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
		}
	}

	return CE_OK;
}

const CRESULT GL32_Cubemap::GetBufferData2D(Ceng::BufferData2D *dataPtr)
{
	dataPtr->format = imageFormat;

	dataPtr->width = width;
	dataPtr->height = height;

	dataPtr->mipLevels = mipLevels;
	return CE_OK;
}

const Ceng::CRESULT GL32_Cubemap::GetShaderViewCubemap(const Ceng::ShaderResourceViewDesc &desc,
	Ceng::ShaderResourceView **resourceView)
{
	if (desc.cubeMap.baseMipLevel > mipLevels)
	{
		return CE_ERR_INVALID_PARAM;
	}

	GLint maxMipLevel = desc.cubeMap.maxMipLevel;

	if (maxMipLevel == -1)
	{
		maxMipLevel = mipLevels;
	}
	else if (desc.cubeMap.maxMipLevel > mipLevels)
	{
		return CE_ERR_INVALID_PARAM;
	}

	*resourceView = (ShaderResourceView*)new GL32_ShaderViewCubemap(this, desc.cubeMap.baseMipLevel, maxMipLevel);


	return CE_OK;
}

const Ceng::CRESULT GL32_Cubemap::GetSubResourceData(const Ceng::CubemapFace::value face,
	const Ceng::UINT32 mipLevel, const Ceng::IMAGE_FORMAT::value destFormat,void *destPtr)
{
	if (mipLevel > mipLevels)
	{
		return CE_ERR_INVALID_PARAM;
	}

	// Correct pixel transfer mode

	glPixelStorei(GL_PACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_PACK_LSB_FIRST, GL_FALSE);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);

	// Determine destination format

	GL32_TextureFormat gl_destFormat;

	Texture2dDesc desc;

	desc.format = destFormat;

	Ceng::CRESULT cresult = TranslateFormat(desc, &gl_destFormat);
	if (cresult != Ceng::CE_OK)
	{
		return CE_ERR_INCOMPATIBLE_FORMAT;
	}

	// Store current texture binding

	GLint gl_oldType;
	GLint gl_oldId;

	GetPreviousTexBinding(gl_oldType, gl_oldId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, gl_textureID);

	glGetTexImage(faceArray[face], mipLevel, gl_destFormat.format, gl_destFormat.type, destPtr);

	GLenum gl_result = glGetError();

	if (gl_result != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	// Restore previous texture binding
	glBindTexture(gl_oldType, gl_oldId);

	return CE_OK;
}

const Ceng::CRESULT GL32_Cubemap::SetSubResourceData(const Ceng::CubemapFace::value face,
	const Ceng::UINT32 mipLevel, const Ceng::IMAGE_FORMAT::value sourceFormat,void *sourcePtr)
{
	if (mipLevel > mipLevels)
	{
		return CE_ERR_INVALID_PARAM;
	}

	// Determine source format

	GL32_TextureFormat gl_sourceFormat;

	Texture2dDesc desc;

	desc.format = sourceFormat;

	Ceng::CRESULT cresult = TranslateFormat(desc, &gl_sourceFormat);
	if (cresult != Ceng::CE_OK)
	{
		return CE_ERR_INCOMPATIBLE_FORMAT;
	}

	// Correct pixel transfer mode

	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Store current texture binding

	GLint gl_oldType;
	GLint gl_oldId;

	GetPreviousTexBinding(gl_oldType, gl_oldId);

	glBindTexture(GL_TEXTURE_CUBE_MAP, gl_textureID);

	Ceng::UINT32 mipWidth = width >> mipLevel;
	Ceng::UINT32 mipHeight = height >> mipLevel;

	glTexSubImage2D(faceArray[face], mipLevel, 0,0,mipWidth,mipHeight,gl_sourceFormat.format, gl_sourceFormat.type, sourcePtr);

	GLenum gl_result = glGetError();

	if (gl_result != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	// Restore previous texture binding
	glBindTexture(gl_oldType, gl_oldId);

	return CE_OK;
}