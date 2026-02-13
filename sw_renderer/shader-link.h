/*****************************************************************************
*
* cr-shader-link.h
*
* By Jari Korkala 5/2013
*
*****************************************************************************/

#ifndef _CENG_CR_SHADER_LINK_H
#define _CENG_CR_SHADER_LINK_H

#include <ceng/datatypes/aligned-buffer.h>

#include "quad-format.h"

#include "fragment-format.h"

namespace Ceng
{
	class ShaderLinkInstance;

	class CR_VertexShader;
	class CR_PixelShader;

	class CR_ShaderLink
	{
	public:

		CR_VertexShader *vertexShader;
		CR_PixelShader *pixelShader;

		CR_FragmentFormat fragmentFormat;
		CR_QuadFormat quadFormat;

		Ceng::UINT32 fragmentCacheSize;

		Ceng::UINT32 clipperCacheSize;	

		Ceng::UINT32 cacheLineSize;

	public:

		CR_ShaderLink();

		CR_ShaderLink(const Ceng::UINT32 cacheLineSize);
		~CR_ShaderLink();

		CRESULT Configure(CR_VertexShader *vertexShader,CR_PixelShader *pixelShader);		

	protected:

		void Clear();
		
	};
};

#endif