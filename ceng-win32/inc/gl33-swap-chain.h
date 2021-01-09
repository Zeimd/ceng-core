/*****************************************************************************
*
* gl33-swap-chain.h
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#ifndef GL33_SWAP_CHAIN_H
#define GL33_SWAP_CHAIN_H

#include <Windows.h>

#include <ceng/interfaces/swap-chain.h>
#include <ceng/datatypes/swap-chain-desc.h>

#include "../inc/win32-window.h"

namespace Ceng
{
	class GL33_RenderContext;

	class GL33_SwapChain : public SwapChain
	{
	public:
		GL33_RenderContext *renderContext;

		SwapChainDesc desc;

		WinAPI_Window *window;
		::HDC deviceHandle;
		::HGLRC gl_context;

	public:
		GL33_SwapChain();

		GL33_SwapChain(SwapChainDesc *desc, ::HDC deviceHandle, ::HGLRC gl_context,
			GL33_RenderContext *renderContext);

		virtual ~GL33_SwapChain();

		virtual void Release() override;

		// Default present according to device config
		virtual const CRESULT Present() override;

		virtual const CRESULT Present(const Ceng::UINT32 syncInterval, const Ceng::UINT32 options,
			const Ceng::UINT32 dirtyRectCount,
			const Ceng::Rectangle *dirtyRects,
			const Ceng::Rectangle *scrollRect,
			const Ceng::UINT32 scrollOffsetX,
			const Ceng::UINT32 scrollOffsetY) override;

		virtual const Ceng::CRESULT GetFrameBufferTarget(Ceng::RenderTarget **renderTarget) override;
	};
}

#endif