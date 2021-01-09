/*****************************************************************************
*
* gl33-device.cpp
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#include "../inc/gl33-device.h"

#include "../inc/gl33-vertex-format.h"
#include "../inc/gl32-vertex-buffer.h"
#include "../inc/gl32-vertex-shader.h"
#include "../inc/gl32-pixel-shader.h"
#include "../inc/gl32-shader-program.h"
#include "../inc/gl32-texture-2d.h"
#include "../inc/gl32-sampler-state.h"
#include "../inc/gl32-index-buffer.h"
#include "../inc/gl32-blend-state.h"

#include "../inc/gl32-cubemap.h"

#include "../inc/gl32-depth-stencil-state.h"

using namespace Ceng;

GL33_RenderDevice::GL33_RenderDevice()
{
}

GL33_RenderDevice::GL33_RenderDevice(PlatformWindow *window, ::HDC deviceHandle, ::HGLRC gl_context)
	: window(window),deviceHandle(deviceHandle),gl_context(gl_context)
{

}

GL33_RenderDevice::~GL33_RenderDevice()
{
	if (gl_context != nullptr)
	{
		wglMakeCurrent(NULL, NULL);
	}
}

void GL33_RenderDevice::Release()
{
	delete this;
}

const Ceng::CRESULT GL33_RenderDevice::CreateVertexShader(const Ceng::StringUtf8 &shaderText, Ceng::VertexShader **shaderPtr)
{
	GL32_VertexShader *gl_shader;

	CRESULT cresult = GL32_VertexShader::GetInstance(shaderText,&gl_shader);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*shaderPtr = (VertexShader*)gl_shader;
	return CE_OK;
}

CRESULT GL33_RenderDevice::CreateVertexFormat(const std::vector < Ceng::VertexDeclData > &vertexDecl,
	Ceng::VertexFormat **format)
{
	GL33_VertexFormat *gl_format;

	CRESULT cresult = GL33_VertexFormat::GetInstance(vertexDecl,&gl_format);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*format = (VertexFormat*)gl_format;

	return CE_OK;
}

CRESULT GL33_RenderDevice::CreateVertexBuffer(Ceng::UINT32 vertexSizeBytes,
	Ceng::UINT32 vertexNum,Ceng::UINT32 usage,
	Ceng::VertexBuffer **destPtr)
{
	GL32_VertexBuffer *gl_buffer;

	CRESULT cresult = GL32_VertexBuffer::GetInstance(vertexSizeBytes, vertexNum, usage, &gl_buffer);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*destPtr = (VertexBuffer*)gl_buffer;

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderDevice::CreateIndexBuffer(const Ceng::UINT32 elementSize, const Ceng::UINT32 elements, 
	const Ceng::UINT32 usage, void *initialData,Ceng::IndexBuffer **destPtr)
{
	GL32_IndexBuffer *gl_buffer;

	CRESULT cresult = GL32_IndexBuffer::GetInstance(elementSize,elements,usage,initialData, &gl_buffer);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*destPtr = (IndexBuffer*)gl_buffer;

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderDevice::CreatePixelShader(const Ceng::StringUtf8 &shaderText, Ceng::PixelShader **shaderPtr)
{
	GL32_PixelShader *gl_shader;

	CRESULT cresult = GL32_PixelShader::GetInstance(shaderText, &gl_shader);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*shaderPtr = (PixelShader*)gl_shader;
	return CE_OK;
}

const Ceng::CRESULT GL33_RenderDevice::CreateShaderProgram(Ceng::VertexShader *vertexShader, 
	Ceng::PixelShader *pixelShader, Ceng::ShaderProgram **program)
{
	GL32_ShaderProgram *gl_program;

	CRESULT cresult = GL32_ShaderProgram::GetInstance(vertexShader,pixelShader,&gl_program);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*program = (ShaderProgram*)gl_program;
	return CE_OK;
}

const CRESULT GL33_RenderDevice::CreateSamplerState(const SamplerStateDesc &desc,
	Ceng::SamplerState **out_state)
{
	GL32_SamplerState *gl_state;

	CRESULT cresult = GL32_SamplerState::GetInstance(desc, &gl_state);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*out_state = (SamplerState*)gl_state;
	return CE_OK;
}

const CRESULT GL33_RenderDevice::CreateBlendState(BlendStateDesc *desc, BlendState **statePtr)
{
	GL32_BlendState *gl_state;

	CRESULT cresult = GL32_BlendState::GetInstance(desc, &gl_state);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*statePtr = (BlendState*)gl_state;
	return CE_OK;
}

const Ceng::CRESULT GL33_RenderDevice::CreateDepthStencilState(const DepthStencilDesc &desc, DepthStencilState **statePtr)
{
	GL32_DepthStencilState *gl_state;

	CRESULT cresult = GL32_DepthStencilState::GetInstance(desc, &gl_state);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*statePtr = (DepthStencilState*)gl_state;
	return CE_OK;
}

const CRESULT GL33_RenderDevice::CreateShaderResourceView(RenderResource *resource,
	ShaderResourceViewDesc &desc,
	ShaderResourceView **out_resourceView)
{
	return CE_OK;
}

const CRESULT GL33_RenderDevice::CreateTexture2D(const Texture2dDesc &desc,
	const SubResourceData *initialData,Ceng::Texture2D **texturePtr)
{
	GL32_Texture2D *gl_texture;

	CRESULT cresult = GL32_Texture2D::GetInstance(desc, initialData,&gl_texture);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*texturePtr = (Texture2D*)gl_texture;

	return CE_OK;
}

const CRESULT GL33_RenderDevice::CreateTexture2D(const GL_Texture2dDesc &desc,
	const SubResourceData *initialData, Ceng::Texture2D **texturePtr)
{
	GL32_Texture2D *gl_texture;

	CRESULT cresult = GL32_Texture2D::GetInstance(desc, initialData, &gl_texture);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*texturePtr = (Texture2D*)gl_texture;

	return CE_OK;
}

const CRESULT GL33_RenderDevice::CreateCubemap(const Texture2dDesc &desc,
	const SubResourceData *initialData, Ceng::Cubemap **texturePtr)
{
	GL32_Cubemap *gl_texture;

	CRESULT cresult = GL32_Cubemap::GetInstance(desc, initialData, &gl_texture);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	*texturePtr = (Cubemap*)gl_texture;
	return CE_OK;
}

const Ceng::FLOAT32 degrees_to_radians = 3.14159f / 180.0f;

const CRESULT GL33_RenderDevice::CreateProjectionMatrix(const Ceng::INT32 displayWidth, const Ceng::INT32 displayHeight,
	const Ceng::FLOAT32 horizontalField,
	const Ceng::FLOAT32 zNear,
	const Ceng::FLOAT32 zFar,
	Ceng::Matrix4 *dest)
{
	Ceng::FLOAT32 depthDiv = 1.0f / Ceng::FLOAT32(zFar - zNear);

	FLOAT32 dilation;
	FLOAT32 aspectRatio;

	dilation = FLOAT32(1.0f) /
		tan(FLOAT32(0.5f)*horizontalField*degrees_to_radians);

	aspectRatio = (FLOAT32(displayWidth) / FLOAT32(displayHeight));

	dest->data[0][0] = dilation;
	dest->data[0][1] = 0.0f;
	dest->data[0][2] = 0.0f;
	dest->data[0][3] = 0.0f;

	dest->data[1][0] = 0.0f;
	dest->data[1][1] = aspectRatio*dilation;
	dest->data[1][2] = 0.0f;
	dest->data[1][3] = 0.0f;

	dest->data[2][0] = 0.0f;
	dest->data[2][1] = 0.0f;
	dest->data[2][2] = -(zFar + zNear)*depthDiv;
	dest->data[2][3] = -2.0f*zFar*zNear*depthDiv;

	dest->data[3][0] = 0.0f;
	dest->data[3][1] = 0.0f;
	dest->data[3][2] = -1.0f;
	dest->data[3][3] = 0.0f;

	return CE_OK;
}

const Ceng::UINT32 GL33_RenderDevice::GetOptimalVertexElements()
{
	GLint gl_count;
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &gl_count);

	return gl_count;
}

const Ceng::UINT32 GL33_RenderDevice::GetOptimalIndexElements()
{
	GLint gl_count;
	glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &gl_count);

	return gl_count;
}