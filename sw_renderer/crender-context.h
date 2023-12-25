/*****************************************************************************
*
* crender-context.h
*
* Created By Jari Korkala 2/3/2015
*
*****************************************************************************/

#ifndef CRENDER_CONTEXT_H
#define CRENDER_CONTEXT_H

#include <memory>

#include <ceng/interfaces/render-context.h>
#include <ceng/datatypes/ring-buffer.h>

#include "command-thread.h"

#include "pipeline.h"

#include "shader-link.h"

namespace Ceng
{
	class RenderState;
	class ApiCommand;

	class Thread;
	class DrawBatch;

	class ConceptRenderer;

	class CR_Clipper;
	class CR_Rasterizer;

	class CR_RenderContext : public RenderContext
	{
	public:

		ConceptRenderer *parentDevice;

		/**
		* Render state that will be enabled by the next draw call.
		*/
		std::shared_ptr<RenderState> nextRenderState;

		/**
		* Current render state.
		*/
		std::shared_ptr<RenderState> currentRenderState;

		// Api command queue

		CommandProcessor cmdProcessor;
		Thread *cmdThread;

		Ceng::UINT32 apiCallCounter;

		RingBuffer<std::shared_ptr<ApiCommand>> commandQueue;

		std::shared_ptr<ConditionVariable> cmdProcessorSleep;

		std::shared_ptr<DrawBatch> drawBatch;

		Pipeline pipeline;

		Ceng::CR_Clipper *activeClipper;

		CR_ShaderLink shaderLink;

		CR_Rasterizer *activeRasterizer;

		/*
		* Previous width of output window. Used to determine
		* if the value has changed.
		*/
		UINT32 oldWindowWidth;

		/*
		* Previous height of output window. Used to determine
		* if the value has changed.
		*/
		UINT32 oldWindowHeight;

		bool scene;	// Don't allow external access to render targets while true

		/*
		* Width of output window for this frame.
		*/
		UINT32 windowWidth;

		/*
		* Height of output window for this frame.
		*/
		UINT32 windowHeight;

	public:

		CR_RenderContext();
		~CR_RenderContext() override;

		void Release() override;

		const Ceng::CRESULT Configure(ConceptRenderer *parentDevice);

		const Ceng::CRESULT ClearTarget(Ceng::RenderTarget *renderTarget, const CE_Color &color) override;

		const Ceng::CRESULT ClearDepth(const FLOAT32 depth) override;

		const Ceng::CRESULT ClearDepthStencil(const FLOAT32 depth, const UINT32 stencil) override;

		const Ceng::CRESULT SetVertexFormat(Ceng::VertexFormat *formatPtr) override;

		const Ceng::CRESULT SetVertexStream(const Ceng::UINT32 index, Ceng::VertexBuffer* source, const Ceng::UINT32 stride, const Ceng::UINT32 offset) override;

		const Ceng::CRESULT SetShaderProgram(Ceng::ShaderProgram* program) override;

		const Ceng::CRESULT StartScene() override;
		const Ceng::CRESULT EndScene() override;

		const Ceng::CRESULT SetIndexBuffer(Ceng::IndexBuffer* indexBuffer) override;
	
		const Ceng::CRESULT DrawPrimitive(const Ceng::PRIMITIVE_TYPE::value type,
			const Ceng::UINT32 firstVertex, const Ceng::UINT32 primitives) override;

		const Ceng::CRESULT DrawIndexed(const Ceng::PRIMITIVE_TYPE::value type, const Ceng::UINT32 firstVertex, const Ceng::UINT32 primitives) override;

		const Ceng::CRESULT SetRasterizerState(const Ceng::RasterizerState *state) override;

		const Ceng::CRESULT SetScissorRect(const Ceng::Rectangle *rect) override;

		const Ceng::CRESULT SetViewport(const Ceng::INT32 x, const Ceng::INT32 y, const Ceng::INT32 width, const Ceng::INT32 height) override;

		const Ceng::CRESULT SetPixelShaderResource(const Ceng::UINT32 index, ShaderResourceView* resource) override;

		const Ceng::CRESULT SetPixelShaderSamplerState(const Ceng::UINT32 index, SamplerState* sampler) override;

		const Ceng::CRESULT SetRenderTarget(const Ceng::UINT32 index, RenderTargetView* view) override;

		const Ceng::CRESULT SetBlendState(BlendState* state, Ceng::FLOAT32* blendFactor) override;

		const Ceng::CRESULT SetDepth(RenderTargetView* view) override;

		const Ceng::CRESULT SetDepthStencilState(Ceng::DepthStencilState* state) override;

		const Ceng::CRESULT SetDepthStencil(RenderTargetView* view) override;

		const Ceng::CRESULT GetFrontBufferTarget(RenderTargetView** frontBuffer) override;

	public:

		const CRESULT Execute_DrawPrimitive(const Ceng::UINT32 apiCallId, Ceng::PRIMITIVE_TYPE::value type,
			UINT32 firstVertex,UINT32 primitives,std::shared_ptr<RenderState> &renderState);

		const CRESULT Execute_ClearTarget(Ceng::RenderTarget *renderTarget,
			const CE_Color &color,
			std::shared_ptr<RenderState> &renderState);

		const CRESULT Execute_ClearDepth(const FLOAT32 depth,
			std::shared_ptr<RenderState> &renderState);

		const CRESULT Execute_ClearDepthStencil(const FLOAT32 depth, const UINT32 stencil,
			std::shared_ptr<RenderState> &renderState);

		const CRESULT InstantiateRenderState();
	};
}

#endif