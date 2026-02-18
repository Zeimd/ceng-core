#include "rtarget-service.h"

#include "PixelShaderContextCommon.h"

#include "rtarget-data.h"

using namespace Ceng;

SW_RenderTargetService::SW_RenderTargetService(PixelShaderContextCommon* common)
	: common(common)
{

}

SW_RenderTargetService::~SW_RenderTargetService()
{

}

void SW_RenderTargetService::Release()
{
	delete this;
}

void SW_RenderTargetService::GenerateAddresses(Ceng::UINT32 screenX, Ceng::UINT32 screenY, POINTER* quadTargetOffset)
{	
	for (Ceng::UINT32 i = 2; i < common->activeRenderTargets; i++)
	{
		quadTargetOffset[i] = common->targetHandles[i]->GetQuadAddress(0, screenX, screenY);
	}
}