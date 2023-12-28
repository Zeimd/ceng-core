/*****************************************************************************
*
* gl33-context.h
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#ifndef CENG_GL33_CONTEXT_H
#define CENG_GL33_CONTEXT_H

#include <Windows.h>

#include <gl/glew.h>

#include "../inc/win32-window.h"

#include <ceng/interfaces/render-context.h>

#include "gl32-constants.h"

#include "gl32-state-vertex-stream.h"

#include <ceng/enums/test-type.h>
#include <ceng/enums/stencil-action.h>

#include "gl32-texture-unit.h"
#include "gl32-index-buffer.h"

#include "gl32-target-slot.h"

namespace Ceng
{
	class GL32_ShaderProgram;
	class GL33_VertexFormat;
	class GL33_RenderDevice;
	class GL32_Texture2D;

	class GL32_VertexShader;
	class GL32_PixelShader;
	class GL32_SamplerState;
	class ShaderConstant;

	class GL32_BlendState;
	class GL32_DepthStencilState;

	class GL32_ShaderViewTex2D;

	struct Vec3
	{
		Ceng::FLOAT32 x;
		Ceng::FLOAT32 y;
		Ceng::FLOAT32 z;
	};

	struct TextureCoord
	{
		Ceng::FLOAT32 u;
		Ceng::FLOAT32 v;
	};

	struct VertexData
	{
		Vec3 position;
		TextureCoord texCoord;
	};

	struct Viewport
	{
		Ceng::INT32 x;
		Ceng::INT32 y;
		Ceng::INT32 width;
		Ceng::INT32 height;
	};

	class GL32_RenderTargetView;

	class GL33_RenderContext : public RenderContext
	{
	public:

		GL33_RenderDevice *renderDevice;

		PlatformWindow *window;
		::HDC deviceHandle;
		::HGLRC gl_context;

		/**
		 * Next or current shader program, depending on *programChanged*.
		 */
		GL32_ShaderProgram *shaderProgram;

		/**
		 * True if shader program has changed since last draw call.
		 */
		Ceng::BOOL programChanged;

		//Ceng::BOOL forceUpdateStreams;

		/**
		 * True if vertex format has changed since last draw call.
		 */
		Ceng::BOOL vertexFormatChanged;

		/**
		 * Current vertex format.
		 */
		GL33_VertexFormat *vertexFormat;

		/**
		* Next vertex format.
		*/
		GL33_VertexFormat *nextVertexFormat;

		/**
		 * State of all API-defined vertex streams.
		 */
		std::vector<GL32_VertexStreamState> vertexStreams;

		/**
		 * List of streams that have changed since last draw call.
		 */
		std::vector<Ceng::UINT32> streamChanges;

		/**
		 * Current pipeline index buffer.
		 */
		GL32_IndexBuffer *indexBuffer;

		/**
		 * True if index buffer has been changed since last draw call.
		 */
		Ceng::BOOL indexBufferChanged;

		/**
		 *
		 */
		GLuint gl_vertexBuffer;

		/**
		 * Handle to the compulsory vertex array object.
		 */
		GLuint gl_vertexArray;

		/**
		 * Handle to framebuffer object.
		 */
		GLuint gl_frameBufferObject;

		/**
		 * Handle to default depth attachment.
		 */
		GLuint gl_defaultDepthBuffer;

		GL32_Texture2D *frontBuffer;

		/**
		 * Vertex data for drawing a full screen quad.
		 */
		VertexData fullScreenQuad[4];

		/**
		 * Vertex buffer for drawing a full screen quad.
		 */
		GL32_VertexBuffer *quadBuffer;

		/**
		 * Index data for drawing a full screen quad.
		 */
		Ceng::UINT8 fullScreenIndices[6];

		/**
		 * Index buffer for drawing a full screen quad.
		 */
		GL32_IndexBuffer *quadIndices;

		GL32_VertexShader *quadVshader;
		GL32_PixelShader *quadPshader;
		GL32_ShaderProgram *quadProgram;

		GL32_SamplerState *quadSampler;

		GL32_ShaderViewTex2D *frontBufferView;

		GL32_RenderTargetView *frontBufferTarget;

		GL33_VertexFormat *quadFormat;

		ShaderConstant *ps_texture;

		std::vector<GL32_TextureUnit> vsTextureUnits;

		std::vector<GL32_TextureUnit> psTextureUnits;

		std::vector<Ceng::UINT32> psTextureUpdates;

		/**
		 * Render target data.
		 */
		std::vector<GL32_RenderTargetSlot> renderTargets;

		std::vector<GL32_RenderTargetSlot*> renderTargetUpdates;

		GL32_RenderTargetView *depthTarget;

		/**
		 * Input for glDrawBuffers.
		 */
		std::vector<GLenum> gl_drawBufferData;

		GL32_BlendState *defaultBlendState;

		GL32_BlendState *blendState;

		Ceng::FLOAT32 blendFactor[4];

		GL32_DepthStencilState *defaultDepthStencilState;

		GL32_DepthStencilState *depthStencilState;

		Viewport defaultViewport;
		Viewport viewport;

	public:

		GL33_RenderContext();

		GL33_RenderContext(PlatformWindow *window, ::HDC deviceHandle, ::HGLRC gl_context,
			GL33_RenderDevice *renderDevice);

		virtual ~GL33_RenderContext();

		virtual void Release() override;

		virtual const Ceng::CRESULT ClearTarget(Ceng::RenderTargetView *targetView, const CE_Color &color) override;

		virtual const Ceng::CRESULT ClearDepth(const FLOAT32 depth) override;

		virtual const Ceng::CRESULT ClearDepthStencil(const FLOAT32 depth, const UINT32 stencil) override;

		virtual const Ceng::CRESULT SetVertexFormat(Ceng::VertexFormat *formatPtr) override;
	
		virtual const Ceng::CRESULT SetVertexStream(const Ceng::UINT32 index, Ceng::VertexBuffer *source, const Ceng::UINT32 stride, const Ceng::UINT32 offset) override;

		virtual const Ceng::CRESULT SetIndexBuffer(Ceng::IndexBuffer *indexBuffer) override;

		virtual const Ceng::CRESULT SetShaderProgram(Ceng::ShaderProgram *program) override;

		virtual const Ceng::CRESULT StartScene() override;
		virtual const Ceng::CRESULT EndScene() override;

		virtual const Ceng::CRESULT DrawPrimitive(const Ceng::PRIMITIVE_TYPE::value type,
			const Ceng::UINT32 firstVertex, const Ceng::UINT32 primitives) override;

		virtual const Ceng::CRESULT DrawIndexed(const Ceng::PRIMITIVE_TYPE::value type, const Ceng::UINT32 firstVertex, const Ceng::UINT32 primitives) override;

		virtual const Ceng::CRESULT SetDepthStencilState(Ceng::DepthStencilState *state) override;

		virtual const Ceng::CRESULT SetRasterizerState(const Ceng::RasterizerState *state) override;

		virtual const Ceng::CRESULT SetScissorRect(const Ceng::Rectangle *rect) override;

		const Ceng::CRESULT SetPixelShaderResource(const Ceng::UINT32 index, ShaderResourceView *resource) override;

		virtual const Ceng::CRESULT SetPixelShaderSamplerState(const Ceng::UINT32 index,SamplerState *sampler) override;

		virtual const Ceng::CRESULT SetViewport(const Ceng::INT32 x, const Ceng::INT32 y, const Ceng::INT32 width, const Ceng::INT32 height) override;

		virtual const Ceng::CRESULT SetRenderTarget(const Ceng::UINT32 index, RenderTargetView *view) override;

		virtual const Ceng::CRESULT SetBlendState(BlendState *state, Ceng::FLOAT32 *blendFactor) override;

		virtual const Ceng::CRESULT SetDepth(RenderTargetView *view) override; 
		virtual const Ceng::CRESULT SetDepthStencil(RenderTargetView *view) override;

		virtual const Ceng::CRESULT GetFrontBufferTarget(RenderTargetView **frontBuffer) override;

		void ApplyStateChanges();

		void UpdateVertexStreams(Ceng::BOOL updateAll);

		void UpdateTextureUnits();

		void UpdateRenderTargets();

		/**
		 * Draw proxy front buffer to hardware front buffer.
		 */
		void Present();

		void FinishPresent();

		const Ceng::INT32 SetVertexBufferObject(const GLuint object);

		void GL_SetState(const GLenum state, const Ceng::BOOL value);

		const GLenum GetTestType(const Ceng::TEST_TYPE::value test);

		const GLenum GetStencilAction(const Ceng::STENCIL_ACTION::value action);

		static const Ceng::CRESULT TranslatePrimitive(const Ceng::PRIMITIVE_TYPE::value type,GLenum *gl_type);

		const Ceng::BOOL FramebufferValid();
	};
}

#endif