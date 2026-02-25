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

#include "../interfaces/vertex-decl.h"
#include "../enums/shader-datatype.h"

#include "../math/ce-vector.h"

namespace Ceng::Vshader
{
	typedef void (*VertexShaderInputReader)(void* dest, void* source);

	class CR_VertexShaderInput
	{
	public:
		POINTER sourceAddress;
		VertexShaderInputReader callBack;
		
	public:

		CR_VertexShaderInput()
		{
			sourceAddress = 0;
			callBack = nullptr;
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

			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}
	};

	class InFloat2 : public CR_VertexShaderInput
	{
	public:

		operator VectorF2() const
		{
			_declspec(align(16)) VectorF2 temp;

			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}
	};

	class InFloat3 : public CR_VertexShaderInput
	{
	public:

		operator VectorF3() const
		{
			_declspec(align(16)) VectorF3 temp;

			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}
	};

	class InFloat4 : public CR_VertexShaderInput
	{
	public:

		operator VectorF4() const
		{
			_declspec(align(16)) VectorF4 temp;

			(*callBack)(&temp, (void*)sourceAddress);
			return temp;
		}
	};
};

#endif