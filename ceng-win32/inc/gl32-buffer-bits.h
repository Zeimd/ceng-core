/*****************************************************************************
*
* gl32-buffer-bits.h
*
* Created By Jari Korkala 15/3/2015
*
*****************************************************************************/

#ifndef CENG_GL32_BUFFER_BITS_H
#define CENG_GL32_BUFFER_BITS_H

#include <windows.h>

#include <ceng/datatypes/basic-types.h>
#include <ceng/datatypes/boolean.h>
#include <ceng/enums/image-formats.h>

namespace Ceng
{
	class BufferBits
	{
	public:
		::PIXELFORMATDESCRIPTOR desc;

	public:

		BufferBits();
		~BufferBits();

		BufferBits(const Ceng::IMAGE_FORMAT::value format);
		BufferBits(const Ceng::IMAGE_FORMAT::value format,const Ceng::IMAGE_FORMAT::value depthFormat);

		const Ceng::BOOL IsMatch(const ::PIXELFORMATDESCRIPTOR &other) const;
		const Ceng::BOOL IsMatch(const BufferBits &other) const;

		const Ceng::BOOL IsMatchColor(const ::PIXELFORMATDESCRIPTOR &other) const;
		const Ceng::BOOL IsMatchColor(const BufferBits &other) const;

		const Ceng::BOOL IsMatchColorAlpha(const ::PIXELFORMATDESCRIPTOR &other) const;
		const Ceng::BOOL IsMatchColorAlpha(const BufferBits &other) const;

		const Ceng::BOOL IsMatchDepthStencil(const ::PIXELFORMATDESCRIPTOR &other) const;
		const Ceng::BOOL IsMatchDepthStencil(const BufferBits &other) const;

	protected:

		void InitDesc();

		void SetColorFormat(const Ceng::IMAGE_FORMAT::value format);

		void SetDepthStencilFormat(const Ceng::IMAGE_FORMAT::value format);
	};
}

#endif