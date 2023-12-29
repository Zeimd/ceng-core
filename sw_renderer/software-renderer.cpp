/*****************************************************************************
*
* software-renderer.cpp
*
* By Jari Korkala 30/6/2011
*
* Core methods for software renderer.
*
*****************************************************************************/

#include <ceng/datatypes/cpu-info.h>

#include <ceng/platform.h>

#include <ceng/datatypes/release-deleter.h>

#include "software-renderer.h"

#include "rasterizer-cr.h"

#include "command-thread.h"
#include "render-thread.h"

#include "crender-context.h"

#include "cr-swap-chain.h"

#include "cr-sampler-state.h"

#include "cr-texture-2d.h"

#include "cr-pixel-shader.h"

#include "cr-vertex-format.h"

#include "cr-vertex-buffer.h"

#include "cr-vertex-shader.h"

#include "cr-depthstencil-state.h"

#include "cr-shader-program.h"

using namespace Ceng;

//***************************************************************************
// Concept Renderer methods

SoftwareRenderer::SoftwareRenderer()
{
	outputDevice = nullptr;
	deviceWindow = nullptr;

	renderContext = nullptr;

	renderTileSize = 8;
	cacheLineSize = 16;

	renderThreadCount = 1;

	debugLog.OpenFile("crender-debug.txt");

	//Log::SetLog(&debugLog);

	Log::Print("ConceptRenderer : constructor");
}

SoftwareRenderer::~SoftwareRenderer()
{
	if (outputDevice != nullptr)
	{
		outputDevice->Release();
	}

	Log::Print("ConceptRenderer : destuctor");
}

void SoftwareRenderer::Release()
{
	delete this;
}

CRESULT SoftwareRenderer::Configure(CPU_Info *cpuInfo,Graphics2D *devicePtr,
									DisplayMode *desktopMode,
									SwapChainDesc &swapChainDesc)
{
	Log::Print("Configure : method start");

	if (devicePtr == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	this->cpuInfo = cpuInfo;

	cacheLineSize = cpuInfo->CacheLine();
	
	// TODO: Better evaluation of core count
	renderThreadCount = cpuInfo->LogicalCores() - 1;

	maxScreenSubBuckets = 2*renderThreadCount;

	bufferFactory.SetSystemData(cacheLineSize,4096,16,maxScreenSubBuckets,8);

	outputDevice = devicePtr;

	if (swapChainDesc.autoDepthStencil)
	{
		CRESULT cresult = AutoCreateDepthStencil(swapChainDesc,desktopMode);

		if (cresult != CE_OK) return cresult;
	}

	deviceWindow = swapChainDesc.outputWindow;

	memcpy(&outputParams,&swapChainDesc, sizeof(SwapChainDesc));
	memcpy(&this->desktopMode, desktopMode, sizeof(DisplayMode));

	renderContext = new CR_RenderContext();
	renderContext->Configure(this);

	maxViewWidth = swapChainDesc.displayMode.width;
	maxViewHeight = swapChainDesc.displayMode.height;

	if (swapChainDesc.windowed)
	{
		maxViewWidth = desktopMode->width;
		maxViewHeight = desktopMode->height;
	}


	return CE_OK;
}

const Ceng::CRESULT SoftwareRenderer::GetContext(RenderContext **contextPtr)
{
	*contextPtr = (Ceng::RenderContext*)renderContext;

	return CE_OK;
}

const CRESULT SoftwareRenderer::AutoCreateDepthStencil(SwapChainDesc &swapChainDesc,
	DisplayMode *desktopMode)
{
	Ceng::UINT32 bufferWidth = swapChainDesc.displayMode.width;
	Ceng::UINT32 bufferHeight = swapChainDesc.displayMode.height;

	if (swapChainDesc.windowed)
	{
		bufferWidth = desktopMode->width;
		bufferHeight = desktopMode->height;
	}

	UINT32 bufferUsage = BufferBinding::render_target;
	UINT32 bufferOptions = 0;

	CR_NewTargetData *targetData;

	CRESULT cresult = bufferFactory.GetRenderTarget(bufferWidth,
			bufferHeight,
			bufferWidth,
			bufferHeight,
			swapChainDesc.autoDepthStencilFormat,
			Ceng::BUFFER_TILING::TILED8_LQUADS,
			bufferUsage,
			bufferOptions,
			&targetData);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	depthBuffer = std::shared_ptr<CR_NewTargetData>(targetData);

	return CE_OK;
}
						
const CRESULT SoftwareRenderer::CreateSwapChain(SwapChainDesc &swapChainDesc, SwapChain **out_swapChain)
{
	CRESULT cresult;

	UINT32 bufferUsage = BufferBinding::render_target;
	UINT32 bufferOptions = 0;

	Ceng::UINT32 bufferWidth = swapChainDesc.displayMode.width;
	Ceng::UINT32 bufferHeight = swapChainDesc.displayMode.height;

	if (swapChainDesc.windowed)
	{
		bufferWidth = desktopMode.width;
		bufferHeight = desktopMode.height;
	}

	CR_NewTargetData *targetData;

	cresult = bufferFactory.GetRenderTarget(bufferWidth,
		bufferHeight,
		bufferWidth,
		bufferHeight,
		swapChainDesc.displayMode.format,
		Ceng::BUFFER_TILING::LQUADS,
		bufferUsage,
		bufferOptions,
		&targetData);

	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	targetData->dataLayout = Ceng::BUFFER_LAYOUT::SOA;

	if (cresult != CE_OK) return cresult;

	*out_swapChain = (SwapChain*)new CR_SwapChain(renderContext,outputDevice, targetData);

	return CE_OK;
}

const CRESULT SoftwareRenderer::CreateSamplerState(const SamplerStateDesc &desc,
	Ceng::SamplerState **out_state)
{
	CR_SamplerState *temp = new CR_SamplerState(desc);

	*out_state = (CR_SamplerState*)temp;

	return CE_OK;
}

const CRESULT SoftwareRenderer::CreateShaderResourceView(RenderResource *resource,
	ShaderResourceViewDesc &desc,
	ShaderResourceView **out_resourceView)
{
	switch (resource->GetResourceType())
	{
	case BufferType::texture_2d:

		CR_Texture2D *temp = (CR_Texture2D*)resource;

		return temp->GetShaderViewTex2D(desc, out_resourceView);
	}


	return CE_OK;
}


const CRESULT SoftwareRenderer::CreateTexture2D(const Texture2dDesc &desc,
	const SubResourceData *initialData, Ceng::Texture2D **texturePtr)
{
	TextureArrayVector textures(desc.arraySize);

	CRESULT cresult;

	Texture2dDesc localDesc;

	memcpy(&localDesc, &desc, sizeof(Texture2dDesc));

	IMAGE_FORMAT::value internalFormat = localDesc.format;

	switch (localDesc.format)
	{
	case IMAGE_FORMAT::C24_RGB:
		internalFormat = IMAGE_FORMAT::C32_ARGB;
		break;
	case IMAGE_FORMAT::C24_BGR:
		internalFormat = IMAGE_FORMAT::C32_ABGR;
		break;
	default:
		break;
	}

	localDesc.format = internalFormat;

	if (desc.mipLevels == 0)
	{
		localDesc.width = desc.width;
		localDesc.height = desc.height;

		localDesc.mipLevels = 1;
		
		while (localDesc.width > 1 || localDesc.height > 1)
		{
			if (localDesc.width > 1)
			{
				localDesc.width = localDesc.width >> 1;
			}

			if (localDesc.height > 1)
			{
				localDesc.height = localDesc.height >> 1;
			}

			++localDesc.mipLevels;
		}
	}

	for (Ceng::UINT32 k = 0; k < desc.arraySize; ++k)
	{
		localDesc.width = desc.width;
		localDesc.height = desc.height;

		for (Ceng::UINT32 j = 0; j < localDesc.mipLevels; ++j)
		{
			CR_NewTargetData *tempTexture;

			cresult = bufferFactory.GetTexture2D(localDesc, &tempTexture);

			if (j == 0 || !(desc.optionFlags & BufferOptions::generate_mip_maps))
			{
				const SubResourceData *data = &initialData[k*localDesc.mipLevels + j];

				CopyTextureData(tempTexture, data,desc.format);
			}

			textures[k].push_back(std::shared_ptr<CR_NewTargetData>(tempTexture));

			if (localDesc.width > 1)
			{
				localDesc.width = localDesc.width >> 1;
			}

			if (localDesc.height > 1)
			{
				localDesc.height = localDesc.height >> 1;
			}
		}
	}

	localDesc.width = desc.width;
	localDesc.height = desc.height;

	CR_Texture2D *tempTex = new CR_Texture2D(localDesc, std::move(textures));

	if (desc.optionFlags & BufferOptions::generate_mip_maps)
	{
		tempTex->GenerateMipMaps(0);
	}

	// Convert textures to tiled layout

	textures = TextureArrayVector(desc.arraySize);

	for (Ceng::UINT32 k = 0; k < desc.arraySize; ++k)
	{
		localDesc.width = desc.width;
		localDesc.height = desc.height;

		for (Ceng::UINT32 j = 0; j < localDesc.mipLevels; ++j)
		{
			CR_NewTargetData *tempTexture;

			cresult = bufferFactory.GetTiledTexture2D(localDesc, &tempTexture);

			CopyToTiled(tempTexture, tempTex->textures[k][j].get());

			textures[k].push_back(std::shared_ptr<CR_NewTargetData>(tempTexture));

			if (localDesc.width > 1)
			{
				localDesc.width = localDesc.width >> 1;
			}

			if (localDesc.height > 1)
			{
				localDesc.height = localDesc.height >> 1;
			}
		}
	}

	localDesc.width = desc.width;
	localDesc.height = desc.height;

	delete tempTex;

	CR_Texture2D *finalTex = new CR_Texture2D(localDesc, std::move(textures));

	*texturePtr = finalTex;

	return CE_OK;
}

const CRESULT SoftwareRenderer::CopyToTiled(CR_NewTargetData *tiledTex, CR_NewTargetData *sourceTex)
{
	Ceng::UINT8 *sourceAddress = (Ceng::UINT8*)sourceTex->baseAddress;

	Ceng::UINT32 sourceOffset;

	for (Ceng::UINT32 y = 0; y < sourceTex->bufferHeight; ++y)
	{
		sourceOffset = sourceTex->tileYstep*y;

		for (Ceng::UINT32 x = 0; x < sourceTex->bufferWidth; ++x)
		{
			Ceng::UINT32 *destAddress = (Ceng::UINT32*)GetTiledAddress(tiledTex, x, y);

			*destAddress = *(Ceng::UINT32*)&sourceAddress[sourceOffset];

			sourceOffset += sourceTex->bytesPerPixel;
		}
	}

	return CE_OK;
}

const Ceng::UINT8* SoftwareRenderer::GetTiledAddress(CR_NewTargetData *tiledTex,
	const Ceng::UINT32 u, const Ceng::UINT32 v) const
{
	
	Ceng::UINT32 tileX = u >> 2;
	Ceng::UINT32 posX = u & 3;

	Ceng::UINT32 tileY = v >> 2;
	Ceng::UINT32 posY = v & 3;
	
	
	/*
	Ceng::UINT32 tileX = u >> 3;
	Ceng::UINT32 posX = u & 7;

	Ceng::UINT32 tileY = v >> 3;
	Ceng::UINT32 posY = v & 7;
	
	Ceng::UINT32 tileX = u >> 4;
	Ceng::UINT32 posX = u & 15;

	Ceng::UINT32 tileY = v >> 4;
	Ceng::UINT32 posY = v & 15;
	*/

	Ceng::UINT8 *texelPtr = (Ceng::UINT8*)tiledTex->baseAddress;

	texelPtr += tiledTex->tileXstep*tileX;
	texelPtr += tiledTex->tileYstep*tileY;

	texelPtr += tiledTex->channels[0].unitYstep*posY;
	texelPtr += tiledTex->channels[0].unitXstep*posX;

	return texelPtr;
}

const CRESULT SoftwareRenderer::CopyTextureData(CR_NewTargetData *texture, const SubResourceData *sourceData,
	const Ceng::IMAGE_FORMAT::value sourceFormat)
{
	Ceng::UINT8 *destAddress = (Ceng::UINT8*)texture->baseAddress;
	Ceng::UINT8 *sourceAddress = (Ceng::UINT8*)sourceData->sourcePtr;

	if (texture->bufferFormat == sourceFormat)
	{
		Ceng::UINT32 rowBytes = sourceData->rowPitch;

		for (Ceng::UINT32 k = 0; k < texture->bufferHeight; ++k)
		{
			memcpy(destAddress, sourceAddress, rowBytes);

			destAddress += texture->channels[0].tileYstep;
			sourceAddress += rowBytes;
		}
	}

	if (texture->bufferFormat == IMAGE_FORMAT::C32_ARGB && sourceFormat == IMAGE_FORMAT::C24_RGB)
	{
		Ceng::UINT32 rowBytes = sourceData->rowPitch;

		for (Ceng::UINT32 k = 0; k < texture->bufferHeight; ++k)
		{
			Ceng::UINT8 *tempSource = sourceAddress;
			Ceng::UINT8 *tempDest = destAddress;

			for (Ceng::UINT32 j = 0; j < texture->bufferWidth; ++j)
			{
				tempDest[0] = tempSource[0];
				tempDest[1] = tempSource[1];
				tempDest[2] = tempSource[2];
				tempDest[3] = 255;

				tempSource += 3;
				tempDest += texture->channels[0].bytesPerPixel;

				//memcpy(destAddress, sourceAddress, rowBytes);

			}

			destAddress += texture->channels[0].tileYstep;
			sourceAddress += rowBytes;
		}
	}

	return CE_OK;
}

const Ceng::CRESULT SoftwareRenderer::CreateVertexShader(const Ceng::StringUtf8& shaderText, Ceng::VertexShader** shaderPtr)
{
	CRESULT cresult;

	Log::Print("CreateVertexShader : method start");

	//************************************************************
	// Old creation

	Ceng::CR_VertexShader* vertexShader;

	*shaderPtr = NULL;

	try
	{
		vertexShader = new CR_VertexShader();
	}
	catch (std::bad_alloc&)
	{
		return CE_ERR_OUT_OF_MEMORY;
	}

	Ceng::CR_vsInputSemantic vsTempInput;

	// Set inputs registers

	vsTempInput.semantic = Ceng::SHADER_SEMANTIC::POSITION;
	vsTempInput.options = 0;

	vertexShader->inputSemantics.push_back(vsTempInput);

	vsTempInput.semantic = Ceng::SHADER_SEMANTIC::NORMAL;
	vsTempInput.options = 0;

	vertexShader->inputSemantics.push_back(vsTempInput);

	vsTempInput.semantic = Ceng::SHADER_SEMANTIC::TANGENT;
	vsTempInput.options = 0;

	vertexShader->inputSemantics.push_back(vsTempInput);

	vsTempInput.semantic = Ceng::SHADER_SEMANTIC::TEXCOORD_0;
	vsTempInput.options = 0;

	vertexShader->inputSemantics.push_back(vsTempInput);

	vsTempInput.semantic = Ceng::SHADER_SEMANTIC::TEXCOORD_1;
	vsTempInput.options = 0;

	vertexShader->inputSemantics.push_back(vsTempInput);

	cresult = vertexShader->ConfigureInput();
	if (cresult != CE_OK)
	{
		return cresult;
	}

	// Set output registers

	Ceng::CR_vsOutputSemantic vShaderOutput;

	vShaderOutput.semantic = Ceng::SHADER_SEMANTIC::POSITION;
	vShaderOutput.dataType = Ceng::SHADER_DATATYPE::FLOAT4;
	vShaderOutput.options = 0;

	vertexShader->outputSemantics.push_back(vShaderOutput);

	vShaderOutput.semantic = Ceng::SHADER_SEMANTIC::NORMAL;
	vShaderOutput.dataType = Ceng::SHADER_DATATYPE::FLOAT4;
	vShaderOutput.options = 0;

	vertexShader->outputSemantics.push_back(vShaderOutput);

	vShaderOutput.semantic = Ceng::SHADER_SEMANTIC::TANGENT;
	vShaderOutput.dataType = Ceng::SHADER_DATATYPE::FLOAT4;
	vShaderOutput.options = 0;

	vertexShader->outputSemantics.push_back(vShaderOutput);

	vShaderOutput.semantic = Ceng::SHADER_SEMANTIC::TEXCOORD_0;
	vShaderOutput.dataType = Ceng::SHADER_DATATYPE::FLOAT2;
	vShaderOutput.options = 0;

	vertexShader->outputSemantics.push_back(vShaderOutput);

	vShaderOutput.semantic = Ceng::SHADER_SEMANTIC::TEXCOORD_1;
	vShaderOutput.dataType = Ceng::SHADER_DATATYPE::FLOAT2;
	vShaderOutput.options = 0;

	vertexShader->outputSemantics.push_back(vShaderOutput);

	// Set constants

	Ceng::CR_ShaderConstantData tempShaderConst;

	tempShaderConst.name = "fullVertexTransform";
	tempShaderConst.dataType = Ceng::SHADER_DATATYPE::FLOAT4x4;

	vertexShader->uniformList.push_back(tempShaderConst);

	cresult = vertexShader->ConfigureConstants();
	if (cresult != CE_OK)
	{
		return cresult;
	}

	*shaderPtr = (Ceng::VertexShader*)vertexShader;

	return CE_OK;

}

const Ceng::CRESULT SoftwareRenderer::CreateIndexBuffer(const Ceng::UINT32 elementSize, const Ceng::UINT32 elements,
	const Ceng::UINT32 usage, void* initialData, Ceng::IndexBuffer** destPtr)
{
	return CE_ERR_UNIMPLEMENTED;
}

const Ceng::UINT32 SoftwareRenderer::GetOptimalVertexElements()
{
	return CE_ERR_UNIMPLEMENTED;
}

const Ceng::UINT32 SoftwareRenderer::GetOptimalIndexElements()
{
	return CE_ERR_UNIMPLEMENTED;
}

const Ceng::CRESULT SoftwareRenderer::CreatePixelShader(const Ceng::StringUtf8& shaderText, Ceng::PixelShader** shaderPtr)
{
	Ceng::CR_PixelShader *pixelShader;

	*shaderPtr = nullptr;

	try
	{
		pixelShader = new CR_PixelShader();
	}
	catch(std::bad_alloc&)
	{
		return CE_ERR_OUT_OF_MEMORY;
	}

	Ceng::CR_PixelShaderSemantic psTempRegister;

	
	psTempRegister.semantic = Ceng::SHADER_SEMANTIC::NORMAL;
	pixelShader->inputSemantics.push_back(psTempRegister);
	
	psTempRegister.semantic = Ceng::SHADER_SEMANTIC::TANGENT;
	pixelShader->inputSemantics.push_back(psTempRegister);

	psTempRegister.semantic = Ceng::SHADER_SEMANTIC::TEXCOORD_0;
	pixelShader->inputSemantics.push_back(psTempRegister);

	psTempRegister.semantic = Ceng::SHADER_SEMANTIC::TEXCOORD_1;
	pixelShader->inputSemantics.push_back(psTempRegister);
	
	Ceng::CR_ShaderConstantData tempConst;

	tempConst.dataType = SHADER_DATATYPE::UINT;
	tempConst.name = "diffuseTexture";

	pixelShader->uniformList.push_back(tempConst);

	pixelShader->ConfigureConstants();

	Ceng::CR_PixelShaderTarget psTempTarget;

	psTempTarget.target = Ceng::CR_SHADER_TARGET0;
	pixelShader->renderTargets.push_back(psTempTarget);

	*shaderPtr = (Ceng::PixelShader*)pixelShader;
	 
	return Ceng::CE_OK;
}

const Ceng::CRESULT SoftwareRenderer::CreateShaderProgram(Ceng::VertexShader* vertexShader, Ceng::PixelShader* pixelShader, Ceng::ShaderProgram** program)
{
	CR_ShaderProgram* prog;

	CRESULT cresult = CR_ShaderProgram::GetInstance((CR_VertexShader*)vertexShader, (CR_PixelShader*)pixelShader, &prog);

	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	*program = prog;

	return CE_OK;
}

const CRESULT SoftwareRenderer::CreateBlendState(BlendStateDesc* desc, BlendState** statePtr)
{
	return CE_ERR_UNIMPLEMENTED;
}

const Ceng::CRESULT SoftwareRenderer::CreateDepthStencilState(const DepthStencilDesc& desc, DepthStencilState** statePtr)
{
	*statePtr = new CR_DepthStencilState(desc);

	return CE_OK;
}

const CRESULT SoftwareRenderer::CreateTexture2D(const GL_Texture2dDesc& desc,	const SubResourceData* initialData,
	Ceng::Texture2D** texturePtr)
{
	return CE_ERR_UNIMPLEMENTED;
}

const CRESULT SoftwareRenderer::CreateCubemap(const Texture2dDesc& desc, const SubResourceData* initialData,
	Ceng::Cubemap** texturePtr)
{
	return CE_ERR_UNIMPLEMENTED;
}

const CRESULT SoftwareRenderer::CreateProjectionMatrix(const Ceng::INT32 displayWidth, const Ceng::INT32 displayHeight,
	const Ceng::FLOAT32 horizontalField, const Ceng::FLOAT32 zNear, const Ceng::FLOAT32 zFar,
	Ceng::Matrix4* dest)
{
	if (dest == nullptr)
	{
		return CE_ERR_FAIL;
	}

	// Determine dilation

	Ceng::FLOAT32 horizField = horizontalField;

	if (horizontalField >= FLOAT32(180.0f)
		|| horizontalField <= FLOAT32(0.0f))
	{
		horizField = FLOAT32(90.0f);
	}

	FLOAT32 dilation;
	FLOAT32 aspectRatio;

	dilation = FLOAT32(1.0f) /
		tan(FLOAT32(0.5f) * horizField * degrees_to_radians);

	aspectRatio = (FLOAT32(displayWidth) / FLOAT32(displayHeight));

	FLOAT32 depth0, depth1;

	depth0 = zFar / (zFar - zNear);
	depth1 = -(zNear * zFar) / (zFar - zNear);

	// Fill the projection matrix

	dest->data[0][0] = FLOAT32(1.0f) * dilation;
	dest->data[0][1] = FLOAT32(0.0f);
	dest->data[0][2] = FLOAT32(0.0f); //-centerX / dilation;
	dest->data[0][3] = FLOAT32(0.0f);

	dest->data[1][0] = FLOAT32(0.0f);
	dest->data[1][1] = aspectRatio * dilation;
	dest->data[1][2] = FLOAT32(0.0f);//-centerY / dilation;
	dest->data[1][3] = FLOAT32(0.0f);

	dest->data[2][0] = FLOAT32(0.0f);
	dest->data[2][1] = FLOAT32(0.0f);
	dest->data[2][2] = -depth0;
	dest->data[2][3] = depth1;

	dest->data[3][0] = FLOAT32(0.0f);
	dest->data[3][1] = FLOAT32(0.0f);
	dest->data[3][2] = FLOAT32(-1.0f);
	dest->data[3][3] = FLOAT32(0.0f);

	return CE_OK;
}

CRESULT SoftwareRenderer::CreateVertexFormat(const std::vector<Ceng::VertexDeclData>& vertexDecl,
	Ceng::VertexFormat** vertexFormat)
{
	*vertexFormat = nullptr;

	Log::Print("CreateVertexFormat : method start");

	if (&vertexDecl == nullptr)
	{
		Log::Print("CreateVertexFormat : nullptr input");
		return CE_ERR_NULL_PTR;
	}


	UINT32 size = 0;

	if (vertexDecl.size() == 0)
	{
		Log::Print("CreateVertexFormat : vertex declaration is empty");
		return CE_ERR_INVALID_PARAM;
	}

	// Count variables, but interrupt immediately if
	// an invalid value is encountered

	size_t k;

	for (k = 0; k < vertexDecl.size(); k++)
	{	
		if (vertexDecl[k].format == Ceng::VTX_DATATYPE::FORMAT_END)
		{
			break;
		}

		if (vertexDecl[k].format == Ceng::SHADER_SEMANTIC::FORMAT_END)
		{
			break;
		}

		if (vertexDecl[k].streamSource >= CRENDER_MAX_VERTEX_STREAMS)
		{
			return CE_ERR_INVALID_PARAM;
		}
	}

	CR_VertexFormat* formatPtr;

	try
	{
		formatPtr = new CR_VertexFormat();
	}
	catch (std::bad_alloc&)
	{
		Log::Print("CreateVertexFormat : Error : failed to create format object");
		return CE_ERR_OUT_OF_MEMORY;
	}

	UINT32 variableCount = k;

	UINT32 flagBit = 0;
	UINT32 variableSizeBytes;

	memset(formatPtr->streamStrides, 0, CRENDER_MAX_VERTEX_STREAMS * sizeof(POINTER));

	CR_VertexVariable tempVariable;

	formatPtr->sizeBytes = 0;

	for (size_t k = 0; k < variableCount; k++)
	{
		// Check that variables from the same stream don't
		// overlap

		if (vertexDecl[k].offset < formatPtr->streamStrides[vertexDecl[k].streamSource])
		{
			Log::Print("CreateVertexFormat : Error : variable overlap detected");

			delete formatPtr;
			formatPtr = nullptr;
			return CE_ERR_INVALID_PARAM;
		}

		tempVariable.semantic = vertexDecl[k].semantic;

		tempVariable.outputOffset = formatPtr->sizeBytes;

		tempVariable.dataType = vertexDecl[k].format;

		tempVariable.inputStream = vertexDecl[k].streamSource;
		tempVariable.inputOffset = vertexDecl[k].offset;

		tempVariable.aligned = 0;

		formatPtr->semanticFlags |= tempVariable.semantic;

		variableSizeBytes = VertexVariableSize(vertexDecl[k].format);

		formatPtr->streamStrides[vertexDecl[k].streamSource] =
			vertexDecl[k].offset + variableSizeBytes;

		formatPtr->sizeBytes += variableSizeBytes;

		try
		{
			formatPtr->variables.push_back(tempVariable);
		}
		catch (std::bad_alloc&)
		{
			Log::Print("CreateVertexFormat : failed to allocate variable");

			delete formatPtr;
			formatPtr = nullptr;
			return CE_ERR_OUT_OF_MEMORY;
		}

	};

	// Check whether variables are 16-byte aligned in their
	// respective streams. First of all, the stride of
	// the source stream must be divisible by 16. Second,
	// the variable's offset in an input chunk must be
	// divisible by 16.

	// NOTE: x86 SSE has faster read/write
	//       operations that require 16-byte aligned 
	//       memory address. If the address is not
	//       aligned, a slower read/write operation
	//       must be used.

	for (k = 0; k < formatPtr->variables.size(); k++)
	{
		if (formatPtr->variables[k].inputOffset % 16 == 0)
		{
			if (formatPtr->streamStrides[formatPtr->variables[k].inputStream] % 16 == 0)
			{
				formatPtr->variables[k].aligned = 1;
			}
		}
	}

	*vertexFormat = (Ceng::VertexFormat*)formatPtr;

	Log::Print("\nCreateVertexFormat : format dump:\n");

	String temp;

	for (k = 0; k < formatPtr->variables.size(); k++)
	{
		temp = formatPtr->variables[k].inputStream;
		temp += ",";
		temp += formatPtr->variables[k].outputOffset;
		temp += ",";

		switch (formatPtr->variables[k].dataType)
		{
		case VTX_DATATYPE::FLOAT:
			temp += "float";
			break;
		case VTX_DATATYPE::FLOAT2:
			temp += "float2";
			break;
		case VTX_DATATYPE::FLOAT4:
			temp += "float4";
			break;
		default:
			break;
		}

		temp += ",";

		switch (formatPtr->variables[k].semantic)
		{
		case SHADER_SEMANTIC::POSITION:
			temp += "position";
			break;
		case SHADER_SEMANTIC::NORMAL:
			temp += "normal";
			break;
		case SHADER_SEMANTIC::COLOR_0:
			temp += "color0";
			break;
		case SHADER_SEMANTIC::TEXCOORD_0:
			temp += "texCoord0";
			break;
		case SHADER_SEMANTIC::TEXCOORD_1:
			temp += "texCoord1";
			break;
		case SHADER_SEMANTIC::TEXCOORD_2:
			temp += "texCoord2";
			break;
		default:
			break;
		}

		Log::Print(temp);
	}

	Log::Print("");

	return CE_OK;
}

Ceng::UINT32 SoftwareRenderer::VertexVariableSize(Ceng::VTX_DATATYPE::value dataType)
{
	switch (dataType)
	{
	case Ceng::VTX_DATATYPE::FLOAT:
		return 4;
	case Ceng::VTX_DATATYPE::FLOAT2:
		return 8;
	case Ceng::VTX_DATATYPE::FLOAT3:
		return 12;
	case Ceng::VTX_DATATYPE::FLOAT4:
		return 16;
	default:
		return 0;
	};
}

CRESULT SoftwareRenderer::CreateVertexBuffer(Ceng::UINT32 vertexSizeBytes,
	Ceng::UINT32 vertexNum,
	Ceng::UINT32 usage,
	Ceng::VertexBuffer** destPtr)
{
	Log::Print("CreateVertexBuffer : method start");

	String temp = "vertexSize = ";
	temp += vertexSizeBytes;
	Log::Print(temp);

	temp = "vertexNum = ";
	temp += vertexNum;
	Log::Print(temp);

	UINT8* allocPtr = nullptr;
	CR_VertexBuffer* vertexBuffer = nullptr;

	if (vertexSizeBytes == 0)
	{
		Log::Print("CreateVertexBuffer : vertex size is zero");
		return CE_ERR_INVALID_PARAM;
	}

	if (vertexNum == 0)
	{
		Log::Print("CreateVertexBuffer : vertex amount is zero");
		return CE_ERR_INVALID_PARAM;
	}

	allocPtr = (UINT8*)AlignedMalloc(vertexSizeBytes * vertexNum, cacheLineSize);
	if (allocPtr == nullptr)
	{
		Log::Print("CreateVertexBuffer : memory allocation failed");
		return CE_ERR_OUT_OF_MEMORY;
	}

	try
	{
		vertexBuffer = new CR_VertexBuffer(allocPtr, vertexSizeBytes,
			vertexNum);
	}
	catch (std::bad_alloc&)
	{
		Log::Print("CreateVertexBuffer : failed to create buffer");
		AlignedFree(allocPtr);
		return CE_ERR_OUT_OF_MEMORY;
	}

	temp = "base address = ";
	temp += (POINTER)allocPtr;

	Log::Print(temp);

	*destPtr = vertexBuffer;

	return CE_OK;
}




