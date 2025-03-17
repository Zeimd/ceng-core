/*****************************************************************************
*
* gl33-context.cpp
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#include <gl/glew.h>

#include <ceng/datatypes/color-format.h>
#include <ceng/datatypes/render-target-view-desc.h>

#include "../inc/gl32-depth-stencil-state.h"

#include <ceng/datatypes/blend-state-desc.h>
#include "../inc/gl32-blend-state.h"

#include "../inc/gl33-context.h"
#include "../inc/gl32-shader-program.h"
#include "../inc/gl33-vertex-format.h"
#include "../inc/gl32-vertex-buffer.h"

#include "../inc/gl33-device.h"

#include <ceng/interfaces/rasterizer-state.h>
#include <ceng/interfaces/depth-stencil-desc.h>
#include <ceng/interfaces/index-buffer.h>

#include <ceng/datatypes/tex2d-desc.h>

#include "../inc/gl32-texture-2d.h"

#include "../inc/gl32-vertex-shader.h"
#include "../inc/gl32-pixel-shader.h"

#include "../inc/gl32-sampler-state.h"
#include "../inc/gl32-view-tex2d.h"

#include "../inc/gl32-render-target-view.h"

using namespace Ceng;

GL33_RenderContext::GL33_RenderContext()
{
}

GL33_RenderContext::GL33_RenderContext(PlatformWindow *window, ::HDC deviceHandle, ::HGLRC gl_context,
	GL33_RenderDevice *renderDevice)
	: window(window),deviceHandle(deviceHandle),gl_context(gl_context),renderDevice(renderDevice),
	vertexStreams(std::vector<GL32_VertexStreamState>(max_vertex_streams,GL32_VertexStreamState())),
	gl_vertexBuffer(0),shaderProgram(nullptr),vertexFormat(nullptr),nextVertexFormat(nullptr),depthTarget(nullptr),
	blendState(nullptr),depthStencilState(nullptr)
{
	GLenum glResult;

	// Create and bind compulsory vertex array object

	glGenVertexArrays(1, &gl_vertexArray);
	glBindVertexArray(gl_vertexArray);

	// Create framebuffer object and bind it

	glGenFramebuffers(1, &gl_frameBufferObject);

	glResult = glGetError();
	if (glResult != GL_NO_ERROR)
	{
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER,gl_frameBufferObject);

	glResult = glGetError();
	if (glResult != GL_NO_ERROR)
	{
		return;
	}

	// Create proxy front buffer

	Texture2dDesc desc;

	Ceng::UINT32 width, height;

	window->GetClientArea(&width, &height);

	defaultViewport.x = 0;
	defaultViewport.y = 0;
	defaultViewport.width = width;
	defaultViewport.height = height;

	memcpy(&viewport, &defaultViewport, sizeof(Viewport));

	desc.width = width;
	desc.height = height;
	desc.format = IMAGE_FORMAT::unorm_a8_b8_g8_r8;
	desc.mipLevels = 1;
	desc.arraySize = 1;

	desc.sRGB = false;

	desc.multisampleDesc.count = 0;
	desc.multisampleDesc.quality = 0;

	desc.usage = BufferUsage::gpu_read_write;
	desc.bindFlags = BufferBinding::render_target | BufferBinding::shader_resource;
	desc.cpuAccessFlags = 0;
	desc.optionFlags = 0;

	CRESULT cresult = renderDevice->CreateTexture2D(desc, nullptr, (Ceng::Texture2D**)&frontBuffer);
	if (cresult != CE_OK)
	{
		return;
	}

	// Bind proxy buffer

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frontBuffer->gl_textureID, 0);

	glResult = glGetError();
	if (glResult != GL_NO_ERROR)
	{
		return;
	}

	// Default depth target

	glGenRenderbuffers(1, &gl_defaultDepthBuffer);

	glBindRenderbuffer(GL_RENDERBUFFER, gl_defaultDepthBuffer);

	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8, width, height);

	glResult = glGetError();
	if (glResult != GL_NO_ERROR)
	{
		return;
	}

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, gl_defaultDepthBuffer);

	glResult = glGetError();
	if (glResult != GL_NO_ERROR)
	{
		return;
	}

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	// Draw buffers
	GLenum drawBuffer = GL_COLOR_ATTACHMENT0;
	
	glDrawBuffers(1, &drawBuffer);

	glResult = glGetError();
	if (glResult != GL_NO_ERROR)
	{
		return;
	}

	Ceng::BOOL complete = FramebufferValid();
	if (complete == false)
	{
		return;
	}

	RenderTargetViewDesc targetDesc;

	targetDesc.type = BufferType::texture_2d;
	targetDesc.tex2d.mipSlice = 0;

	cresult = frontBuffer->GetRenderTargetView(targetDesc, (RenderTargetView**)&frontBufferTarget);
	if (cresult != CE_OK)
	{
		return;
	}

	// Vertex format for full screen quad

	std::vector<Ceng::VertexDeclData> progVertexDecl;

	Ceng::VertexDeclData declVar;

	declVar = Ceng::VertexDeclData(0, 0, Ceng::VTX_DATATYPE::FLOAT3, sizeof(VertexData), "position");
	progVertexDecl.push_back(declVar);

	declVar = Ceng::VertexDeclData(0, 12, Ceng::VTX_DATATYPE::FLOAT2, sizeof(VertexData), "textureUV");
	progVertexDecl.push_back(declVar);

	progVertexDecl.push_back(Ceng::VTX_DECL_END);

	cresult = renderDevice->CreateVertexFormat(progVertexDecl, (VertexFormat**)&quadFormat);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	// Vertex buffer for drawing proxy buffer

	fullScreenQuad[0].position.x = -1.0f;
	fullScreenQuad[0].position.y = -1.0f;
	fullScreenQuad[0].position.z = 1.0f;
	fullScreenQuad[0].texCoord.u = 0.0f;
	fullScreenQuad[0].texCoord.v = 0.0f;

	fullScreenQuad[1].position.x = 1.0f;
	fullScreenQuad[1].position.y = -1.0f;
	fullScreenQuad[1].position.z = 1.0f;
	fullScreenQuad[1].texCoord.u = 1.0f;
	fullScreenQuad[1].texCoord.v = 0.0f;
	
	fullScreenQuad[2].position.x = 1.0f;
	fullScreenQuad[2].position.y = 1.0f;
	fullScreenQuad[2].position.z = 1.0f;
	fullScreenQuad[2].texCoord.u = 1.0f;
	fullScreenQuad[2].texCoord.v = 1.0f;

	fullScreenQuad[3].position.x = -1.0f;
	fullScreenQuad[3].position.y = 1.0f;
	fullScreenQuad[3].position.z = 1.0f;
	fullScreenQuad[3].texCoord.u = 0.0f;
	fullScreenQuad[3].texCoord.v = 1.0f;

	cresult = renderDevice->CreateVertexBuffer(sizeof(VertexData), 4, BufferUsage::gpu_read_only, (VertexBuffer**)&quadBuffer);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	quadBuffer->LoadData(fullScreenQuad);

	fullScreenIndices[0] = 0;
	fullScreenIndices[1] = 1;
	fullScreenIndices[2] = 2;
	fullScreenIndices[3] = 0;
	fullScreenIndices[4] = 2;
	fullScreenIndices[5] = 3;

	cresult = renderDevice->CreateIndexBuffer(1, 6, BufferUsage::gpu_read_only, fullScreenIndices, (IndexBuffer**)&quadIndices);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	// Shaders for drawing full screen quad

	Ceng::StringUtf8 vertexText;

	vertexText += "#version 330 core\n";
	
	vertexText += "in vec3 position;\n";
	vertexText += "in vec2 textureUV;\n";

	vertexText += "out vec2 f_uv;\n";

	vertexText += "void main()\n";
	vertexText += "{\n";

	vertexText += "gl_Position = vec4(position.xy,0.0,1.0);\n";

	vertexText += "f_uv = textureUV;\n";

	vertexText += "}\n";

	cresult = renderDevice->CreateVertexShader(vertexText, (VertexShader**)&quadVshader);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	Ceng::StringUtf8 pixelText;

	pixelText += "#version 330 core\n";

	pixelText += "in vec2 f_uv;\n";

	pixelText += "uniform sampler2D texture;\n";

	pixelText += "out vec4 color;\n";

	pixelText += "void main()\n";
	pixelText += "{\n";

	pixelText += "vec4 diffuse = texture2D(texture,f_uv);\n";
	pixelText += "color = pow(diffuse,vec4(1.0/2.2,1.0/2.2,1.0/2.2,1.0));\n";
	//pixelText += "color = diffuse;\n";

	pixelText += "}\n";

	cresult = renderDevice->CreatePixelShader(pixelText, (PixelShader**)&quadPshader);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	cresult = renderDevice->CreateShaderProgram(quadVshader, quadPshader, (ShaderProgram**)&quadProgram);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	cresult = quadProgram->GetConstant("texture", &ps_texture);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	// Nearest sampler

	SamplerStateDesc samplerDesc;

	samplerDesc.addressU = TextureAddressMode::clamp;
	samplerDesc.addressV = TextureAddressMode::clamp;
	samplerDesc.addressW = TextureAddressMode::clamp;

	samplerDesc.magFilter = TextureMagFilter::nearest;
	samplerDesc.minFilter = TextureMinFilter::nearest;

	samplerDesc.maxAnisotrophy = 0;
	samplerDesc.minLod = 0;
	samplerDesc.maxLod = 0;
	samplerDesc.mipLodBias = 0;

	cresult = renderDevice->CreateSamplerState(samplerDesc, (SamplerState**)&quadSampler);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	ShaderResourceViewDesc viewDesc;

	viewDesc.dimensions = BufferType::texture_2d;
	viewDesc.format = desc.format;
	viewDesc.tex2d.baseMipLevel = 0;
	viewDesc.tex2d.maxMipLevel = 0;

	cresult = frontBuffer->GetShaderViewTex2D(viewDesc, (ShaderResourceView**)&frontBufferView);
	if (cresult != Ceng::CE_OK)
	{
		return;
	}

	GLint maxPsTextures;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxPsTextures);

	psTextureUnits = std::vector<GL32_TextureUnit>(maxPsTextures);

	for (GLint k = 0; k < maxPsTextures; ++k)
	{
		psTextureUnits[k].unitIndex = k;
	}

	// Render target data

	GLint maxRenderTargets;
	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxRenderTargets);

	renderTargets = std::vector<GL32_RenderTargetSlot>(maxRenderTargets);
	gl_drawBufferData = std::vector<GLenum>(maxRenderTargets);

	for (GLint k = 0; k < maxRenderTargets; ++k)
	{
		renderTargets[k].view = nullptr;
		renderTargets[k].nextView = nullptr;
		renderTargets[k].gl_slotID = GL_COLOR_ATTACHMENT0 + k;

		//gl_drawBufferData[k] = GL_COLOR_ATTACHMENT0 + k;
		gl_drawBufferData[k] = GL_NONE;
	}

	gl_drawBufferData[0] = GL_COLOR_ATTACHMENT0;

	// Default blend state

	BlendStateDesc blendDesc;
	RenderTargetBlendDesc targetBlend;

	blendDesc.alphaToCoverage = false;
	blendDesc.independentBlend = false;
	blendDesc.targets = 1;
	blendDesc.descList = &targetBlend;

	targetBlend.blendEnable = false;
	
	targetBlend.sourceBlend = BlendType::one;
	targetBlend.destBlend = BlendType::zero;
	targetBlend.blendOp = BlendOp::add;

	targetBlend.sourceBlendAlpha = BlendType::one;
	targetBlend.destBlendAlpha = BlendType::zero;
	targetBlend.blendAlphaOp = BlendOp::add;

	defaultBlendState = nullptr;

	cresult = renderDevice->CreateBlendState(&blendDesc, (BlendState**)&defaultBlendState);
	if (cresult != CE_OK)
	{
		return;
	}

	// Default depth stencil state

	DepthStencilDesc dsDesc;

	dsDesc.depthEnable = false;
	dsDesc.stencilEnable = false;

	dsDesc.depthTest = TEST_TYPE::ALWAYS_PASS;
	dsDesc.depthWrite = false;

	dsDesc.frontFace.stencilTest = TEST_TYPE::ALWAYS_PASS;
	
	dsDesc.frontFace.stencilRef = 0;
	dsDesc.frontFace.stencilReadMask = -1;
	dsDesc.frontFace.stencilWriteMask = -1;

	dsDesc.frontFace.depthFail = STENCIL_ACTION::KEEP;
	dsDesc.frontFace.depthPass = STENCIL_ACTION::KEEP;
	dsDesc.frontFace.stencilFail = STENCIL_ACTION::KEEP;

	dsDesc.backFace.stencilTest = TEST_TYPE::ALWAYS_PASS;

	dsDesc.backFace.stencilRef = 0;
	dsDesc.backFace.stencilReadMask = -1;
	dsDesc.backFace.stencilWriteMask = -1;

	dsDesc.backFace.depthFail = STENCIL_ACTION::KEEP;
	dsDesc.backFace.depthPass = STENCIL_ACTION::KEEP;
	dsDesc.backFace.stencilFail = STENCIL_ACTION::KEEP;

	cresult = renderDevice->CreateDepthStencilState(dsDesc, (DepthStencilState**)&defaultDepthStencilState);
	if (cresult != CE_OK)
	{
		return;
	}

	SetDepthStencilState(defaultDepthStencilState);

	SetBlendState(defaultBlendState, nullptr);

	SetRenderTarget(0, frontBufferTarget);

	ApplyStateChanges();

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	//glDisable(GL_FRAMEBUFFER_SRGB);
	//glEnable(GL_FRAMEBUFFER_SRGB);
}

const Ceng::BOOL GL33_RenderContext::FramebufferValid()
{
	GLenum glResult = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (glResult != GL_FRAMEBUFFER_COMPLETE)
	{
		if (glResult == GL_FRAMEBUFFER_UNDEFINED)
		{
			return false;
		}
		else if (glResult == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
		{
			return false;
		}
		else if (glResult == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
		{
			return false;
		}
		else if (glResult == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)
		{
			return false;
		}
		else if (glResult == GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)
		{
			return false;
		}
		else if (glResult == GL_FRAMEBUFFER_UNSUPPORTED)
		{
			return false;
		}
		else if (glResult == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)
		{
			return false;
		}
	}
	return true;
}


GL33_RenderContext::~GL33_RenderContext()
{
	glDeleteVertexArrays(1,&gl_vertexArray);

	glDeleteRenderbuffers(1, &gl_defaultDepthBuffer);

	glDeleteFramebuffers(1, &gl_frameBufferObject);

	frontBufferTarget->Release();
	frontBufferView->Release();
	frontBuffer->Release();

	quadBuffer->Release();
	quadIndices->Release();

	quadVshader->Release();
	quadPshader->Release();
	quadProgram->Release();

	ps_texture->Release();
	quadSampler->Release();

	quadFormat->Release();

	defaultBlendState->Release();

	defaultDepthStencilState->Release();
}

void GL33_RenderContext::Release()
{
	delete this;
}

void GL33_RenderContext::Present()
{
	// Set hardware back buffer as render target
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Backup current state

	DepthStencilState *oldDepthState = depthStencilState;

	BlendState *oldBlendState = blendState;

	ShaderProgram *oldProgram = shaderProgram;

	ShaderResourceView *oldTex = psTextureUnits[0].resource;
	SamplerState *oldSampler = psTextureUnits[0].sampler;

	IndexBuffer *oldIndex = indexBuffer;
	VertexFormat *oldFormat = vertexFormat;

	SetPixelShaderResource(0, (ShaderResourceView*)frontBufferView);
	SetPixelShaderSamplerState(0, (SamplerState*)quadSampler);

	VertexBuffer *oldBuffer = vertexStreams[0].vertexBuffer;
	Ceng::UINT32 stride = vertexStreams[0].stride;
	Ceng::UINT32 offset = vertexStreams[0].offset;

	// Set state for fullscreen quad render

	SetViewport(defaultViewport.x, defaultViewport.y, 
		defaultViewport.width, defaultViewport.height);

	SetShaderProgram(quadProgram);

	ps_texture->SetInt(0);

	SetIndexBuffer(quadIndices);

	SetVertexFormat(quadFormat);

	SetVertexStream(0, quadBuffer, sizeof(VertexData), 0);

	SetBlendState(nullptr, nullptr);

	SetDepthStencilState(nullptr);

	DrawIndexed(PRIMITIVE_TYPE::TRIANGLE_LIST, 0, 6);

	// Restore previous state

	SetViewport(viewport.x, viewport.y, viewport.width, viewport.height);

	SetVertexStream(0, oldBuffer, stride, offset);
	SetIndexBuffer(oldIndex);
	
	SetPixelShaderResource(0, oldTex);
	SetPixelShaderSamplerState(0, oldSampler);

	SetVertexFormat(oldFormat);

	SetShaderProgram(oldProgram);

	SetBlendState(oldBlendState, nullptr);

	SetDepthStencilState(oldDepthState);
}

void GL33_RenderContext::FinishPresent()
{
	glBindFramebuffer(GL_FRAMEBUFFER, gl_frameBufferObject);
}

const Ceng::CRESULT GL33_RenderContext::GetFrontBufferTarget(RenderTargetView **frontBuffer)
{
	RenderTargetViewDesc desc;

	desc.type = BufferType::texture_2d;
	desc.tex2d.mipSlice = 0;

	return this->frontBuffer->GetRenderTargetView(desc, frontBuffer);
}

const Ceng::CRESULT GL33_RenderContext::ClearTarget(Ceng::RenderTargetView *targetView, const CE_Color &color)
{
	ApplyStateChanges();
	//UpdateRenderTargets();

	Ceng::FLOAT32 clearColor[4];

	color.ExtractFloatColor(clearColor);

	glClearColor(clearColor[2], clearColor[1], clearColor[0], clearColor[3]);

	int error = glGetError();

	if (error != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		return CE_ERR_FAIL;
	}

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::ClearDepth(const FLOAT32 depth)
{
	glClearDepth(depth);

	glClear(GL_DEPTH_BUFFER_BIT);

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::ClearDepthStencil(const FLOAT32 depth, const Ceng::UINT32 stencil)
{
	glClearDepth(depth);
	glClearStencil(stencil);

	glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetVertexFormat(Ceng::VertexFormat *newFormat)
{
	GL33_VertexFormat *gl_format = static_cast<GL33_VertexFormat*>(newFormat);

	/*
	if (vertexFormat == gl_format)
	{
		return CE_OK;
	}
	*/

	if (nextVertexFormat == gl_format)
	{
		return CE_OK;
	}

	nextVertexFormat = gl_format;

	vertexFormatChanged = true;

	return CE_OK;
}


const Ceng::CRESULT GL33_RenderContext::SetIndexBuffer(Ceng::IndexBuffer *indexBuffer)
{
	GL32_IndexBuffer *gl_buffer = static_cast<GL32_IndexBuffer*>(indexBuffer);

	if (this->indexBuffer != gl_buffer)
	{
		indexBufferChanged = true;
	}

	this->indexBuffer = gl_buffer;

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetShaderProgram(Ceng::ShaderProgram *program)
{
	GL32_ShaderProgram *gl_program = static_cast<GL32_ShaderProgram*>(program);

	if (shaderProgram == nullptr)
	{
		shaderProgram = gl_program;
		programChanged = true;
		return CE_OK;
	}

	if (shaderProgram->programID != gl_program->programID)
	{
		shaderProgram = gl_program;
		programChanged = true;
		return CE_OK;
	}

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::StartScene()
{
	if (window->IsResized())
	{

	}

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::EndScene()
{
	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::DrawPrimitive(const Ceng::PRIMITIVE_TYPE::value type,
	const Ceng::UINT32 firstVertex, const Ceng::UINT32 primitives)
{
	ApplyStateChanges();

	GLenum gl_mode;
	CRESULT cresult;

	cresult = TranslatePrimitive(type, &gl_mode);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	glDrawArrays(gl_mode, firstVertex, primitives);

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::DrawIndexed(const Ceng::PRIMITIVE_TYPE::value type, 
	const Ceng::UINT32 firstVertex, const Ceng::UINT32 primitives)
{
	ApplyStateChanges();

	if (indexBuffer == nullptr)
	{
		return CE_OK;
	}

	GLenum gl_mode;
	CRESULT cresult;

	cresult = TranslatePrimitive(type, &gl_mode);
	if (cresult != CE_OK)
	{
		return cresult;
	}

	Ceng::POINTER offset = firstVertex * indexBuffer->elementSize;

	glDrawElements(gl_mode, primitives,indexBuffer->gl_size,(void*)(offset));

	GLenum result = glGetError();
	if (result != GL_NO_ERROR)
	{
		return CE_OK;
	}

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::TranslatePrimitive(const Ceng::PRIMITIVE_TYPE::value type, GLenum *gl_type)
{
	switch (type)
	{
	case Ceng::PRIMITIVE_TYPE::TRIANGLE_LIST:
		*gl_type = GL_TRIANGLES;
		break;
	case Ceng::PRIMITIVE_TYPE::TRIANGLE_STRIP:
		*gl_type = GL_TRIANGLE_STRIP;
		break;
	case Ceng::PRIMITIVE_TYPE::TRIANGLE_FAN:
		*gl_type = GL_TRIANGLE_FAN;
		break;
	default:
		return CE_ERR_NOT_SUPPORTED;
	}
	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetDepthStencilState(Ceng::DepthStencilState *state)
{
	if (depthStencilState != state)
	{
		if (state == nullptr)
		{
			depthStencilState = defaultDepthStencilState;
		}
		else
		{
			depthStencilState = static_cast<GL32_DepthStencilState*>(state);
		}

		depthStencilState->GL_Enable();
	}

	return CE_OK;
}

void GL33_RenderContext::GL_SetState(const GLenum state, const Ceng::BOOL value)
{
	if (value == true)
	{
		glEnable(state);
	}
	else
	{
		glDisable(state);
	}
}

const Ceng::CRESULT GL33_RenderContext::SetRasterizerState(const Ceng::RasterizerState *state)
{
	Ceng::BOOL cullingEnable = false;
	GLenum gl_cullingMode = GL_BACK;

	switch (state->cullingMode)
	{
	case CULLING_MODE::NONE:
		break;
	case CULLING_MODE::BACK:
		cullingEnable = true;
		break;
	case CULLING_MODE::FRONT:
		cullingEnable = true;
		gl_cullingMode = GL_FRONT;
		break;
	default:
		return CE_ERR_INVALID_PARAM;
	}

	if (cullingEnable == true)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(gl_cullingMode);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetBlendState(BlendState *state, Ceng::FLOAT32 *blendFactor)
{
	if (blendState != state)
	{
		if (state == nullptr)
		{
			blendState = defaultBlendState;
		}
		else
		{
			blendState = static_cast<GL32_BlendState*>(state);
		}

		blendState->GL_Enable();
	}

	if (blendFactor != nullptr)
	{
		this->blendFactor[0] = blendFactor[0];
		this->blendFactor[1] = blendFactor[1];
		this->blendFactor[2] = blendFactor[2];
		this->blendFactor[3] = blendFactor[3];
	}
	else
	{
		this->blendFactor[0] = 1.0f;
		this->blendFactor[1] = 1.0f;
		this->blendFactor[2] = 1.0f;
		this->blendFactor[3] = 1.0f;
	}

	glBlendColor(this->blendFactor[0], this->blendFactor[1], this->blendFactor[2], this->blendFactor[3]);

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetViewport(const Ceng::INT32 x, const Ceng::INT32 y,
	const Ceng::INT32 width, const Ceng::INT32 height)
{
	viewport.x = x;
	viewport.y = y;
	viewport.width = width;
	viewport.height = height;

	glViewport(x, y, width, height);

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetScissorRect(const Ceng::Rectangle *rect)
{
	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetPixelShaderResource(const Ceng::UINT32 index,ShaderResourceView *resource)
{
	if (resource == psTextureUnits[index].resource)
	{
		return CE_OK;
	}

	psTextureUnits[index].nextResource = resource;

	if (psTextureUnits[index].dirty == false)
	{
		psTextureUpdates.push_back(index);
		psTextureUnits[index].dirty = true;
	}

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetPixelShaderSamplerState(const Ceng::UINT32 index, SamplerState *sampler)
{
	if (sampler == psTextureUnits[index].sampler)
	{
		return CE_OK;
	}

	psTextureUnits[index].sampler = sampler;

	if (psTextureUnits[index].dirty == false)
	{
		psTextureUpdates.push_back(index);
		psTextureUnits[index].dirty = true;
	}
	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetDepth(RenderTargetView *view)
{
	if (depthTarget != nullptr)
	{
		depthTarget->GL_Unbind(GL_DEPTH_ATTACHMENT);
	}
	else
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);
		GLenum result = glGetError();
		if (result != GL_NO_ERROR)
		{
			return CE_OK;
		}

	
	}

	depthTarget = static_cast<GL32_RenderTargetView*>(view);

	if (view == nullptr)
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, gl_defaultDepthBuffer);
		GLenum result = glGetError();
		if (result != GL_NO_ERROR)
		{
			return CE_OK;
		}
	}
	else
	{
		depthTarget->GL_Bind(GL_DEPTH_ATTACHMENT);
		GLenum result = glGetError();
		if (result != GL_NO_ERROR)
		{
			return CE_OK;
		}

	}

	FramebufferValid();

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetDepthStencil(RenderTargetView *view)
{
	if (depthTarget != nullptr)
	{
		depthTarget->GL_Unbind(GL_DEPTH_STENCIL_ATTACHMENT);
	}
	else
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, 0);
	}

	depthTarget = static_cast<GL32_RenderTargetView*>(view);

	if (view == nullptr)
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, gl_defaultDepthBuffer);
	}
	else
	{
		depthTarget->GL_Bind(GL_DEPTH_STENCIL_ATTACHMENT);
		GLenum result = glGetError();
		if (result != GL_NO_ERROR)
		{
			return CE_OK;
		}

	}

	return CE_OK;
}

const Ceng::CRESULT GL33_RenderContext::SetRenderTarget(const Ceng::UINT32 index, RenderTargetView *view)
{
	if (index >= renderTargets.size())
	{
		return CE_ERR_INVALID_PARAM;
	}

	GL32_RenderTargetView *gl_view = static_cast<GL32_RenderTargetView*>(view);

	if (renderTargets[index].nextView == gl_view)
	{
		return CE_OK;
	}

	if (renderTargets[index].dirty == false)
	{
		renderTargetUpdates.push_back(&renderTargets[index]);

		renderTargets[index].dirty = true;
	}	

	renderTargets[index].nextView = gl_view;

	return CE_OK;
}

void GL33_RenderContext::UpdateRenderTargets()
{
	for (Ceng::UINT32 k = 0; k < renderTargetUpdates.size(); ++k)
	{
		renderTargetUpdates[k]->GL_Update();
	}

	if (renderTargetUpdates.size() > 0)
	{
		for (Ceng::UINT32 k = 0; k < renderTargets.size(); ++k)
		{
			gl_drawBufferData[k] = GL_COLOR_ATTACHMENT0 + k;
			if (renderTargets[k].view == nullptr)
			{
				gl_drawBufferData[k] = GL_NONE;
			}
		}

		glDrawBuffers(GLsizei(renderTargets.size()), &gl_drawBufferData[0]);

		renderTargetUpdates.clear();
	}

	FramebufferValid();

	// If a resource is bound as render target, set all texture units using
	// that resource to null input.

	for (Ceng::UINT32 k = 0; k < renderTargets.size(); ++k)
	{
		if (renderTargets[k].view == nullptr)
		{
			continue;
		}
	
		for (Ceng::UINT32 j = 0; j < psTextureUnits.size(); ++j)
		{
			auto *gl_view = static_cast<GL32_ShaderResourceView*>(psTextureUnits[j].resource);

			if (gl_view == nullptr)
			{
				continue;
			}

			if (gl_view->ResourcePtr() == (void*)renderTargets[k].view->ResourcePtr())
			{
				SetPixelShaderResource(j, nullptr);
			}
		}
	}
}

const Ceng::CRESULT GL33_RenderContext::SetVertexStream(const Ceng::UINT32 index, Ceng::VertexBuffer *source,
	const Ceng::UINT32 stride, const Ceng::UINT32 offset)
{
	if (index > vertexStreams.size())
	{
		return CE_ERR_NOT_SUPPORTED;
	}

	if (source == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	GL32_VertexBuffer *gl_vbuffer = static_cast<GL32_VertexBuffer*>(source);

	if (offset > gl_vbuffer->bufferSize)
	{
		return CE_ERR_INVALID_PARAM;
	}

	if (vertexStreams[index].vertexBuffer == gl_vbuffer)
	{
		if (vertexStreams[index].offset == offset)
		{
			return CE_OK;
		}
	}

	vertexStreams[index].offset = offset;
	vertexStreams[index].vertexBuffer = gl_vbuffer;

	if (vertexStreams[index].changed == false)
	{
		vertexStreams[index].changed = true;
		streamChanges.push_back(index);
	}



	return CE_OK;
}


void GL33_RenderContext::UpdateVertexStreams(Ceng::BOOL updateAll)
{
	if (vertexFormat == nullptr) return;

	if (updateAll == true)
	{
		for (Ceng::UINT32 k = 0; k < vertexStreams.size(); ++k)
		{
			if (vertexStreams[k].vertexBuffer != nullptr)
			{
				GLuint gl_buffer = vertexStreams[k].vertexBuffer->bufferID;

				if (gl_buffer != 0)
				{
					SetVertexBufferObject(gl_buffer);
				}

				vertexFormat->LinkVertexStream(k, &vertexStreams[k]);
			}
			vertexStreams[k].changed = false;
		}
		SetVertexBufferObject(0);
	}
	else
	{
		for (auto &index : streamChanges)
		{
			if (vertexStreams[index].vertexBuffer != nullptr)
			{
				GLuint gl_buffer = vertexStreams[index].vertexBuffer->bufferID;

				if (gl_buffer != 0)
				{
					SetVertexBufferObject(gl_buffer);
				}

				vertexFormat->LinkVertexStream(index, &vertexStreams[index]);
			}
			vertexStreams[index].changed = false;
		}
		SetVertexBufferObject(0);
	}

	streamChanges.clear();
}

const Ceng::INT32 GL33_RenderContext::SetVertexBufferObject(const GLuint gl_bufferID)
{
	if (gl_vertexBuffer != gl_bufferID)
	{
		if (gl_bufferID == 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			gl_vertexBuffer = 0;
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, gl_bufferID);

			GLenum result = glGetError();
			if (result != GL_NO_ERROR)
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				gl_vertexBuffer = 0;

				return -1;
			}

			gl_vertexBuffer = gl_bufferID;
		}		
	}

	return 0;
}

void GL33_RenderContext::ApplyStateChanges()
{
	GLenum result;

	Ceng::BOOL forceUpdateStreams = false;

	if (programChanged == true)
	{
		glUseProgram(shaderProgram->programID);

		result = glGetError();
		if (result != GL_NO_ERROR)
		{
			return;
		}

		vertexFormatChanged = true;
		forceUpdateStreams = true;
		programChanged = false;
	}

	if (shaderProgram != nullptr)
	{
		shaderProgram->GL_UpdateUniforms();
	}

	if (vertexFormatChanged == true)
	{
		// Clean up current vertex format links
		if (vertexFormat != nullptr)
		{
			vertexFormat->DisableStreamLinks();

		}

		//if (shaderProgram != nullptr)
		//{
			if (nextVertexFormat != nullptr)
			{
				nextVertexFormat->LinkShaderProgram(shaderProgram);
			}
		//}

		vertexFormat = nextVertexFormat;
		vertexFormatChanged = false;

		forceUpdateStreams = true;
	}

	UpdateVertexStreams(forceUpdateStreams);

	//UpdateVertexStreams(true);

	if (indexBufferChanged == true)
	{
		if (indexBuffer == nullptr)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->gl_bufferID);
		}

		indexBufferChanged = false;
	}

	UpdateTextureUnits();
	UpdateRenderTargets();
}

void GL33_RenderContext::UpdateTextureUnits()
{
	for (Ceng::UINT32 k = 0; k < psTextureUpdates.size(); ++k)
	{
		Ceng::UINT32 index = psTextureUpdates[k];
		psTextureUnits[index].GL_Update();
	}

	psTextureUpdates.clear();
}