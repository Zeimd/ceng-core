/*****************************************************************************
*
* gl32-target-slot.h
*
* Created By Jari Korkala 9/11/2015
*
*****************************************************************************/

#ifndef CENG_GL32_TARGET_SLOT_H
#define CENG_GL32_TARGET_SLOT_H

#include <ceng/datatypes/boolean.h>
#include "../inc/gl32-constants.h"

#include <gl/glew.h>

namespace Ceng
{
	class GL32_RenderTargetView;

	class GL32_RenderTargetSlot
	{
	public:
		Ceng::BOOL dirty;
		GLenum gl_slotID;
		GL32_RenderTargetView *view;
		GL32_RenderTargetView *nextView;

	public:
		GL32_RenderTargetSlot();
		~GL32_RenderTargetSlot();

		void GL_Update();
	};
}

#endif
