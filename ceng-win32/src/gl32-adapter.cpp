/*****************************************************************************
*
* gl32-adapter.cpp
*
* Created By Jari Korkala 15/3/2015
*
*****************************************************************************/

#include "../inc/gl32-adapter.h"

using namespace Ceng;

GL32_GraphicsAdapter::GL32_GraphicsAdapter()
{
}

GL32_GraphicsAdapter::GL32_GraphicsAdapter(const ::DISPLAY_DEVICE &source) : deviceData(source)
{
}

GL32_GraphicsAdapter::~GL32_GraphicsAdapter()
{
}

void GL32_GraphicsAdapter::Release()
{
	delete this;
}

const CRESULT GL32_GraphicsAdapter::GetDesc(GraphicsAdapterDesc &desc)
{
	desc.deviceName = deviceData.DeviceName;

	desc.description = deviceData.DeviceString;
	
	desc.stateFlags = 0;

	if (deviceData.StateFlags & DISPLAY_DEVICE_ACTIVE)
	{
		desc.stateFlags |= GraphicsAdapterState::active;
	}

	if (deviceData.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER)
	{
		desc.stateFlags |= GraphicsAdapterState::mirroring_driver;
	}

	if (deviceData.StateFlags & DISPLAY_DEVICE_MODESPRUNED)
	{
		desc.stateFlags |= GraphicsAdapterState::spruned_modes;
	}

	if (deviceData.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
	{
		desc.stateFlags |= GraphicsAdapterState::primary_device;
	}

	if (deviceData.StateFlags & DISPLAY_DEVICE_REMOVABLE)
	{
		desc.stateFlags |= GraphicsAdapterState::removable;
	}

	if (deviceData.StateFlags & DISPLAY_DEVICE_VGA_COMPATIBLE)
	{
		desc.stateFlags |= GraphicsAdapterState::vga_compatible;
	}

	return CE_OK;
}