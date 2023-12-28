/*****************************************************************************
*
* win32-crend.cpp
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#include <sstream>

#include <ceng/enums/device-options.h>
#include <ceng/datatypes/cpu-info.h>

#include "../inc/ceng-win32.h"

#include "../inc/win32-crend-d3d9.h"

#include "../inc/win32-window.h"
#include "../inc/d3d9-adapter.h"


#ifdef _MSC_VER
	#ifdef UNICODE
		constexpr ::WCHAR* DEBUG_DLL = L"ceng-swr-debug.dll";
		constexpr ::WCHAR* RELEASE_DLL = L"ceng-swr.dll";
	#else
		constexpr ::TCHAR* DEBUG_DLL = "ceng-swr-debug.dll";
		constexpr ::TCHAR* RELEASE_DLL = "ceng-swr.dll";
	#endif

	#ifdef _DEBUG
		#define	DEPLOY_DLL DEBUG_DLL
	#else
		#define DEPLOY_DLL RELEASE_DLL
	#endif

	#ifdef UNICODE
		static const ::WCHAR* crender_mt_dll = DEPLOY_DLL;
	#else
		static const ::TCHAR* crender_mt_dll = DEPLOY_DLL;
	#endif


#endif

using namespace Ceng;

Ceng::CRESULT ConceptRenderer_D3D9::GetInstance(CPU_Info* cpuData, ConceptRenderer_D3D9** out_renderer)
{
	CRESULT cresult;

	CriticalSection *crit_crender;

	cresult = Ceng_CreateCriticalSection((CriticalSection**)&crit_crender);

	if (cresult != CE_OK)
	{
		return CE_ERR_FAIL;
	}

	CriticalSection *crit_crenderMT;

	cresult = Ceng_CreateCriticalSection((CriticalSection**)&crit_crenderMT);

	if (cresult != CE_OK)
	{
		crit_crender->Release();
		return CE_ERR_FAIL;
	}

	Direct3D_Core *core = Direct3D_Core::GetInstance();

	if (core == nullptr)
	{
		crit_crender->Release();
		crit_crenderMT->Release();
		return CE_ERR_FAIL;
	}

	ConceptRenderer_D3D9 *temp = new ConceptRenderer_D3D9(core,cpuData,
															crit_crender,
															crit_crenderMT);

	*out_renderer = temp;

	return CE_OK;
}

ConceptRenderer_D3D9::ConceptRenderer_D3D9(Direct3D_Core *core,CPU_Info *cpuData,
										   CriticalSection *crit_crender,
										   CriticalSection *crit_crenderMT)
	: d3d_core(core),cpuData(cpuData),crender(nullptr),crenderMT(nullptr),
	crit_crender(crit_crender),crit_crenderMT(crit_crenderMT)
{
}

ConceptRenderer_D3D9::ConceptRenderer_D3D9()
{
	d3d_core = nullptr;
	cpuData = nullptr;

	crender = nullptr;
	crenderMT = nullptr;

	crit_crender = nullptr;
	crit_crenderMT = nullptr;
}

ConceptRenderer_D3D9::~ConceptRenderer_D3D9()
{
	if (d3d_core != nullptr)
	{
		d3d_core->Release();
		d3d_core = nullptr;
	}

	if (cpuData != nullptr)
	{
		cpuData->Release();
		cpuData = nullptr;
	}

	if (crender != nullptr)
	{
		crender->Release();
		crender = nullptr;
	}

	if (crenderMT != nullptr)
	{
		crenderMT->Release();
		crenderMT = nullptr;
	}

	if (crit_crender != nullptr)
	{
		crit_crender->Release();
	}

	if (crit_crenderMT != nullptr)
	{
		crit_crenderMT->Release();
	}
}

void ConceptRenderer_D3D9::Release()
{
	delete this;
}

const CRESULT ConceptRenderer_D3D9::GetRenderDevice(GraphicsAdapter *adapter, 
													const Ceng::UINT64 deviceOptions, 
													SwapChainDesc *parameters, 
													SwapChain **swapChainPtr,
													RenderDevice **devicePtr,
													RenderContext **contextPtr)
{
	CRESULT cresult;

	//Ceng::Log::Print("call : ConceptRenderer_Core::GetRenderDevice\n");

	if (parameters == nullptr)
	{
		//Ceng::Log::Print("\tError : parameters = nullptr\n");
		//return CE_ERR_INVALID_PARAM;
		return CE_ERR_DEBUG_0;
	}

	if (parameters->outputWindow == nullptr)
	{
		//Ceng::Log::Print("\tError : parameters->displayWindow = nullptr\n");
		//return CE_ERR_INVALID_PARAM;
		return CE_ERR_DEBUG_1;
	}

	if (devicePtr == nullptr)
	{
		//Ceng::Log::Print("\tError : devicePtr = nullptr\n");
		//return CE_ERR_NULL_PTR;
		return CE_ERR_DEBUG_2;
	}

	// Convert API parameters to Direct3D 9 format

	D3DFORMAT depthFormat;

	// Find desktop mode

	LPDIRECT3D9 corePtr = d3d_core->GetCore();
	
	HRESULT hr;


	DisplayMode crender_desktopMode;

	d3d_core->CurrentDisplayMode(adapter,crender_desktopMode);

	/*
	D3DDISPLAYMODE desktopMode;

	hr = corePtr->GetAdapterDisplayMode(d3d_adapter->index,&desktopMode);
	if (hr == D3DERR_INVALIDCALL)
	{
		//Ceng::Log::Print("\tError : Failed to get desktop mode\n");
		//return CE_ERR_FAIL;
		return CE_ERR_DEBUG_3;
	}
	*/

	//std::stringstream writer;

	/*
	Ceng::Log::Print("\tDesktop mode:\n");

	writer << "\twidth = " << desktopMode.Width << std::endl;
	writer << "\theight = " << desktopMode.Height << std::endl;
	writer << "\tformat = " << desktopMode.Format << std::endl;
	writer << "\trefresh rate = " << desktopMode.RefreshRate << std::endl;

	Ceng::Log::Print(writer.str().c_str());	
	*/

	D3DPRESENT_PARAMETERS d3d_Params;
	//memset(&d3d_Params,0,sizeof(D3DPRESENT_PARAMETERS));

	cresult = d3d_core->TranslateSwapChainDesc(*parameters, adapter, d3d_Params);

	if (cresult != Ceng::CE_OK)
	{
		return cresult;
	}

	if (parameters->windowed)
	{

	}


	/*
	if (!parameters->windowed)
	{
		//Ceng::Log::Print("Full screen mode");

		switch(parameters->displayMode.format)
		{
		case Ceng::IMAGE_FORMAT::C16:
			outputFormat = D3DFMT_R5G6B5;
			d3d_Params.BackBufferFormat = D3DFMT_R5G6B5;
			break;
		case Ceng::IMAGE_FORMAT::C16_A1:
			outputFormat = D3DFMT_X1R5G5B5;
			d3d_Params.BackBufferFormat = D3DFMT_A1R5G5B5;
			break;
		case Ceng::IMAGE_FORMAT::C32_ARGB:
			outputFormat = D3DFMT_X8R8G8B8;
			d3d_Params.BackBufferFormat = D3DFMT_A8R8G8B8;
			break;
		case Ceng::IMAGE_FORMAT::C32_A2_RGB:
			outputFormat = D3DFMT_A2R10G10B10;
			d3d_Params.BackBufferFormat = D3DFMT_A2R10G10B10;
			break;
		default:
			//Ceng::Log::Print("Error: display format not supported");
			return CE_ERR_NOT_SUPPORTED;
			break;
		}
	}
	else
	{
		// Windowed mode
		//Ceng::Log::Print("Windowed mode");

		outputFormat = desktopMode.Format;
		d3d_Params.BackBufferFormat = desktopMode.Format;
	}
	*/

	// Since we use Direct3D only to display the output of a 
	// software renderer, find any depth format compatible with
	// back buffer format.

	D3DFORMAT depthTest[6] = {D3DFMT_D16, D3DFMT_D24X8, D3DFMT_D24S8,
								D3DFMT_D24X4S4, D3DFMT_D32, D3DFMT_D24FS8 };

	int formatIndex;
	bool foundDepthFormat = false;

	for(formatIndex=0;formatIndex<6;formatIndex++)
	{
		hr = corePtr->CheckDeviceFormat(D3DADAPTER_DEFAULT,
											D3DDEVTYPE_HAL, d3d_Params.BackBufferFormat,
											D3DUSAGE_DEPTHSTENCIL,
											D3DRTYPE_SURFACE,
											depthTest[formatIndex]);

		if (hr == D3D_OK)
		{
			depthFormat = depthTest[formatIndex];
			foundDepthFormat = true;
			break;
		}
	}

	if (foundDepthFormat == false)
	{
		//Ceng::Log::Print("\tError : Couldn't find compatible depth format\n");
		//return CE_ERR_NOT_SUPPORTED;
		return CE_ERR_DEBUG_4;
	}

	// Set up parameters

	//D3DPRESENT_PARAMETERS d3d_params;

	Ceng::IMAGE_FORMAT::value crender_depthFormat;
	Ceng::BOOL autoDepth = false;
	if (parameters->autoDepthStencil)
	{
		autoDepth = true;

		crender_depthFormat = parameters->autoDepthStencilFormat;

		parameters->autoDepthStencilFormat = Direct3D_Core::ReverseMapFormat(depthFormat);
	}

	d3d_Params.EnableAutoDepthStencil = TRUE;
	d3d_Params.AutoDepthStencilFormat = depthFormat;

	d3d_Params.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3d_Params.MultiSampleQuality = 0;

	if (parameters->windowed)
	{
		// Override normal window size

		d3d_Params.BackBufferWidth = crender_desktopMode.width;
		d3d_Params.BackBufferHeight = crender_desktopMode.height;
	}

	DWORD d3d_DeviceFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	if (deviceOptions & Ceng::E_DeviceOption::disable_print_screen)
	{
		d3d_DeviceFlags |= D3DCREATE_DISABLE_PRINTSCREEN;
	}

	if (deviceOptions & Ceng::E_DeviceOption::multi_threaded)
	{
		d3d_DeviceFlags |= D3DCREATE_MULTITHREADED;
	}

	if (deviceOptions & Ceng::E_DeviceOption::no_window_changes)
	{
		d3d_DeviceFlags |= D3DCREATE_NOWINDOWCHANGES;
	}

	if (deviceOptions & Ceng::E_DeviceOption::allow_screen_saver)
	{
		d3d_DeviceFlags |= D3DCREATE_SCREENSAVER;
	}

	if (autoDepth)
	{
		parameters->autoDepthStencilFormat = crender_depthFormat;
	}

	// Create Direct3D 9 device

	Direct3D9_Adapter* d3d_adapter = (Direct3D9_Adapter*)adapter;

	IDirect3DDevice9 *d3d_Device = nullptr;

	HWND focusWindow = d3d_Params.hDeviceWindow;

	hr = corePtr->CreateDevice(d3d_adapter->index,
								D3DDEVTYPE_HAL, focusWindow,
								d3d_DeviceFlags,&d3d_Params,&d3d_Device);
								
	if (hr != D3D_OK)
	{
		//Ceng::Log::Print("\tError : Failed to create device\n");
		//return CE_ERR_FAIL;

		parameters->bufferCount = d3d_Params.BackBufferCount;

		switch (hr)
		{
		case D3DERR_DEVICELOST:
			return CE_ERR_DEBUG_5;
		case D3DERR_INVALIDCALL:
			return CE_ERR_DEBUG_6;
		case D3DERR_NOTAVAILABLE:
			return CE_ERR_NOT_SUPPORTED;
		case D3DERR_OUTOFVIDEOMEMORY:
			return CE_ERR_OUT_OF_VIDEO_MEMORY;
		default:
			return CE_ERR_FAIL;
		}
	}

	// Create concept engine output interface

	Graphics2D_D3D9 *graphics2D;

	try
	{
		graphics2D = new Graphics2D_D3D9();
	}
	catch(std::bad_alloc&)
	{
		//Ceng::Log::Print("\tError : Failed to create output object\n");

		d3d_Device->Release();
		//return CE_ERR_OUT_OF_MEMORY;
		return CE_ERR_DEBUG_6;
	}

	// NOTE: control of d3d_Device is transfered to outputDevice

	cresult = graphics2D->ConfigureOutput(d3d_Device,&d3d_Params);

	if (cresult != CE_OK)
	{
		//Ceng::Log::Print("\tError : d3d_Output configure failed\n");

		graphics2D->Release();
		//return cresult;
		return CE_ERR_DEBUG_7;
	}

	// Load crender library

	
	RenderDeviceCall local_GetRenderDevice;


	//if (deviceOptions & E_DeviceOption::multi_threaded)
	//{
		crit_crenderMT->Lock();

		if (crenderMT == nullptr)
		{

			crenderMT = DLL_Handle::GetInstance(crender_mt_dll);

			if (crenderMT == nullptr)
			{
				//Ceng::Log::Print("Error: Failed to load SW renderer DLL");
				graphics2D->Release();
				//return CE_ERR_FAIL;
				return CE_ERR_DEBUG_8;
			}

			call_GetRenderDeviceMT = crenderMT->GetFunction("GetRenderDevice");

			if (call_GetRenderDeviceMT == nullptr)
			{
				//Ceng::Log::Print("Error: SW renderer DLL does not have function GetRenderDevice");
				graphics2D->Release();
				//return CE_ERR_FAIL;
				return CE_ERR_DEBUG_9;
			}
		}

		crit_crenderMT->Unlock();

		local_GetRenderDevice = (RenderDeviceCall)call_GetRenderDeviceMT;
	//}
	//else
	//{
		/*
		crit_crender->Lock();

		if (crender == nullptr)
		{
			crender = DLL_Handle::GetInstance(crender_dll);

			if (crender == nullptr)
			{
				graphics2D->Release();
				return CE_ERR_FAIL;
			}

			call_GetRenderDevice = crender->GetFunction("GetRenderDevice");

			if (call_GetRenderDevice == nullptr)
			{
				graphics2D->Release();
				return CE_ERR_FAIL;
			}
		}

		crit_crender->Unlock();

		local_GetRenderDevice = (RenderDeviceCall)call_GetRenderDevice;
		*/
	//}

	// Create renderer object

	RenderDevice *renderer=nullptr;
	RenderContext *context = nullptr;
	SwapChain *swapChain = nullptr;

	int result = local_GetRenderDevice(cpuData,
										&crender_desktopMode,
										graphics2D, parameters, &swapChain,
										&renderer,
										&context);

	if (result != 0)
	{
		//Ceng::Log::Print("Error: Failed to get SW render device");
		graphics2D->Release();
		//return CE_ERR_FAIL;
		return CE_ERR_DEBUG_10;
	}
	
	// Write output pointer
	*devicePtr = (RenderDevice*)renderer;
	*contextPtr = context;
	*swapChainPtr = swapChain;

	return CE_OK;
}

const CRESULT ConceptRenderer_D3D9::CreateSwapChain(RenderDevice *device,
	SwapChainDesc &swapChainDesc,
	SwapChain **chainPtr)
{
	return CE_OK;
}

const Ceng::UINT32 ConceptRenderer_D3D9::AdapterCount()
{
	return d3d_core->AdapterCount();
}

const Ceng::CRESULT ConceptRenderer_D3D9::EnumAdapter(const Ceng::UINT32 index, GraphicsAdapter **out_adapter)
{
	return d3d_core->EnumAdapter(index, out_adapter);
}

const Ceng::UINT32 ConceptRenderer_D3D9::CurrentDisplayMode(GraphicsAdapter *adapter, DisplayMode &out_mode)
{
	return d3d_core->CurrentDisplayMode(adapter, out_mode);
}

const Ceng::UINT32 ConceptRenderer_D3D9::DisplayModeCount(GraphicsAdapter *adapter, const Ceng::IMAGE_FORMAT::value format)
{
	return d3d_core->DisplayModeCount(adapter, format);
}

const Ceng::CRESULT ConceptRenderer_D3D9::EnumDisplayMode(GraphicsAdapter *adapter, const Ceng::UINT32 index,
	const Ceng::IMAGE_FORMAT::value format, DisplayMode &out_mode)
{
	return d3d_core->EnumDisplayMode(adapter, index, format, out_mode);
}

const Ceng::CRESULT ConceptRenderer_D3D9::CheckFramebufferSupport(GraphicsAdapter *adapter,
	const Ceng::IMAGE_FORMAT::value displayFormat,
	const Ceng::IMAGE_FORMAT::value backBufferFormat,
	const Ceng::BOOL windowed)
{
	return d3d_core->CheckFramebufferSupport(adapter, displayFormat, backBufferFormat, windowed);
}

const Ceng::CRESULT ConceptRenderer_D3D9::CheckBufferSupport(GraphicsAdapter *out_adapter,
	const Ceng::IMAGE_FORMAT::value displayFormat,
	const Ceng::BufferType::value type,
	const Ceng::IMAGE_FORMAT::value bufferFormat,
	const Ceng::UINT32 binding,
	const Ceng::BufferUsage::value usage,
	const Ceng::UINT32 cpuAccess,
	const Ceng::UINT32 options)
{
	return CE_OK;
}