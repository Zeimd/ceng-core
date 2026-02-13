/*****************************************************************************
*
* shader-link.cpp
*
* By Jari Korkala 5/2013
*
* -----------------------------------------------------------
*
* Jari Korkala 8/2014
*
* - Renamed to shader-link.cpp
*
*****************************************************************************/

#include <ceng/lib/liblog.h>

#include "shader-link.h"

#include "cr-vertex-shader.h"
#include "cr-pixel-shader.h"

using namespace Ceng;

CR_ShaderLink::CR_ShaderLink()
	: vertexShader(nullptr), pixelShader(nullptr)
{

}

CR_ShaderLink::CR_ShaderLink(const Ceng::UINT32 cacheLineSize)
	: vertexShader(nullptr), pixelShader(nullptr), cacheLineSize(cacheLineSize)
{
	
}

CR_ShaderLink::~CR_ShaderLink()
{
	Clear();
}

void CR_ShaderLink::Clear()
{

}

CRESULT CR_ShaderLink::Configure(CR_VertexShader *vertexShader,CR_PixelShader *pixelShader)
{
	this->vertexShader = vertexShader;
	this->pixelShader = pixelShader;

	if (this->vertexShader == nullptr || this->pixelShader == nullptr)
	{
		Log::Print("ShaderLink.Configure : don't have two shaders -> abort");
		return CE_OK;
	}

	// Create fragment format

	Clear();

	CRESULT cresult;

	cresult = fragmentFormat.Configure(vertexShader->outputSemantics,pixelShader->inputSemantics);

	if (cresult != CE_OK)
	{
		Log::Print("ShaderLink.Configure : fragment format configure failed");
		return cresult;
	}

	cresult = quadFormat.Configure(&fragmentFormat);

	if (cresult != CE_OK)
	{
		Log::Print("ShaderLink.Configure : quad format configure failed");
		return cresult;
	}

	cresult = vertexShader->SetFragmentFormat(&fragmentFormat);

	if (cresult != CE_OK)
	{
		Log::Print("ShaderLink.Configure : failed to sync vertex shader output");
		return cresult;
	}

	/*
	cresult = pixelShader->SetFragmentFormat(&quadFormat);

	if (cresult != CE_OK)
	{
		Log::Print("ShaderLink.Configure : failed to sync pixel shader input");
		return cresult;
	}
	*/

	clipperCacheSize = 10*fragmentFormat.size;

	
	return CE_OK;
}

