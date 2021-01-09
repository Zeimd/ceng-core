/*****************************************************************************
*
* win32-opengl32.h
*
* Created By Jari Korkala 15/3/2015
*
*****************************************************************************/

#ifndef CENG_WIN32_OPENGL32_H
#define CENG_WIN32_OPENGL32_H

#include <gl/glew.h>
#include <gl/wglew.h>


#include <ceng/datatypes/cpu-info.h>
#include <ceng/interfaces/graphics-system.h>

#include "../inc/win32-dll.h"

#include "../inc/win32-window.h"

#include "../inc/gl32-buffer-bits.h"

namespace Ceng
{
	

	class GL32_GraphicsSystem : public GraphicsSystem
	{
	protected:

		WinAPI_Window *dummyWindow;

		::HGLRC dummyRenderContext;

		::HDC dummyDeviceContext;

		GL32_GraphicsSystem();

		GL32_GraphicsSystem(WinAPI_Window *window,::HDC deviceContext,::HGLRC renderContext);

	public:
		
		virtual  ~GL32_GraphicsSystem();

		virtual void Release() override;

		static const Ceng::CRESULT GetInstance(CPU_Info *cpuData,Ceng::GraphicsSystem **out_system,LogType *log);

		virtual const Ceng::UINT32 AdapterCount() override;

		virtual const Ceng::CRESULT EnumAdapter(const Ceng::UINT32 index, GraphicsAdapter **out_adapter) override;

		virtual const Ceng::UINT32 CurrentDisplayMode(GraphicsAdapter *adapter,
			DisplayMode &out_mode) override;

		virtual const Ceng::UINT32 DisplayModeCount(GraphicsAdapter *adapter,
			const Ceng::IMAGE_FORMAT::value format) override;

		virtual const Ceng::CRESULT EnumDisplayMode(GraphicsAdapter *adapter, const Ceng::UINT32 index,
			const Ceng::IMAGE_FORMAT::value format, DisplayMode &out_mode) override;

		virtual const Ceng::CRESULT CheckFramebufferSupport(GraphicsAdapter *adapter,
			const Ceng::IMAGE_FORMAT::value displayFormat,
			const Ceng::IMAGE_FORMAT::value backBufferFormat,
			const Ceng::BOOL windowed) override;

		virtual const Ceng::CRESULT CheckBufferSupport(GraphicsAdapter *adapter,
			const Ceng::IMAGE_FORMAT::value displayFormat,
			const Ceng::BufferType::value type,
			const Ceng::IMAGE_FORMAT::value bufferFormat,
			const Ceng::UINT32 binding,
			const Ceng::BufferUsage::value usage,
			const Ceng::UINT32 cpuAccess,
			const Ceng::UINT32 options) override;

		virtual const CRESULT CreateSwapChain(RenderDevice *device,
			SwapChainDesc &swapChainDesc,
			SwapChain **chainPtr) override;

		virtual const CRESULT GetRenderDevice(GraphicsAdapter *adapter,
			const Ceng::UINT64 deviceOptions,
			SwapChainDesc *swapChainDesc,
			SwapChain **swapChainPtr,
			RenderDevice **devicePtr,
			RenderContext **contextPtr) override;

		static const Ceng::IMAGE_FORMAT::value BitsToFormat(const Ceng::UINT32 colorBits);

		static const Ceng::INT32 FindSimplePixelFormat(::HDC context,const Ceng::IMAGE_FORMAT::value format);

	protected:

		const CRESULT TranslateDisplayMode(GraphicsAdapter *adapter, const Ceng::UINT32 index, DisplayMode &out_mode);

		

	};
}

#endif