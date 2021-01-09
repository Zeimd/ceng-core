/*****************************************************************************
*
* gl32-buffer-bits.cpp
*
* Created By Jari Korkala 15/3/2015
*
*****************************************************************************/

#include "../inc/gl32-buffer-bits.h"

using namespace Ceng;

BufferBits::BufferBits()
{
}

BufferBits::~BufferBits()
{
}

void BufferBits::InitDesc()
{
	memset(&desc, 0, sizeof(::PIXELFORMATDESCRIPTOR));

	desc.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
	desc.nVersion = 1;
	desc.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;

	desc.iPixelType = PFD_TYPE_RGBA;
}

void BufferBits::SetColorFormat(const Ceng::IMAGE_FORMAT::value format)
{
	switch (format)
	{
	case IMAGE_FORMAT::C32_ARGB:
	case IMAGE_FORMAT::C32_XRGB:
	case IMAGE_FORMAT::C24_RGB:
		desc.cRedBits = 8;
		desc.cRedShift = 0;

		desc.cGreenBits = 8;
		desc.cGreenShift = 8;

		desc.cBlueBits = 8;
		desc.cBlueShift = 16;
		break;
	case IMAGE_FORMAT::C32_ABGR:
	case IMAGE_FORMAT::C32_XBGR:
	case IMAGE_FORMAT::C24_BGR:
		desc.cRedBits = 8;
		desc.cRedShift = 16;

		desc.cGreenBits = 8;
		desc.cGreenShift = 8;

		desc.cBlueBits = 8;
		desc.cBlueShift = 0;
		break;
	case IMAGE_FORMAT::C32_A2_BGR:
		desc.cRedBits = 10;
		desc.cRedShift = 20;

		desc.cGreenBits = 10;
		desc.cGreenShift = 10;

		desc.cBlueBits = 10;
		desc.cBlueShift = 0;
		break;
	case IMAGE_FORMAT::C32_A2_RGB:
		desc.cRedBits = 10;
		desc.cRedShift = 0;

		desc.cGreenBits = 10;
		desc.cGreenShift = 10;

		desc.cBlueBits = 10;
		desc.cBlueShift = 20;
		break;

	default:
		desc.cRedBits = 0;
		desc.cRedShift = 0;

		desc.cGreenBits = 0;
		desc.cGreenShift = 0;

		desc.cBlueBits = 0;
		desc.cBlueShift = 0;
		break;
	}

	desc.cAlphaBits = 0;
	desc.cAlphaShift = 0;

	switch (format)
	{
	case IMAGE_FORMAT::C32_ARGB:
	case IMAGE_FORMAT::C32_ABGR:
		desc.cAlphaBits = 8;
		desc.cAlphaShift = 24;
		break;
	case IMAGE_FORMAT::C32_A2_BGR:
	case IMAGE_FORMAT::C32_A2_RGB:
		desc.cAlphaBits = 2;
		desc.cAlphaShift = 30;
		break;
	default:
		break;
	}

	desc.cColorBits = desc.cRedBits + desc.cGreenBits + desc.cBlueBits
		+ desc.cAlphaBits;
}

void BufferBits::SetDepthStencilFormat(const Ceng::IMAGE_FORMAT::value format)
{
	desc.cStencilBits = 0;

	switch (format)
	{
	case IMAGE_FORMAT::D16:
		desc.cDepthBits = 16;
		break;
	case IMAGE_FORMAT::D15_S1:
		desc.cDepthBits = 15;
		desc.cStencilBits = 1;
		break;
	case IMAGE_FORMAT::D24_S8:
		desc.cDepthBits = 24;
		desc.cStencilBits = 8;
		break;
	case IMAGE_FORMAT::D32:
	case IMAGE_FORMAT::D32F:
		desc.cDepthBits = 32;
		break;
	}
}

BufferBits::BufferBits(const Ceng::IMAGE_FORMAT::value format)
{
	InitDesc();

	SetColorFormat(format);
}

BufferBits::BufferBits(const Ceng::IMAGE_FORMAT::value format, const Ceng::IMAGE_FORMAT::value depthFormat)
{
	InitDesc();

	SetColorFormat(format);
	SetDepthStencilFormat(depthFormat);
}

const Ceng::BOOL BufferBits::IsMatchDepthStencil(const ::PIXELFORMATDESCRIPTOR &other) const
{
	if (other.cDepthBits != desc.cDepthBits)
	{
		return false;
	}

	if (other.cStencilBits != desc.cStencilBits)
	{
		return false;
	}

	return true;
}

const Ceng::BOOL BufferBits::IsMatchDepthStencil(const BufferBits &other) const
{
	return IsMatchDepthStencil(other.desc);
}

const Ceng::BOOL BufferBits::IsMatchColorAlpha(const ::PIXELFORMATDESCRIPTOR &other) const
{
	if (other.cAlphaBits != desc.cAlphaBits)
	{
		return false;
	}

	if (other.cAlphaShift != desc.cAlphaShift)
	{
		return false;
	}

	return IsMatchColor(other);
}

const Ceng::BOOL BufferBits::IsMatchColorAlpha(const BufferBits &other) const
{
	return IsMatchColorAlpha(other.desc);
}

const Ceng::BOOL BufferBits::IsMatchColor(const ::PIXELFORMATDESCRIPTOR &other) const
{
	if (other.cColorBits != desc.cColorBits)
	{
		return false;
	}

	if (other.cRedBits != desc.cRedBits)
	{
		return false;
	}

	if (other.cRedShift != desc.cRedShift)
	{
		return false;
	}

	if (other.cGreenBits != desc.cGreenBits)
	{
		return false;
	}

	if (other.cGreenShift != desc.cGreenShift)
	{
		return false;
	}

	if (other.cBlueBits != desc.cBlueBits)
	{
		return false;
	}

	if (other.cBlueShift != desc.cBlueShift)
	{
		return false;
	}

	return true;
}

const Ceng::BOOL BufferBits::IsMatchColor(const BufferBits &other) const
{
	return IsMatchColor(other.desc);
}