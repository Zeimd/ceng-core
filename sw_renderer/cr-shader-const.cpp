/*****************************************************************************
*
* cr-shader-const.cpp
*
* Created By Jari Korkala 31/8/2014
*
* - Moved CR_ShaderConstHandle methods here from header.
*
*****************************************************************************/

#include "cr-shader-const.h"

#include "cr-vertex-shader.h"

using namespace Ceng;

CR_ShaderConstant::CR_ShaderConstant(Ceng::UINT32 index, Ceng::CR_ShaderProgram* program)
	: index(index),program(program)
{

}

void CR_ShaderConstant::MarkDirty()
{
	dirty = true;
}

void CR_ShaderConstant::Update()
{

}

void CR_ShaderConstant::ForceUpdate()
{

}