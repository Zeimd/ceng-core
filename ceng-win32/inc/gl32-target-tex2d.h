/*****************************************************************************
*
* gl32-target-tex2d.h
*
* Created By Jari Korkala 9/11/2015
*
*****************************************************************************/

#ifndef CENG_GL32_TARGET_TEX2D_H
#define CENG_GL32_TARGET_TEX2D_H

#include "gl32-render-target-view.h"

namespace Ceng
{
	class GL32_Texture2D;

	class GL32_RenderTexture2D : public GL32_RenderTargetView
	{
	public:
		GL32_Texture2D *texture;

		Ceng::UINT32 mipSlice;

	public:
		GL32_RenderTexture2D();
		GL32_RenderTexture2D(GL32_Texture2D *texture, const Ceng::UINT32 mipSlice);

		virtual void Release() override;

		virtual ~GL32_RenderTexture2D();

		virtual void GL_Bind(const Ceng::UINT32 slot) override;
		virtual void GL_Unbind(const Ceng::UINT32 slot) override;
		
		virtual void* ResourcePtr() override;
	};
}

#endif
