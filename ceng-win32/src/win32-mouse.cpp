/*****************************************************************************
*
* sdl-mouse.cpp
*
* By Jari Korkala 15/12/2015
*
*****************************************************************************/

#include <dinput.h>

#include "../inc/win32-window.h"
#include "../inc/win32-mouse.h"

using namespace Ceng;

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_ShowSystemCursor(const Ceng::BOOL visible)
{
	if (visible)
	{
		while(::ShowCursor(TRUE) < 0);
	}
	else
	{
		while(::ShowCursor(FALSE) >=0);
	}

	return CE_OK;
}

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_CreateMouse(Ceng::PlatformWindow *window,
	Ceng::MouseDevice **device)
{
	WinAPI_Window *api_window = static_cast<WinAPI_Window*>(window);

	LPDIRECTINPUT8 core;

	HRESULT hresult;

	hresult = DirectInput8Create(::GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(LPVOID*)&core, nullptr);
	if (hresult != DI_OK)
	{
		return CE_ERR_FAIL;
	}

	LPDIRECTINPUTDEVICE8 mouseDevice;

	hresult = core->CreateDevice(GUID_SysMouse, &mouseDevice, NULL);
	if (hresult != DI_OK)
	{
		core->Release();
		return CE_ERR_FAIL;
	}

	// Set data format
	hresult = mouseDevice->SetDataFormat(&c_dfDIMouse2);
	if (hresult != DI_OK)
	{
		mouseDevice->Release();
		core->Release();

		return CE_ERR_FAIL;
	}

	// Set cooperative level
	hresult = mouseDevice->SetCooperativeLevel(api_window->GetWindowHandle(),
		DISCL_NONEXCLUSIVE |
		DISCL_FOREGROUND);
	if (hresult != DI_OK)
	{
		mouseDevice->Release();
		core->Release();

		return CE_ERR_FAIL;
	}

	// Set buffer size

	DIPROPDWORD dipwd;

	dipwd.diph.dwSize = sizeof(DIPROPDWORD);
	dipwd.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipwd.diph.dwObj = 0;
	dipwd.diph.dwHow = DIPH_DEVICE;

	dipwd.dwData = 16;

	hresult = mouseDevice->SetProperty(DIPROP_BUFFERSIZE, &dipwd.diph);
	if (hresult != DI_OK)
	{
		mouseDevice->Release();
		core->Release();

		return CE_ERR_FAIL;
	}

	*device = new Mouse_DirectInput(api_window,core,mouseDevice);

	return CE_OK;
}

Mouse_DirectInput::Mouse_DirectInput()
{
}

Mouse_DirectInput::Mouse_DirectInput(WinAPI_Window *focusWindow, LPDIRECTINPUT8 core,
	LPDIRECTINPUTDEVICE8 mouseDevice)
	: focusWindow(focusWindow),core(core),mouseDevice(mouseDevice)
{
	
}


Mouse_DirectInput::~Mouse_DirectInput()
{
	mouseDevice->Release();
	core->Release();

	::ClipCursor(NULL);
}

void Mouse_DirectInput::Release()
{
	delete this;
}

const Ceng::CRESULT Mouse_DirectInput::RelativeMode(const Ceng::BOOL state)
{
	DIPROPDWORD dipwd;

	dipwd.diph.dwSize = sizeof(DIPROPDWORD);
	dipwd.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipwd.diph.dwObj = 0;
	dipwd.diph.dwHow = DIPH_DEVICE;
	
	dipwd.dwData = DIPROPAXISMODE_ABS;

	if (state == true)
	{
		dipwd.dwData = DIPROPAXISMODE_REL;
	}

	HRESULT hr = mouseDevice->SetProperty(DIPROP_AXISMODE, &dipwd.diph);
	if (hr != DI_OK)
	{
		return CE_ERR_FAIL;
	}

	relative = state;
	return CE_OK;
}


const CRESULT Mouse_DirectInput::Restore()
{
	HRESULT hresult;

	// Read complete keyboard status
	hresult = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &di_state);
	if (hresult == DI_OK)
	{
		return CE_OK;
	}
	else if (hresult == DIERR_NOTACQUIRED || hresult == DIERR_INPUTLOST)
	{
		hresult = mouseDevice->Acquire();

		// Check if an another application has
		// keyboard focus
		if (hresult == DIERR_OTHERAPPHASPRIO)
		{
			return CE_OK;
		}

		// If the application has focus, wait until
		// the keyboard is acquired
		while (hresult != DI_OK)
		{
			hresult = mouseDevice->Acquire();
		};

		hresult = mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &di_state);

		return CE_OK;
	}

	return CE_ERR_FAIL;
}

const Ceng::CRESULT Mouse_DirectInput::GetState(MouseState *state)
{
	state->relative = relative;

	if (relative)
	{
		state->xRelative = di_state.lX;
		state->yRelative = di_state.lY;
	}
	
	return CE_OK;
}

const Ceng::CRESULT Mouse_DirectInput::ClipToWindow(const Ceng::BOOL clip)
{
	if (clip)
	{
		HWND handle = focusWindow->GetWindowHandle();

		RECT rect;

		::GetWindowRect(handle, &rect);

		::ClipCursor(&rect);

	}
	else
	{
		::ClipCursor(NULL);
	}

	return CE_OK;
}