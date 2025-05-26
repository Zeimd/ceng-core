/*****************************************************************************
*
* gl33-device.h
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#ifndef CENG_GL33_DEVICE_H
#define CENG_GL33_DEVICE_H

#include <windows.h>

#include <ceng/datatypes/window.h>

#include <ceng/interfaces/render-device.h>

namespace Ceng
{
	class GL33_RenderDevice : public RenderDevice
	{
	public:

		PlatformWindow *window;
		::HDC deviceHandle;
		::HGLRC gl_context;

	public:

		GL33_RenderDevice();

		GL33_RenderDevice(PlatformWindow *window, ::HDC deviceHandle, ::HGLRC gl_context);

		~GL33_RenderDevice() override;

		void Release() override;

		const Ceng::CRESULT CreateVertexShader(const Ceng::StringUtf8 &shaderText, Ceng::VertexShader **shaderPtr) override;

		const Ceng::CRESULT CreateVertexShader(const VertexShaderDescriptor* desc, Ceng::PixelShader** shaderPtr) override;

		CRESULT CreateVertexFormat(const std::vector<Ceng::VertexDeclData>
			&vertexDecl,
			Ceng::VertexFormat **format) override;

		CRESULT CreateVertexBuffer(UINT32 vertexSizeBytes,
			UINT32 vertexNum,
			UINT32 usage,
			Ceng::VertexBuffer **destPtr) override;

		const Ceng::CRESULT CreateIndexBuffer(const Ceng::UINT32 elementSize, const Ceng::UINT32 elements,
			const Ceng::UINT32 usage, void *initialData,Ceng::IndexBuffer **destPtr) override;

		/**
		* Returns recommended maximum number of vertices in a vertex buffer.
		*/
		const Ceng::UINT32 GetOptimalVertexElements() override;

		/**
		* Returns recommended maximum number of indices in an index buffer.
		*/
		const Ceng::UINT32 GetOptimalIndexElements() override;

		const Ceng::CRESULT CreatePixelShader(const Ceng::StringUtf8 &shaderText, Ceng::PixelShader **shaderPtr) override;

		const Ceng::CRESULT CreatePixelShader(const PixelShaderDescriptor* desc, Ceng::PixelShader** shaderPtr) override;

		const Ceng::CRESULT CreateShaderProgram(Ceng::VertexShader *vertexShader, Ceng::PixelShader *pixelShader, Ceng::ShaderProgram **program) override;

		const CRESULT CreateSamplerState(const SamplerStateDesc &desc,
			Ceng::SamplerState **out_state) override;

		const CRESULT CreateShaderResourceView(RenderResource *resource,
			ShaderResourceViewDesc &desc,
			ShaderResourceView **out_resourceView) override;

		const CRESULT CreateTexture2D(const Texture2dDesc &desc,
			const SubResourceData *initialData,
			Ceng::Texture2D **texturePtr) override;

		const CRESULT CreateTexture2D(const GL_Texture2dDesc &desc,
			const SubResourceData *initialData,
			Ceng::Texture2D **texturePtr) override;

		const CRESULT CreateCubemap(const Texture2dDesc &desc,
			const SubResourceData *initialData,
			Ceng::Cubemap **texturePtr) override;

		const CRESULT CreateProjectionMatrix(const Ceng::INT32 displayWidth, const Ceng::INT32 displayHeight,
			const Ceng::FLOAT32 horizontalField,
			const Ceng::FLOAT32 zNear,
			const Ceng::FLOAT32 zFar,
			Ceng::Matrix4 *dest) override;

		const CRESULT CreateBlendState(BlendStateDesc *desc, BlendState **statePtr) override;

		const Ceng::CRESULT CreateDepthStencilState(const DepthStencilDesc &desc, DepthStencilState **statePtr) override;
	};
}

#endif