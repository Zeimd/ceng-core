/*****************************************************************************
*
* gl32-shader-const.h
*
* Created By Jari Korkala 25/10/2015
*
*
*****************************************************************************/

#include "../inc/gl32-shader-const.h"
#include "../inc/gl32-shader-program.h"

using namespace Ceng;

GL32_ShaderConstant::GL32_ShaderConstant() : dirty(false), program(nullptr), index(-1)
{
}

GL32_ShaderConstant::GL32_ShaderConstant(GLint index, Ceng::GL32_ShaderProgram *program)
	: dirty(false),program(program),index(index)
{
}

GL32_ShaderConstant::~GL32_ShaderConstant()
{
}

void GL32_ShaderConstant::Release()
{
	delete this;
}

void GL32_ShaderConstant::MarkDirty()
{
	if (dirty == false)
	{
		program->AddUniformUpdate(this);
		dirty = true;
	}
}

void GL32_ShaderConstant::GL_Update()
{
	//if (!program->IsActive()) return;

	if (dirty == true)
	{
		GL_UpdateThis();
	}

	dirty = false;
}

void GL32_ShaderConstant::GL_ForceUpdate()
{
	if (!program->IsActive()) return;

	GL_UpdateThis();

	dirty = false;
}


