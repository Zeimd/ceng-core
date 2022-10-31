/*****************************************************************************
*
* win32-window.cpp
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#include <ceng/interfaces/display-mode.h>

#include "../inc/ceng-win32.h"

#include "../inc/win32-window.h"
#include "../inc/winproc-thunk.h"

using namespace Ceng;

static LRESULT CALLBACK WindowProc(::HWND hwnd,::UINT msg,
											::WPARAM wParam,::LPARAM lParam);

static int instanceCounter = 0;

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_CreateWindow(Ceng::String &windowTitle,
											const Ceng::UINT32 locX,const Ceng::UINT32 locY,
											const Ceng::UINT32 width,const Ceng::UINT32 height,
											const Ceng::UINT32 options,
											Ceng::PlatformWindow *parent,
											Ceng::PlatformWindow **out_window)
{
	if (instanceCounter < 0)
	{
		return CE_ERR_FAIL;
	}

	WinProcThunk *thunk = WinProcThunk::GetInstance();

	if (thunk == nullptr)
	{
		return CE_ERR_OUT_OF_MEMORY;
	}

	::WNDCLASSEX windowClass;

	memset(&windowClass,0,sizeof(WNDCLASSEX));

	windowClass.cbSize = sizeof(WNDCLASSEX); // Window data size
	windowClass.style = CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS; // Class styles

	if (options & E_WindowOptions::own_device_context)
	{
		windowClass.style |= CS_OWNDC;
	}

	windowClass.cbClsExtra = 0; // Extra bytes to allocate after WNDCLASSEX struct
	windowClass.cbWndExtra = 0; // Extra bytes to allocate after instance of struct
	windowClass.hInstance = GetModuleHandle(NULL);//hInstance; // Instance of the application
	windowClass.hIcon = NULL; // Class icon
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW); // Class mouse pointer
	
	windowClass.lpszMenuName = NULL; // Menu resource

	Ceng::StringUtf16 *className = new StringUtf16("ceng-window-class-");

	*className += instanceCounter;

#ifdef UNICODE
	windowClass.lpszClassName = className->ToWString(); // Name of the class
#else
	windowClass.lpszClassName = className->ToCString(); // Name of the class
#endif

	windowClass.hIconSm = NULL; // Small icon for the class

	// Pointer to callback function

	// TODO: Replace with a function that calls this->WindowProc() instead
	//windowClass.lpfnWndProc = (WNDPROC)&WindowProc; 

	windowClass.lpfnWndProc = thunk->GetCallback();

	// Register class
#ifdef UNICODE
	if (!RegisterClassExW(&windowClass))
#else
	if (!RegisterClassEx(&windowClass))
#endif
	{
		delete thunk;
		return CE_ERR_INVALID_PARAM;
	}

	int statusFlags=0;

	DWORD style=0,extendedStyle=0;

	if (options & E_WindowOptions::popup)
	{
		style |= WS_POPUP;

		statusFlags |= E_WindowStatus::full_client;
	}
	else
	{
		windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW); // Background color

		style |= WS_CAPTION | WS_SYSMENU;
		style |= WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
	}

	if (options & E_WindowOptions::start_minimized)
	{
		style |= WS_MINIMIZE;
	}

	if (options & E_WindowOptions::start_maximized)
	{
		style |= WS_MAXIMIZE;
	}	

	if (options & E_WindowOptions::resizable)
	{
		style |= WS_SIZEBOX;
	}
	
	if (options & E_WindowOptions::topmost)
	{
		extendedStyle |= WS_EX_TOPMOST;
		style |= WS_EX_TOPMOST;
	}

	Ceng::StringUtf16 *caption = new Ceng::StringUtf16(windowTitle);


	Ceng::StringUtf16 *fullCaption = new Ceng::StringUtf16(*caption);
	
	int clientWidth = width;
	int clientHeight = height;

	// TODO: Should be in client code

	*fullCaption += " | ";
	*fullCaption += clientWidth;
	*fullCaption += " x ";
	*fullCaption += clientHeight;

	WinAPI_Window *newWindow = new WinAPI_Window(caption,fullCaption,
													&windowClass,className,thunk);
	HWND windowHandle = NULL;

	HWND parentHandle = HWND_DESKTOP;

	if (parent != nullptr)
	{
		auto win32_parent = static_cast<WinAPI_Window*>(parent);

		parentHandle = win32_parent->GetWindowHandle();
	}

	windowHandle = CreateWindowExW(extendedStyle,
									className->ToWString(),
									fullCaption->ToWString(),
									style,
									locX,locY,
									clientWidth,clientHeight,
									parentHandle,NULL,
									GetModuleHandle(NULL),NULL);


	if (windowHandle == NULL)
	{
		::DWORD error = GetLastError();

		delete newWindow;
		return CE_ERR_INVALID_PARAM;
	}

	int newWidth,newHeight;

	newWidth = width;
	newHeight = height;

	RECT desktopRect;

	GetWindowRect(::GetDesktopWindow(),&desktopRect);

	DisplayMode desktopMode;

	desktopMode.width = desktopRect.right-desktopRect.left;
	desktopMode.height = desktopRect.bottom-desktopRect.top;

	int screenLocX = locX;
	int screenLocY = locY;

	if (options & ~E_WindowOptions::popup)
	{
		// Resize window so that client area is given by *width*,*height*
		RECT windowRect,clientRect;
		
		::GetWindowRect(windowHandle,&windowRect);
		::GetClientRect(windowHandle,&clientRect);
		
		LONG window_dx,window_dy,client_dx,client_dy;
		
		window_dx = windowRect.right-windowRect.left;
		window_dy = windowRect.bottom-windowRect.top;
		
		client_dx = clientRect.right-clientRect.left;
		client_dy = clientRect.bottom-clientRect.top;
		
		newWidth = clientWidth + (window_dx-client_dx);
		newHeight = clientHeight + (window_dy-client_dy);
		
		if (options & E_WindowOptions::center_x)
		{
			screenLocX = (desktopMode.width - newWidth) >> 1;
		}

		if (options & E_WindowOptions::center_y)
		{
			screenLocY = (desktopMode.height - newHeight) >> 1;
		}
		
		::MoveWindow(windowHandle,screenLocX,screenLocY,
			newWidth,newHeight,FALSE);
	}

	/*
	newWindow->Configure(caption,fullCaption,windowHandle,&windowClass,className,
							statusFlags,screenLocX,screenLocY,newWidth,newHeight);
							*/

	newWindow->Configure(caption, fullCaption, windowHandle, &windowClass, className,
		statusFlags, screenLocX, screenLocY, clientWidth, clientHeight);

	++instanceCounter;

	*out_window = (Ceng::PlatformWindow*)newWindow;

	return CE_OK;
}

extern "C" const CRESULT Ceng_MessageWindow(Ceng::PlatformWindow *parent,const String &windowTitle,
											const Ceng::String &message)
{
	int result;

	Ceng::WinAPI_Window *window = (WinAPI_Window*)parent;

	Ceng::StringUtf16 message_utf16 = message;
	Ceng::StringUtf16 windowTitle_utf16 = windowTitle;

	HWND handle = NULL;

	if (window != nullptr)
	{
		handle = window->GetWindowHandle();
	}

	result = MessageBoxW(handle, message_utf16.ToWString(), windowTitle_utf16.ToWString(), MB_OK);

	return CE_OK;
}

WinAPI_Window::WinAPI_Window(Ceng::StringUtf16 *caption,Ceng::StringUtf16 *fullCaption,
							 WNDCLASSEX *windowClass,Ceng::StringUtf16 *className,
							 WinProcThunk *thunk)
	: caption(caption),fullCaption(fullCaption),className(className),thunk(thunk),
	windowHandle(NULL)
{
	memcpy(&this->windowClass,windowClass,sizeof(WNDCLASSEX));

	thunk->SetWindow(this);
}

void WinAPI_Window::Configure(Ceng::StringUtf16 *caption,Ceng::StringUtf16 *fullCaption,
							 HWND windowHandle,
							 WNDCLASSEX *windowClass,Ceng::StringUtf16 *className,
							 int statusFlags,
							 const Ceng::UINT32 locX,const Ceng::UINT32 locY,
							 const Ceng::UINT32 width,const Ceng::UINT32 height)
{
	this->windowHandle = windowHandle;

	this->className = className;

	this->screenLocX = locX;
	this->screenLocY = locY;

	this->clientWidth = width;
	this->clientHeight = height;

	this->statusFlags = statusFlags | E_WindowStatus::active;

	//sdl_window = SDL_CreateWindowFrom(windowHandle);
}

WinAPI_Window::WinAPI_Window()
{
	windowHandle = NULL;

	screenLocX = 0;
	screenLocY = 0;

	clientWidth = 0;
	clientHeight = 0;

	statusFlags = 0;
}

WinAPI_Window::~WinAPI_Window()
{
	if (windowHandle != NULL)
	{
		//SDL_DestroyWindow(sdl_window);

		::DestroyWindow(windowHandle);
	}

	::UnregisterClassW(className->ToWString(),GetModuleHandle(NULL));

	delete className;
	delete caption;
	delete fullCaption;

	delete thunk;
}

void WinAPI_Window::Release()
{
	delete this;
}

const Ceng::BOOL WinAPI_Window::IsDestroyed()
{
	return (statusFlags & E_WindowStatus::destroyed);
}

const Ceng::BOOL WinAPI_Window::IsActive()
{
	return (statusFlags & E_WindowStatus::active);
}

const Ceng::BOOL WinAPI_Window::IsVisible()
{
	return (statusFlags & E_WindowStatus::visible);
}

const Ceng::BOOL WinAPI_Window::IsResized()
{
	if (resized == true)
	{
		resized = false;
		return true;
	}
	return false;
}

const Ceng::BOOL WinAPI_Window::IsForeground()
{
	HWND temp = ::GetForegroundWindow();

	return (temp == windowHandle);
}

const Ceng::BOOL WinAPI_Window::KeyboardFocus()
{
	HWND temp = ::GetFocus();

	return (temp == windowHandle);
}

HWND WinAPI_Window::GetWindowHandle()
{
	return windowHandle;
}

LRESULT WinAPI_Window::WindowProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	short *dimSelector = (short*)&lParam;

	RECT clientRect;
	LONG client_dx,client_dy;

	switch (msg)
	{
	case WM_SIZE:

		if( (statusFlags & E_WindowStatus::full_client) == 0)
		{
			// NOTE: Messes up full screen mode 

			GetClientRect(windowHandle,&clientRect);	
			
			client_dx = clientRect.right-clientRect.left;
			client_dy = clientRect.bottom-clientRect.top;
			
			if (wParam == SIZE_MINIMIZED)
			{
				statusFlags &= ~E_WindowStatus::visible;
			}
			else if (wParam == SIZE_MAXIMIZED)
			{
				clientWidth = client_dx;
				clientHeight = client_dy;

				statusFlags |= E_WindowStatus::visible;
				
				resized = true;
			}
			else if (wParam == SIZE_RESTORED)
			{
				clientWidth = client_dx;
				clientHeight = client_dy;
				
				statusFlags |= E_WindowStatus::visible;
				
				resized = true;
			}		
		}
		return 0;
		break;
	case WM_SHOWWINDOW:
		if (wParam == TRUE)
		{
			statusFlags |= E_WindowStatus::visible;
		}
		else
		{
			statusFlags &= ~E_WindowStatus::visible;
		}
		return 0;
		break;
	case WM_ACTIVATEAPP:
		if (wParam == TRUE)
		{
			statusFlags |= E_WindowStatus::active;
			statusFlags |= E_WindowStatus::visible;
		}
		else
		{
			statusFlags &= ~E_WindowStatus::active;

			if (statusFlags & E_WindowStatus::full_client)
			{
				statusFlags &= ~E_WindowStatus::visible;
			}
		}
		return 0;
		break;
	case WM_CLOSE:
		statusFlags |= E_WindowStatus::destroyed;
		return 0;
		break;	
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
        break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONDBLCLK:
		break;
	case WM_RBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_RBUTTONDBLCLK:
		break;
		/*
	case WM_ERASEBKGND:
		break;
	case WM_CHILDACTIVATE:
		break;
	case WM_CANCELMODE:
		break;
	case WM_COMPACTING:
		break;
	case WM_ENTERSIZEMOVE:
		break;
	case WM_CREATE:
		break;
		*/
	default:
		//Call default window handler
		return DefWindowProc(hwnd,msg,wParam,lParam);
	};
	return 0;
}

const CRESULT WinAPI_Window::ProcessMessages()
{
	MSG message;
	::BOOL result;

	if (statusFlags & E_WindowStatus::destroyed)
	{
		return CE_OK;
	}

	if (statusFlags & E_WindowStatus::visible)
	{
		if(PeekMessageW(&message,NULL,0,0,PM_NOREMOVE))
		{
			result = GetMessageW(&message,NULL,0,0);

			if (result == -1)
			{
				return CE_ERR_FAIL;
			}
			else if (result == 0)
			{
				// Signal exit
				statusFlags |= E_WindowStatus::destroyed;
				return CE_OK;
			}
			
			TranslateMessage(&message);
			DispatchMessageW(&message);
		}
	}
	else
	{
		result = GetMessageW(&message,NULL,0,0);
		
		if (result == -1)
		{
			return CE_ERR_FAIL;
		}
		else if (result == 0)
		{
			// Signal exit
			statusFlags |= E_WindowStatus::destroyed;
			return CE_OK;
		}
		
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}

	if (statusFlags & E_WindowStatus::visible)
	{
		UpdateWindow(windowHandle);
	}

	return CE_OK;
}

const CRESULT WinAPI_Window::SetCaption(const String &text)
{
	if (text.Length() == 0)
	{
		return CE_ERR_FAIL;
	}

	*caption = text;

	*fullCaption = *caption + captionExtra;

	SetWindowTextW(windowHandle, fullCaption->ToWString());

	return CE_OK;
}

const CRESULT WinAPI_Window::SetCaptionExtra(const String &extra)
{
	if (extra.Length() == 0)
	{
		return CE_OK;
	}

	captionExtra = extra;

	*fullCaption = *caption + captionExtra;

	SetWindowTextW(windowHandle, fullCaption->ToWString());

	return CE_OK;
}

void WinAPI_Window::GetClientArea(Ceng::UINT32 *widthPtr,
								  Ceng::UINT32 *heightPtr)
{
	*widthPtr = clientWidth;
	*heightPtr = clientHeight;
}

void WinAPI_Window::Show()
{
	ShowWindow(windowHandle,SW_SHOW);

	statusFlags |= E_WindowStatus::visible;
}

void WinAPI_Window::Hide()
{
	ShowWindow(windowHandle,SW_HIDE);

	statusFlags &= ~E_WindowStatus::visible;
}

const CRESULT WinAPI_Window::Redraw()
{
	UpdateWindow(windowHandle);
	return CE_OK;
}

void WinAPI_Window::Minimize()
{
}

void WinAPI_Window::Maximize()
{
}