/*****************************************************************************
*
* winproc-thunk.cpp
*
* Created By Jari Korkala 12/9/2014
*
*****************************************************************************/

#include "../inc/winproc-thunk.h"

#include "../inc/win32-window.h"

using namespace Ceng;

#ifndef _WIN64

typedef LRESULT (__thiscall WinAPI_Window::*Call_WindowProc)(::HWND,::UINT,::WPARAM,::LPARAM);

const Call_WindowProc call_WindowProc = &WinAPI_Window::WindowProc;

typedef LRESULT (*WrapperCall)(WinAPI_Window*,::HWND,::UINT,::WPARAM,::LPARAM);

/**
 * Let the compiler handle forwarding to correct window object's
 * member function.
 */
LRESULT Wrapper(WinAPI_Window *instance,::HWND hwnd,::UINT msg,::WPARAM wParam,::LPARAM lParam)
{
	return instance->WindowProc(hwnd,msg,wParam,lParam);
}

WinProcThunk* WinProcThunk::GetInstance()
{
	Ceng::UINT8 *codeBuffer = (Ceng::UINT8*)::VirtualAlloc(NULL,4096,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE);

	if (codeBuffer == nullptr)
	{
		return nullptr;
	}

	// mov eax,esp
	codeBuffer[0] = 0x8b;
	codeBuffer[1] = (3 << 6) + (0 << 3) + 4;

	// push [eax+16] = LPARAM
	codeBuffer[2] = 0xff;
	codeBuffer[3] = (1 << 6) + (6 << 3) + 0;
	codeBuffer[4] = 16;

	// push [eax+12] = WPARAM
	codeBuffer[5] = 0xff;
	codeBuffer[6] = (1 << 6) + (6 << 3) + 0;
	codeBuffer[7] = 12;

	// push [eax+8] = MSG
	codeBuffer[8] = 0xff;
	codeBuffer[9] = (1 << 6) + (6 << 3) + 0;
	codeBuffer[10] = 8;

	// push [eax+4] = HWND
	codeBuffer[11] = 0xff;
	codeBuffer[12] = (1 << 6) + (6 << 3) + 0;
	codeBuffer[13] = 4;
	

	// push [imm32]
	codeBuffer[14] = 0x68;
	codeBuffer[15] = 0;
	codeBuffer[16] = 0;
	codeBuffer[17] = 0;
	codeBuffer[18] = 0;

	WinAPI_Window **instancePtrLoc = (WinAPI_Window**)&codeBuffer[15];

	// mov eax,[call_Wrapper]
	codeBuffer[19] = 0xb8+0;
	codeBuffer[20] = 0;
	codeBuffer[21] = 0;
	codeBuffer[22] = 0;
	codeBuffer[23] = 0;

	WrapperCall *ptr = (WrapperCall*)&codeBuffer[20];

	*ptr = &Wrapper;
	
	// call [eax]
	codeBuffer[24] = 0xff;
	codeBuffer[25] = (3 << 6) + (2 << 3);

	// add esp,20
	codeBuffer[26] = 0x83;
	codeBuffer[27] = (3 << 6) + 4;
	codeBuffer[28] = 20;

	// ret 16
	codeBuffer[29] = 0xc2;
	codeBuffer[30] = 0;
	codeBuffer[31] = 0;

	// Contents of the codeBuffer are equivalent to the following
	// assembly code:
	
	/*
	__asm
	{
		mov eax,esp;

		push [eax+16]; // LPARAM
		push [eax+12]; // WPARAM
		push [eax+8]; // UINT msg
		push [eax+4]; // HWND
		push instance

		mov eax,call_WindowProc;

		call [eax];

		add esp,20
		
		return 16
	}
	*/

	Call_Thunk thunkPtr = (Call_Thunk)&codeBuffer[0];

	WinProcThunk *temp = new WinProcThunk(thunkPtr,instancePtrLoc,codeBuffer,4096);

	return temp;
}

#else

constexpr uint8_t rexW = (1 << 6) | (1 << 3);

typedef LRESULT(__thiscall WinAPI_Window::* Call_WindowProc)(::HWND, ::UINT, ::WPARAM, ::LPARAM);

const Call_WindowProc call_WindowProc = &WinAPI_Window::WindowProc;

typedef LRESULT(*WrapperCall_x64)(::HWND, ::UINT, ::WPARAM, ::LPARAM, WinAPI_Window*);

/**
 * Let the compiler handle forwarding to correct window object's
 * member function.
 */
LRESULT Wrapper_x64(::HWND hwnd, ::UINT msg, ::WPARAM wParam, ::LPARAM lParam, WinAPI_Window* instance)
{
	return instance->WindowProc(hwnd, msg, wParam, lParam);
}

WinProcThunk* WinProcThunk::GetInstance()
{
	Ceng::UINT8* codeBuffer = (Ceng::UINT8*)::VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

	if (codeBuffer == nullptr)
	{
		return nullptr;
	}

	// Coming in from the previous function, we have
	//
	// rcx = LPARAM
	// rdx = WPARAM
	// r8 = MSG
	// r9 = HWND
	//
	// These must remain as is because the next function will reuse them
	//
	// Stack is aligned at 16 byte boundary before a call instruction. The call then
	// places 8 byte return address to stack, leaving it out of alignment by 8 bytes.
	// 
	// Our function puts one param to stack (8 bytes), followed by 32 bytes of shadow space.
	// At this point 48 bytes have been added since last alignment, so we can proceed.
	// 
	// Setting up the stack frame for function call:
	// 
	// 1. Align stack to 16 bytes
	// 2. Instance pointer is pushed to stack
	// 3. Add 32 byte shadow space to stack
	// 4. Call wrapper
	// 5. Clear stack on return

	// This means the following assembly code is needed:
		/*
	__asm
	{
		//and rsp, ~15;  // floors rsp to nearest number divisible by 16

		sub rsp, 8;

		mov rax, instancePtr;

		push rax;

		sub rsp, 32;  // shadow space

		mov rax,call_WindowProc;

		call [rax];

		return 40; // clear shadow space (32) + instance ptr
	}
	*/

	/*
	// and rsp, ~15
	// REX.W + 83 /4 lb
	codeBuffer[0] = rexW;
	codeBuffer[1] = 0x83;
	codeBuffer[2] = (0b11 << 6) | (4 << 3) | 0b100;
	codeBuffer[3] = 0xF0;
	*/

	/*
	// sub rsp, 8
	// // sub r/m64, imm8
	// REX.W + 83 /5 lb
	codeBuffer[0] = rexW;
	codeBuffer[1] = 0x83;
	codeBuffer[2] = (0b11 << 6) | (5 << 3) | 0b100;
	codeBuffer[3] = 8;
	*/

	// mov rax, instancePtr
	// REX.W b8 +rd Io
	codeBuffer[0] = rexW;
	codeBuffer[1] = 0xb8;

	// instancePtr
	codeBuffer[2] = 0;
	codeBuffer[3] = 0;
	codeBuffer[4] = 0;
	codeBuffer[5] = 0;
	codeBuffer[6] = 0;
	codeBuffer[7] = 0;
	codeBuffer[8] = 0;
	codeBuffer[9] = 0;

	WinAPI_Window** instancePtrLoc = (WinAPI_Window**)&codeBuffer[2];

	// push rax
	// 50+rd
	codeBuffer[10] = 0x50;

	// sub rsp, 32
	// sub r/m64, imm8
	// REX.W + 83 /5 ib
	codeBuffer[11] = rexW;
	codeBuffer[12] = 0x83;
	codeBuffer[13] = (0b11 << 6) | (5 << 3) | 0b100;
	codeBuffer[14] = 32;

	//mov rax, call_WindowProc;
	codeBuffer[15] = rexW;
	codeBuffer[16] = 0xb8;

	// call_WindowProc
	codeBuffer[17] = 0;
	codeBuffer[18] = 0;
	codeBuffer[19] = 0;
	codeBuffer[20] = 0;
	codeBuffer[21] = 0;
	codeBuffer[22] = 0;
	codeBuffer[23] = 0;
	codeBuffer[24] = 0;

	WrapperCall_x64* ptr = (WrapperCall_x64*)&codeBuffer[17];

	*ptr = &Wrapper_x64;

	//call rax
	// FF /2
	codeBuffer[25] = 0xff;
	codeBuffer[26] = (3 << 6) | (2 << 3);

	// add rsp, 40
	// add r/m64, imm8
	// REX.W + 83 /0 ib
	codeBuffer[27] = rexW;
	codeBuffer[28] = 0x83;
	codeBuffer[29] = (0b11 << 6) | 0b100;
	codeBuffer[30] = 40;

	// return
	codeBuffer[31] = 0xc3;

	Call_Thunk thunkPtr = (Call_Thunk)&codeBuffer[0];

	WinProcThunk* temp = new WinProcThunk(thunkPtr, instancePtrLoc, codeBuffer, 4096);

	return temp;
}

#endif

WinProcThunk::WinProcThunk(Call_Thunk callback,WinAPI_Window **instancePtrLoc,
						   Ceng::UINT8 *codeBuffer,
						   const Ceng::UINT32 bufferSize)
	: thunkCall(callback),instancePtrLoc(instancePtrLoc),codeBuffer(codeBuffer),bufferSize(bufferSize)
{
	this->bufferSize = bufferSize;
}

void WinProcThunk::SetWindow(WinAPI_Window *window)
{
	*instancePtrLoc = window;
}


WinProcThunk::Call_Thunk WinProcThunk::GetCallback()
{
	return thunkCall;
}

WinProcThunk::~WinProcThunk()
{
	::VirtualFree(codeBuffer,0,MEM_RELEASE);
}

