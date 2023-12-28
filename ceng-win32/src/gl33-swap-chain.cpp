/*****************************************************************************
*
* gl33-swap-chain.cpp
*
* Created By Jari Korkala 16/3/2015
*
*****************************************************************************/

#include "../inc/gl33-swap-chain.h"
#include "../inc/gl33-context.h"

using namespace Ceng;

GL33_SwapChain::GL33_SwapChain()
{
}

GL33_SwapChain::GL33_SwapChain(SwapChainDesc *desc, ::HDC deviceHandle, ::HGLRC gl_context,
	GL33_RenderContext *renderContext)
	: desc(*desc),deviceHandle(deviceHandle),gl_context(gl_context),renderContext(renderContext)
{

}


GL33_SwapChain::~GL33_SwapChain()
{
}

void GL33_SwapChain::Release()
{
	delete this;
}

const CRESULT GL33_SwapChain::Present()
{
	renderContext->Present();

	SwapBuffers(deviceHandle);

	renderContext->FinishPresent();

	return CE_OK;
}

const CRESULT GL33_SwapChain::Present(const Ceng::UINT32 syncInterval, const Ceng::UINT32 options,
	const Ceng::UINT32 dirtyRectCount,
	const Ceng::Rectangle *dirtyRects,
	const Ceng::Rectangle *scrollRect,
	const Ceng::UINT32 scrollOffsetX,
	const Ceng::UINT32 scrollOffsetY)
{
	return CE_OK;
}

const Ceng::CRESULT GL33_SwapChain::GetFrameBufferTarget(Ceng::RenderTargetView **renderTarget)
{
	return CE_OK;
}