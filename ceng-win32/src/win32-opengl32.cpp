/*****************************************************************************
*
* win32-opengl32.cpp
*
* Created By Jari Korkala 15/3/2015
*
*****************************************************************************/

#include <Windows.h>

#include "../inc/ceng-win32.h"
#include "../inc/win32-opengl32.h"
#include "../inc/gl32-adapter.h"
#include "../inc/gl33-swap-chain.h"
#include "../inc/gl33-device.h"
#include "../inc/gl33-context.h"

using namespace Ceng;

const Ceng::CRESULT GL32_GraphicsSystem::GetInstance(CPU_Info *cpuData, Ceng::GraphicsSystem **out_system, LogType *log)
{
	if (out_system == nullptr)
	{
		return CE_ERR_NULL_PTR;
	}

	*out_system = nullptr;

	PlatformWindow *out_window;
	
	CRESULT cresult = Ceng_CreateWindow(Ceng::String("dummyWindow"), 0, 0, 10, 10,E_WindowOptions::own_device_context,nullptr,&out_window);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	WinAPI_Window *window = (WinAPI_Window*)out_window;

	::HDC deviceContext = ::GetDC(window->GetWindowHandle());

	Ceng::INT32 pixelFormat = GL32_GraphicsSystem::FindSimplePixelFormat(deviceContext, IMAGE_FORMAT::unorm_x8_b8_g8_r8);

	::PIXELFORMATDESCRIPTOR pixelDesc;

	memset(&pixelDesc, 0, sizeof(::PIXELFORMATDESCRIPTOR));

	pixelDesc.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
	pixelDesc.nVersion = 1;

	::DescribePixelFormat(deviceContext, pixelFormat, sizeof(::PIXELFORMATDESCRIPTOR), &pixelDesc);

	::SetPixelFormat(deviceContext, pixelFormat, &pixelDesc);

	::HGLRC renderContext = wglCreateContext(deviceContext);

	if (renderContext == NULL)
	{
		window->Release();
		::DWORD error = ::GetLastError();

		return CE_ERR_FAIL;
	}

	::BOOL result = wglMakeCurrent(deviceContext, renderContext);

	if (!result)
	{
		::DeleteDC(deviceContext);
		window->Release();
		return CE_ERR_FAIL;
	}

	glewExperimental = TRUE;

	GLenum error = glewInit();

	if (error != GLEW_OK)
	{
		wglMakeCurrent(NULL, NULL);
		::DeleteDC(deviceContext);
		window->Release();

		return CE_ERR_FAIL;
	}

	if (!WGLEW_ARB_pixel_format || !WGLEW_ARB_create_context_profile || !WGLEW_ARB_create_context)
	{
		wglMakeCurrent(NULL, NULL);
		::DeleteDC(deviceContext);
		window->Release();

		return CE_ERR_FAIL;
	}

	const GLubyte *versionString = glGetString(GL_VERSION);

	// Check that OpenGL version 3.3 is supported
	if (versionString[0] < 3 || versionString[2] < 3)
	{
		wglMakeCurrent(NULL, NULL);
		::DeleteDC(deviceContext);
		window->Release();
		return CE_ERR_FAIL;
	}

	*out_system = static_cast<Ceng::GraphicsSystem*>(new GL32_GraphicsSystem(window,deviceContext,renderContext));

	return CE_OK;
}

GL32_GraphicsSystem::GL32_GraphicsSystem() : dummyWindow(nullptr),dummyDeviceContext(NULL),dummyRenderContext(NULL)
{
}

GL32_GraphicsSystem::GL32_GraphicsSystem(WinAPI_Window *window, ::HDC deviceContext, ::HGLRC renderContext)
	: dummyWindow((WinAPI_Window*)window),dummyDeviceContext(deviceContext),dummyRenderContext(renderContext)
{
	

	/*
	const GLubyte *versionString = glGetString(GL_VERSION);

	Ceng::String verString = (const char*)versionString;

	Ceng::String major = verString.SubString(verString.ConstBeginIterator(), verString.FindFirst('.',verString.ConstBeginIterator()));
	*/
}

GL32_GraphicsSystem::~GL32_GraphicsSystem()
{
	if (dummyWindow != nullptr)
	{
		dummyWindow->Release();
	}

	if (dummyRenderContext != NULL)
	{
		wglMakeCurrent(NULL,NULL);
		wglDeleteContext(dummyRenderContext);
	}

	if (dummyDeviceContext != NULL)
	{
		::DeleteDC(dummyDeviceContext);
	}
}

void GL32_GraphicsSystem::Release()
{
	delete this;
}

const Ceng::UINT32 GL32_GraphicsSystem::AdapterCount()
{
	Ceng::UINT32 count = 0;

	::DISPLAY_DEVICE deviceData;
	::BOOL result;

	deviceData.cb = sizeof(::DISPLAY_DEVICE);
	
	while (result = ::EnumDisplayDevices(NULL, count, &deviceData, 0))
	{
		++count;
	};

	return count;
}

const Ceng::CRESULT GL32_GraphicsSystem::EnumAdapter(const Ceng::UINT32 index, GraphicsAdapter **out_adapter)
{
	::DISPLAY_DEVICE deviceData;

	deviceData.cb = sizeof(::DISPLAY_DEVICE);

	::BOOL result = ::EnumDisplayDevices(NULL, index, &deviceData, 0);

	if (!result)
	{
		return CE_ERR_INVALID_PARAM;
	}

	*out_adapter = new GL32_GraphicsAdapter(deviceData);

	return CE_OK;
}

const Ceng::IMAGE_FORMAT::value GL32_GraphicsSystem::BitsToFormat(const Ceng::UINT32 colorBits)
{
	switch (colorBits)
	{
	case 16:
		return IMAGE_FORMAT::unorm_r5_g6_b5;
	case 24:
		return IMAGE_FORMAT::unorm_r8_g8_b8;
	case 32:
		return IMAGE_FORMAT::unorm_x8_r8_g8_b8;
	case 64:
		return IMAGE_FORMAT::unorm_a16_b16_g16_r16;
	default:
		return IMAGE_FORMAT::UNKNOWN;
	}
}

const CRESULT GL32_GraphicsSystem::TranslateDisplayMode(GraphicsAdapter *adapter, const Ceng::UINT32 index, DisplayMode &out_mode)
{
	GL32_GraphicsAdapter *gl_adapter = (GL32_GraphicsAdapter*)adapter;

	::DEVMODE modeData;

	memset(&modeData, 0, sizeof(::DEVMODE));

	modeData.dmSize = sizeof(::DEVMODE);

	::BOOL result;

	result = ::EnumDisplaySettings(gl_adapter->deviceData.DeviceName, index, &modeData);

	if (!result)
	{
		return CE_ERR_INVALID_PARAM;
	}

	out_mode.format = BitsToFormat(modeData.dmBitsPerPel);

	out_mode.width = modeData.dmPelsWidth;
	out_mode.height = modeData.dmPelsHeight;
	out_mode.refreshHz = modeData.dmDisplayFrequency;

	return CE_OK;
}

const Ceng::UINT32 GL32_GraphicsSystem::CurrentDisplayMode(GraphicsAdapter *adapter,
	DisplayMode &out_mode)
{
	return TranslateDisplayMode(adapter, ENUM_CURRENT_SETTINGS, out_mode);
}

const Ceng::UINT32 GL32_GraphicsSystem::DisplayModeCount(GraphicsAdapter *adapter,
	const Ceng::IMAGE_FORMAT::value format)
{
	DisplayMode tempMode;

	Ceng::UINT32 k = 0;
	Ceng::UINT32 counter=0;

	while (TranslateDisplayMode(adapter, k, tempMode) == CE_OK)
	{
		if (tempMode.format == format)
		{
			++counter;
		}

		++k;
	};

	return counter;
}

const Ceng::CRESULT GL32_GraphicsSystem::EnumDisplayMode(GraphicsAdapter *adapter, const Ceng::UINT32 index,
	const Ceng::IMAGE_FORMAT::value format, DisplayMode &out_mode)
{
	Ceng::UINT32 k=0;
	Ceng::UINT32 counter=0;
	
	while (TranslateDisplayMode(adapter,k, out_mode) == CE_OK)
	{
		if (out_mode.format == format)
		{
			if (counter == index) return CE_OK;

			++counter;
		}

		++k;
	};	
	
	return CE_OK;
}

const Ceng::INT32 GL32_GraphicsSystem::FindSimplePixelFormat(::HDC context,const Ceng::IMAGE_FORMAT::value format)
{
	BufferBits bits(format);

	return ::ChoosePixelFormat(context, &bits.desc);
}

const Ceng::CRESULT GL32_GraphicsSystem::CheckFramebufferSupport(GraphicsAdapter *adapter,
	const Ceng::IMAGE_FORMAT::value displayFormat,
	const Ceng::IMAGE_FORMAT::value backBufferFormat,
	const Ceng::BOOL windowed)
{
	GL32_GraphicsAdapter *gl_adapter = (GL32_GraphicsAdapter*)adapter;

	BufferBits backBufferBits(backBufferFormat);
	BufferBits displayBits(displayFormat);

	if (windowed)
	{
		/*
		DisplayMode currentMode;

		CurrentDisplayMode(adapter, currentMode);
		*/

		//::HWND desktopHandle = ::GetDesktopWindow();

		/*
		::HDC desktopContext = ::GetWindowDC(NULL);

		if (desktopContext == NULL)
		{
			return CE_ERR_FAIL;
		}

		::PIXELFORMATDESCRIPTOR currentDesc;

		memset(&currentDesc, 0, sizeof(::PIXELFORMATDESCRIPTOR));
		currentDesc.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
		currentDesc.nVersion = 1;

		int currentPixelFormat = ::GetPixelFormat(desktopContext);

		if (currentPixelFormat == 0)
		{
			::DWORD error = ::GetLastError();
			
			return CE_ERR_FAIL;
		}

		::DescribePixelFormat(desktopContext, currentPixelFormat, sizeof(::PIXELFORMATDESCRIPTOR), &currentDesc);

		::ReleaseDC(NULL,desktopContext);

		if (!displayBits.IsMatchColorAlpha(currentDesc))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
		*/
	}
	else
	{
		if (!backBufferBits.IsMatchColor(displayBits))
		{
			return CE_ERR_NOT_SUPPORTED;
		}
	}

	int pixelFormat = FindSimplePixelFormat(dummyDeviceContext, backBufferFormat);

	if (pixelFormat == 0)
	{
		return CE_ERR_NOT_SUPPORTED;
	}

	::PIXELFORMATDESCRIPTOR out_desc;

	memset(&out_desc, 0, sizeof(::PIXELFORMATDESCRIPTOR));

	out_desc.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
	out_desc.nVersion = 1;

	int result = ::DescribePixelFormat(dummyDeviceContext, pixelFormat,sizeof(::PIXELFORMATDESCRIPTOR), &out_desc);

	if (!result)
	{
		return CE_ERR_NOT_SUPPORTED;
	}

	Ceng::BOOL test = backBufferBits.IsMatchColorAlpha(out_desc);

	Ceng::CRESULT cresult = CE_OK;

	if (!test)
	{
		cresult = CE_ERR_NOT_SUPPORTED;
	}	

	return cresult;
}

const Ceng::CRESULT GL32_GraphicsSystem::CheckBufferSupport(GraphicsAdapter *adapter,
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

const CRESULT GL32_GraphicsSystem::CreateSwapChain(RenderDevice *device,
	SwapChainDesc &swapChainDesc,
	SwapChain **chainPtr)
{
	return CE_OK;
}

const CRESULT GL32_GraphicsSystem::GetRenderDevice(GraphicsAdapter *adapter,
	const Ceng::UINT64 deviceOptions,
	SwapChainDesc *swapChainDesc,
	SwapChain **swapChainPtr,
	RenderDevice **devicePtr,
	RenderContext **contextPtr)
{

	BufferBits bits(swapChainDesc->displayMode.format, swapChainDesc->autoDepthStencilFormat);

	// Select pixel format

	const int attributeList[] =
	{
		WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
		WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
		WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB, bits.desc.cColorBits,
		WGL_DEPTH_BITS_ARB, bits.desc.cDepthBits,
		WGL_STENCIL_BITS_ARB, bits.desc.cStencilBits,
		0
	};

	WinAPI_Window *deviceWindow = (WinAPI_Window*)swapChainDesc->outputWindow;

	::HDC deviceContext = ::GetWindowDC(deviceWindow->GetWindowHandle());

	if (deviceContext == NULL)
	{
		return CE_ERR_FAIL;
	}

	Ceng::INT32 formatList[16];

	memset(formatList, 0, sizeof(Ceng::INT32) * 16);

	Ceng::UINT32 outputSize;

	::BOOL result = wglChoosePixelFormatARB(deviceContext, attributeList, NULL, 1, formatList, &outputSize);

	if (!result)
	{
		return CE_ERR_FAIL;
	}

	if (outputSize == 0)
	{
		return CE_ERR_NOT_SUPPORTED;
	}

	::PIXELFORMATDESCRIPTOR pixelDesc;

	result = ::SetPixelFormat(deviceContext, formatList[0], &pixelDesc);
	
	//result = wglSetPixelFormatARB(deviceContext, attributeList, NULL, 1, &formatList[0], &outputSize);

	if (!result)
	{
		return CE_ERR_FAIL;
	}

	// Create render context

	const int renderAttributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB,3,
		WGL_CONTEXT_MINOR_VERSION_ARB,3,
		WGL_CONTEXT_PROFILE_MASK_ARB,WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	HGLRC gl_renderContext = wglCreateContextAttribsARB(deviceContext, NULL, renderAttributes);

	if (gl_renderContext == NULL)
	{
		return CE_ERR_FAIL;
	}

	wglMakeCurrent(deviceContext, gl_renderContext);
	
	GL33_RenderDevice *tempDev = new GL33_RenderDevice(swapChainDesc->outputWindow, deviceContext, gl_renderContext);

	*devicePtr = tempDev;

	*contextPtr = new GL33_RenderContext(swapChainDesc->outputWindow, deviceContext, 
		gl_renderContext,tempDev);

	*swapChainPtr = new GL33_SwapChain(swapChainDesc, deviceContext, gl_renderContext, (GL33_RenderContext*)*contextPtr);

	return CE_OK;
}