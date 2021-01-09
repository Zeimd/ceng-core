/*****************************************************************************
*
* gl32-adapter.h
*
* Created By Jari Korkala 15/3/2015
*
*****************************************************************************/

#ifndef CENG_GL32_ADAPTER_H
#define CENG_GL32_ADAPTER_H

#include <Windows.h>

#include <ceng/interfaces/graphics-adapter.h>

namespace Ceng
{
	class GL32_GraphicsAdapter : public GraphicsAdapter
	{
	public:

		::DISPLAY_DEVICE deviceData;

	public:

		GL32_GraphicsAdapter();

		GL32_GraphicsAdapter(const ::DISPLAY_DEVICE &source);

		virtual ~GL32_GraphicsAdapter();

		virtual void Release() override;

		virtual const CRESULT GetDesc(GraphicsAdapterDesc &desc) override;
	};
}

#endif