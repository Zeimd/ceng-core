/*****************************************************************************
*
* software-renderer.h
*
* By Jari Korkala 30/6/2011
*
* Class SoftwareRenderer : Implements a software renderer.
*
*****************************************************************************/

#ifndef _CONCEPT2_CONCEPT_RENDERER_H
#define _CONCEPT2_CONCEPT_RENDERER_H

#include <vector>
#include <exception>
#include <atomic>

#include <ceng/interfaces/render-device.h>

#include "crender-base.h"

// Include CE_Buffer declaration
#include "buffer-factory.h"

// Include CR_RenderTarget declaration
#include "rendertarget-cr.h"


// Include CR_Rasterizer declaration

#include "cr-image-buffer.h"



#include <ceng/interfaces/graphics-2d.h>

#include <ceng/interfaces/display-mode.h>

#include <ceng/lib/liblog.h>

#include <ceng/datatypes/swap-chain-desc.h>

//*************************************************************************
// Concept Renderer

namespace Ceng
{
	class RenderContext;

	class CR_VertexFormat;
	class CR_VertexShader;

	class CR_PixelShader;

	class CR_Texture2D;

	class CR_Rasterizer;

	class CPU_Info;

	class CR_RenderContext;
	class SwapChain;

	class SoftwareRenderer : public RenderDevice
	{
	public:

		FileLog debugLog;

		SwapChainDesc outputParams;
		
		CPU_Info *cpuInfo;

		CR_RenderContext *renderContext;
	
		Graphics2D *outputDevice;
		PlatformWindow *deviceWindow;

		DisplayMode desktopMode;
		
		Ceng::IMAGE_FORMAT::value backBufferFormat;

		CR_BufferFactory bufferFactory;
		
		
		std::shared_ptr<CR_NewTargetData> depthBuffer;

		Ceng::UINT32 maxScreenSubBuckets;		

	
		
		UINT8 renderTileSize;
		UINT16 renderThreadCount;
		UINT16 cacheLineSize;
		
		UINT16 maxViewWidth,maxViewHeight;
		
		//*******************************************
		// Scene variables
		
	
	
	public:
		SoftwareRenderer();
		~SoftwareRenderer() override;
		
		void Release() override;

		const Ceng::CRESULT CreateVertexShader(const Ceng::StringUtf8& shaderText, Ceng::VertexShader** shaderPtr) override;

		CRESULT CreateVertexFormat(const std::vector<Ceng::VertexDeclData>
			& vertexDecl,
			Ceng::VertexFormat** format) override;

		CRESULT CreateVertexBuffer(UINT32 vertexSizeBytes,
			UINT32 vertexNum,
			UINT32 usage,
			Ceng::VertexBuffer** destPtr) override;

		const Ceng::CRESULT CreateIndexBuffer(const Ceng::UINT32 elementSize, const Ceng::UINT32 elements,
			const Ceng::UINT32 usage, void* initialData, Ceng::IndexBuffer** destPtr) override;

		/**
		 * Returns recommended maximum number of vertices in a vertex buffer.
		 */
		const Ceng::UINT32 GetOptimalVertexElements() override;

		/**
		* Returns recommended maximum number of indices in an index buffer.
		*/
		const Ceng::UINT32 GetOptimalIndexElements() override;

		const Ceng::CRESULT CreatePixelShader(const Ceng::StringUtf8& shaderText, Ceng::PixelShader** shaderPtr) override;

		const Ceng::CRESULT CreateShaderProgram(Ceng::VertexShader* vertexShader, Ceng::PixelShader* pixelShader, Ceng::ShaderProgram** program) override;

		const CRESULT CreateSamplerState(const SamplerStateDesc& desc,
			Ceng::SamplerState** out_state) override;

		const CRESULT CreateShaderResourceView(RenderResource* resource,
			ShaderResourceViewDesc& desc,
			ShaderResourceView** out_resourceView) override;

		const CRESULT CreateBlendState(BlendStateDesc* desc, BlendState** statePtr) override;

		const Ceng::CRESULT CreateDepthStencilState(const DepthStencilDesc& desc, DepthStencilState** statePtr) override;

		const CRESULT CreateTexture2D(const Texture2dDesc& desc,
			const SubResourceData* initialData,
			Ceng::Texture2D** texturePtr) override;

		const CRESULT CreateTexture2D(const GL_Texture2dDesc& desc,
			const SubResourceData* initialData,
			Ceng::Texture2D** texturePtr) override;

		const CRESULT CreateCubemap(const Texture2dDesc& desc,
			const SubResourceData* initialData,
			Ceng::Cubemap** texturePtr) override;

		const CRESULT CreateProjectionMatrix(const Ceng::INT32 displayWidth, const Ceng::INT32 displayHeight,
			const Ceng::FLOAT32 horizontalField,
			const Ceng::FLOAT32 zNear,
			const Ceng::FLOAT32 zFar,
			Ceng::Matrix4* dest) override;

	public:

		CRESULT Configure(CPU_Info *cpuInfo,Graphics2D *devicePtr,DisplayMode *desktopMode,
							SwapChainDesc &swapChainDesc);

		const Ceng::CRESULT GetContext(RenderContext **contextPtr);

		const CRESULT AutoCreateDepthStencil(SwapChainDesc &swapChainDesc,
			DisplayMode *desktopMode);

		const CRESULT CreateSwapChain(SwapChainDesc &swapChainDesc, SwapChain **out_swapChain);
		
		/*
		CRESULT CreateFrameBuffer(SwapChainDesc *parameters,
									UINT32 desktopWidth,
									UINT32 desktopHeight);
									*/

		//**************************
		// Vertex format methods

		virtual CRESULT CreateVertexShader(Ceng::VertexShader **shaderPtr);
		
		UINT32 VertexVariableSize(Ceng::VTX_DATATYPE::value dataType);		
		
	protected:

		const CRESULT CopyTextureData(CR_NewTargetData *texture, const SubResourceData *sourceData,
			const Ceng::IMAGE_FORMAT::value sourceFormat);

		const CRESULT CopyToTiled(CR_NewTargetData *tiledTex, CR_NewTargetData *sourceTex);

		const Ceng::UINT8* GetTiledAddress(CR_NewTargetData *tiledTexconst, 
			const Ceng::UINT32 u, const Ceng::UINT32 v) const;

	public:
		
		/**
		* Returns the number of bytes required by a variable of CE_VTX_FORMAT.
		*/
		UINT32 GetDeclarationVariableSize(UINT32 format);

		

	};

} // Namespace end

#endif // Include guard
