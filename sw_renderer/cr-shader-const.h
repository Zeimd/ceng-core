/*****************************************************************************
*
* cr-shader-const.h
*
* By Jari Korkala 4/2013
*
*****************************************************************************/

#ifndef _CENG_CR_SHADER_CONST_H
#define _CENG_CR_SHADER_CONST_H

#include <ceng/interfaces/shader-const.h>

#include "shader-const-data.h"

#include "shader-wrapper.h"

namespace Ceng
{
	class CR_ShaderProgram;

	class CR_ShaderConstant : public Ceng::ShaderConstant
	{
	private:

		Ceng::BOOL dirty;

		Ceng::ShaderWrapper* wrapper;

	protected:

		Ceng::UINT32 index;

		~CR_ShaderConstant() override
		{

		}

		CR_ShaderConstant()
		{

		}

	public:

		CR_ShaderConstant(Ceng::UINT32 index, Ceng::ShaderWrapper* wrapper);

		void MarkDirty();

		void Update();
		void ForceUpdate();

		virtual void UpdateThis() = 0;
		
	};
};

#endif