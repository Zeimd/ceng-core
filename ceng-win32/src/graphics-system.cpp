/*****************************************************************************
*
* platform-renderer.cpp
*
* Created By Jari Korkala 10/9/2014
*
*****************************************************************************/

#include <ceng/interfaces/graphics-system.h>

#include "../inc/ceng-win32.h"

#include "../inc/win32-crend-d3d9.h"
//#include "../inc/win32-crend-d3d10.h"

#include "../inc/win32-opengl32.h"

#include <ceng/datatypes/cpu-info.h>

using namespace Ceng;

extern "C" _declspec(dllexport) const Ceng::CRESULT Ceng_CreateGraphics3D(Ceng::RENDERER_TYPE::value type,
													 Ceng::GraphicsSystem **out_renderer, Ceng::LogType *log)
{
	CRESULT cresult;

	CPU_Info *tempCPU;

	cresult = Ceng_GetCpuInfo(&tempCPU);

	if (cresult != CE_OK)
	{
		return cresult;
	}

	switch(type)
	{
	case Ceng::RENDERER_TYPE::SOFTWARE:

	
		//*********************************************************''
		// Attempt to create Direct3D 10 output

		/*
		ConceptRenderer_D3D10 *outD3D10;

		try
		{
			// NOTE: control of cpu data transferred to tempCore
			outD3D10 = new ConceptRenderer_D3D10(tempCPU);
		}
		catch(std::bad_alloc &ba)
		{
			tempCPU->Release();
			return CE_ERR_OUT_OF_MEMORY;
		}

		cresult = outD3D10->Initialize();

		if (cresult != CE_OK)
		{
			outD3D10->Release();
			return cresult;
		}

		*renderer = (PlatformRenderer*)outD3D10;

		return CE_OK;
		*/
		
		
		//*****************************************************'
		// Create Direct3D 9 output
		
		ConceptRenderer_D3D9 *tempCore;

		cresult = ConceptRenderer_D3D9::GetInstance(tempCPU, &tempCore);

		*out_renderer = (Ceng::GraphicsSystem*)tempCore;
		
		break;
	case Ceng::RENDERER_TYPE::D3D_9:
		/*
		Direct3D_Core *d3d_core;

		d3d_core = Direct3D_Core::GetInstance();

		*out_renderer = (Ceng::GraphicsSystem*)d3d_core;
	*/
		break;

	case Ceng::RENDERER_TYPE::opengl_32:


		cresult = GL32_GraphicsSystem::GetInstance(tempCPU,out_renderer,log);

		// Not used by opengl version
		tempCPU->Release();

		break;

	default:
		tempCPU->Release();
		return CE_ERR_INVALID_PARAM;
	}

	return CE_OK;
}