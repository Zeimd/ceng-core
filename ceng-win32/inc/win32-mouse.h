/*****************************************************************************
*
* sdl-mouse.h
*
* By Jari Korkala 15/12/2015
*
*****************************************************************************/

#ifndef CENG_WIN32_MOUSE_H
#define CENG_WIN32_MOUSE_H

#include <dinput.h>

#include <ceng/interfaces/mouse-device.h>

namespace Ceng
{
	class Mouse_DirectInput : public MouseDevice
	{
	protected:

		LPDIRECTINPUT8 core;
		LPDIRECTINPUTDEVICE8 mouseDevice;

		WinAPI_Window *focusWindow;

		DIMOUSESTATE2 di_state;

		Ceng::BOOL relative;

	public:
		Mouse_DirectInput();
		Mouse_DirectInput(WinAPI_Window *focusWindow,LPDIRECTINPUT8 core,
			LPDIRECTINPUTDEVICE8 mouseDevice);

		virtual ~Mouse_DirectInput();

		virtual void Release() override;

		virtual const Ceng::CRESULT Restore() override;

		virtual const Ceng::CRESULT RelativeMode(const Ceng::BOOL state) override;

		virtual const Ceng::CRESULT GetState(MouseState *state) override;

		virtual const Ceng::CRESULT ClipToWindow(const Ceng::BOOL clip) override;
	};
}

#endif