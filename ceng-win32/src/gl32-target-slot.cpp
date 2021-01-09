/*****************************************************************************
*
* gl32-target-slot.cpp
*
* Created By Jari Korkala 9/11/2015
*
*****************************************************************************/

#include "../inc/gl32-render-target-view.h"
#include "../inc/gl32-target-slot.h"

using namespace Ceng;

GL32_RenderTargetSlot::GL32_RenderTargetSlot() 
	: dirty(false),view(nullptr),nextView(nullptr),gl_slotID(GL_COLOR_ATTACHMENT0)
{
}

GL32_RenderTargetSlot::~GL32_RenderTargetSlot()
{
}

void GL32_RenderTargetSlot::GL_Update()
{
	if (view != nullptr)
	{
		view->GL_Unbind(gl_slotID);
	}

	if (nextView != nullptr)
	{
		nextView->GL_Bind(gl_slotID);
	}

	view = nextView;
	dirty = false;
}


