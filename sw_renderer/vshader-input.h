/*****************************************************************************
*
* cr-vshader-input.h
*
* By Jari Korkala 4/2013
*
* File created as part of project refactoring.
*
*****************************************************************************/

#ifndef _CENG_CR_VSHADER_INPUT_H
#define _CENG_CR_VSHADER_INPUT_H

#include <ceng/interfaces/vertex-decl.h>
#include <ceng/enums/shader-datatype.h>

#include <ceng/math/ce-vector.h>

namespace Ceng::Vshader
{
	typedef void (*VertexShaderInputReader)(void* dest, void* source);

	class CR_VertexShaderInput
	{
	public:
		POINTER sourceAddress;
		VertexShaderInputReader callBack;
		//Ceng::VTX_DATATYPE::value sourceFormat;
	public:
		CR_VertexShaderInput()
		{
			sourceAddress = 0;
			callBack = nullptr;
			//sourceFormat = VTX_DATATYPE::UNKNOWN;
		}
	};

	struct VertexShaderInputRegister
	{
		CR_VertexShaderInput* variable;
		Ceng::SHADER_DATATYPE::value type;
	};

	class InFloat : public CR_VertexShaderInput
	{
	public:

		operator FLOAT32() const
		{
			FLOAT32 temp;

			//(*call_ToFloat[sourceFormat])(&temp, (void*)sourceAddress);
			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}

	protected:

		//static void (*call_ToFloat[128])(void *dest,void *source);
	};

	class InFloat2 : public CR_VertexShaderInput
	{
	public:

		operator VectorF2() const
		{
			_declspec(align(16)) VectorF2 temp;

			//(*call_ToFloat2[sourceFormat])(&temp, (void*)sourceAddress);
			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}

	protected:

		//static void (*call_ToFloat2[128])(void* dest, void* source);
	};

	class InFloat3 : public CR_VertexShaderInput
	{
	public:

		operator VectorF3() const
		{
			_declspec(align(16)) VectorF3 temp;

			//(*call_ToFloat3[sourceFormat])(&temp, (void*)sourceAddress);
			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}

	protected:

		//static void (*call_ToFloat3[128])(void* dest, void* source);
	};

	class InFloat4 : public CR_VertexShaderInput
	{
	public:

		operator VectorF4() const
		{
			_declspec(align(16)) VectorF4 temp;

			//(*call_ToFloat4[sourceFormat])(&temp, (void*)sourceAddress);
			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}

	protected:

		//static void (*call_ToFloat4[128])(void* dest, void* source);
	};

	// Callbacks

	extern void NullVertexReader(void* dest, void* source);

	extern VertexShaderInputReader GetReadCallback(Ceng::SHADER_DATATYPE::value destFormat, 
		Ceng::VTX_DATATYPE::value sourceFormat);

	//extern void VSIN_FLOAT_FLOAT_X86(void *dest,void *source);
	//extern void VSIN_FLOAT2_FLOAT2_X86_SSE2(void *dest,void *source);
	//extern void VSIN_FLOAT3_FLOAT3_X86(void* dest, void* source);
	//extern void VSIN_FLOAT4_FLOAT4_X86_SSE(void *dest,void *source);
};

#endif