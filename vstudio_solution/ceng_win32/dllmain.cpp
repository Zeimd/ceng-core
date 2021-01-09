// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

#define SDL_MAIN_HANDLED
#include <SDL.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		SDL_SetMainReady();
		SDL_Init(0);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		SDL_Quit();
		break;
	}
	return TRUE;
}

