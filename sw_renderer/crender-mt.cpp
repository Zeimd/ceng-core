// crender-mt.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <ceng/datatypes/swap-chain-desc.h>
#include <ceng/interfaces/swap-chain.h>

#include "software-renderer.h"

#include "crender-context.h"

#include <ceng/datatypes/cpu-info.h>

extern "C" __declspec(dllexport) int GetRenderDevice(Ceng::CPU_Info *cpuInfo,
	Ceng::DisplayMode *desktopMode,
	Ceng::Graphics2D *displayPtr,
	Ceng::SwapChainDesc *swapChainDesc,
	Ceng::SwapChain **swapChain,
	Ceng::RenderDevice **renderer,
	Ceng::RenderContext **context)
{
	Ceng::SoftwareRenderer *temp;

	*renderer = NULL;

	try
	{
		temp = new Ceng::SoftwareRenderer();
	}
	catch (std::bad_alloc&)
	{
		return -1;
	}

	Ceng::CRESULT cresult;

	// NOTE: control of d3d_Output transferred to renderer

	cresult = temp->Configure(cpuInfo,displayPtr,desktopMode,*swapChainDesc);

	if (cresult != Ceng::CE_OK)
	{
		temp->Release();
		return -1;
	}

	/*
	if (!swapChainDesc->windowed)
	{
		cresult = temp->CreateFrameBuffer(swapChainDesc,
			swapChainDesc->displayMode.width,
			swapChainDesc->displayMode.height);
	}
	else
	{
		cresult = temp->CreateFrameBuffer(swapChainDesc,
			desktopWidth,
			desktopHeight);
	}
	*/

	//cresult = temp->AutoCreateDepthStencil(swapChainDesc);
	/*
	if (cresult != Ceng::CE_OK)
	{
		temp->Release();
		return cresult;
	}
	*/

	Ceng::RenderContext *tempContext;

	cresult = temp->GetContext(&tempContext);

	if (cresult != Ceng::CE_OK)
	{
		temp->Release();
		return -1;
	}

	*context = tempContext;

	Ceng::SwapChain *tempChain;

	cresult = temp->CreateSwapChain(*swapChainDesc, &tempChain);

	if (cresult != Ceng::CE_OK)
	{
		temp->Release();
		return -1;
	}

	*swapChain = (Ceng::SwapChain*)tempChain;

	*renderer = (Ceng::RenderDevice*)temp;

	return 0;
}
