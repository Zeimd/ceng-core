/*****************************************************************************
*
* gl32-render-target-view.h
*
* Created By Jari Korkala 9/11/2015
*
*****************************************************************************/

#ifndef CENG_GL32_RENDER_TARGET_VIEW_H
#define CENG_GL32_RENDER_TARGET_VIEW_H

#include <ceng/interfaces/render-target-view.h>

namespace Ceng
{
	class GL32_RenderTargetView : public RenderTargetView
	{
	public:

	public:
		GL32_RenderTargetView()
		{
		}

		virtual ~GL32_RenderTargetView()
		{
		}

		virtual void GL_Bind(const Ceng::UINT32 slot) = 0;

		virtual void GL_Unbind(const Ceng::UINT32 slot) = 0;

		virtual void* ResourcePtr() = 0;
	};
}

#endif
