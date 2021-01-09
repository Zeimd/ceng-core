/*****************************************************************************
*
* win32-window.h
*
* By Jari Korkala 10/2012
*
*****************************************************************************/

#ifndef _CONCEPT2_WIN32_WINDOW_H
#define _CONCEPT2_WIN32_WINDOW_H

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#include <Windows.h>

#include <SDL_video.h>

#include <ceng/datatypes/window.h>

namespace Ceng
{
	class WinProcThunk;

	class WinAPI_Window : public PlatformWindow
	{
	protected:

		HWND windowHandle;
		
		WNDCLASSEX windowClass;

		Ceng::StringUtf16 *className;

		Ceng::StringUtf16 *caption,captionExtra;
		Ceng::StringUtf16 *fullCaption;

		WinProcThunk *thunk;
		
		
		// Location of the main window
		int screenLocX,screenLocY;

		// Size of the main window's client area
		int clientWidth,clientHeight;	
		
		int statusFlags;

		bool resized; // Set to true if windows size changes
		

		WinAPI_Window();

	public:

		SDL_Window *sdl_window;

		WinAPI_Window(Ceng::StringUtf16 *caption,Ceng::StringUtf16 *fullCaption,
							 WNDCLASSEX *windowClass,Ceng::StringUtf16 *className,
							 WinProcThunk *thunk);

		void Configure(Ceng::StringUtf16 *caption,Ceng::StringUtf16 *fullCaption,
						HWND windowHandle,
						WNDCLASSEX *windowClass,Ceng::StringUtf16 *className,
						int statusFlags,
						const Ceng::UINT32 locX,const Ceng::UINT32 locY,
						const Ceng::UINT32 width,const Ceng::UINT32 height);
		
		virtual ~WinAPI_Window();

		virtual void Release() override;

		virtual void Show() override;
		virtual void Hide() override;

		virtual void Minimize() override;
		virtual void Maximize() override;

		virtual const Ceng::BOOL IsDestroyed() override;
		virtual const Ceng::BOOL IsActive() override;
		virtual const Ceng::BOOL IsResized() override;
		virtual const Ceng::BOOL IsVisible() override;
		virtual const Ceng::BOOL IsForeground() override;
		virtual const Ceng::BOOL KeyboardFocus() override;

		virtual const CRESULT SetCaption(const Ceng::String &text) override;
		virtual const CRESULT SetCaptionExtra(const Ceng::String &extra) override;

		virtual void GetClientArea(Ceng::UINT32 *widthPtr, Ceng::UINT32 *heightPtr) override;

		virtual const CRESULT ProcessMessages() override;

		HWND GetWindowHandle();

		virtual const CRESULT Redraw() override;

		LRESULT WindowProc(::HWND handle,::UINT message,::WPARAM wParam,::LPARAM lParam);
	};

	

}

#endif