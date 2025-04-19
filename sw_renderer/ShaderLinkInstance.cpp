#include "ShaderLinkInstance.h"

#include "shader-link.h"
#include "cr-pixel-shader.h"

using namespace Ceng;

ShaderLinkInstance::ShaderLinkInstance()
	: link(nullptr), maxViewWidth(0), maxViewHeight(0), quadCacheSize(0), quadSize(0), targetAmount(0)
{

}

/*
ShaderLinkInstance::ShaderLinkInstance(CR_ShaderLink* link)
	: link(link), maxViewWidth(0), maxViewHeight(0), quadCacheSize(0),quadSize(0), targetAmount(0)
{

}
*/

ShaderLinkInstance::~ShaderLinkInstance()
{

}

CRESULT ShaderLinkInstance::SetRenderTargets(const Ceng::UINT32 targets)
{
	if (link == nullptr)
	{
		return Ceng::CE_OK;
	}

	CRESULT cresult;

	// Add space for render targets

	quadSize = Ceng::UINT32(link->quadFormat.targetStart + sizeof(POINTER) * targets);

	UINT32 remainder = quadSize % 16;

	// Pad quad size to a multiply of 16 bytes
	if (remainder)
	{
		quadSize = (quadSize & ~15) + 16;
	}

	targetAmount = targets;

	cresult = SyncQuadCache();

	if (cresult != CE_OK)
	{
		return cresult;
	}

	if (link->pixelShader != nullptr)
	{
		cresult = link->pixelShader->SetShaderLink(this);
	}

	return CE_OK;
}

CRESULT ShaderLinkInstance::SetViewSize(const Ceng::UINT32 maxViewWidth, const Ceng::UINT32 maxViewHeight)
{
	if (this->maxViewWidth == maxViewWidth && this->maxViewHeight == maxViewHeight)
	{
		return CE_OK;
	}

	CRESULT cresult;

	cresult = SyncQuadCache();

	if (cresult != CE_OK)
	{
		return cresult;
	}

	this->maxViewWidth = maxViewWidth;
	this->maxViewHeight = maxViewHeight;

	return CE_OK;
}

CRESULT ShaderLinkInstance::SyncQuadCache()
{
	// TODO: Pad width,height to nearest power of two

	quadCacheSize = (maxViewWidth >> 1) * (maxViewHeight >> 1) * sizeof(CR_QuadHeader);

	return CE_OK;
}

AlignedBuffer<Ceng::UINT8>* ShaderLinkInstance::GetClipperCache(const Ceng::UINT32 batchSize)
{
	return new AlignedBuffer<Ceng::UINT8>(batchSize * link->clipperCacheSize, link->cacheLineSize);
}

AlignedBuffer<Ceng::UINT8>* ShaderLinkInstance::GetShaderStepBuffer()
{
	return new AlignedBuffer<Ceng::UINT8>(link->quadFormat.gradientBufferSize, link->cacheLineSize);
}

AlignedBuffer<Ceng::UINT8>* ShaderLinkInstance::GetFragmentCache(const Ceng::UINT32 batchSize)
{
	return new AlignedBuffer<Ceng::UINT8>(batchSize * link->fragmentFormat.size, link->cacheLineSize);
}

AlignedBuffer<CR_FloatFragment>* ShaderLinkInstance::GetFloatVariableBuffer()
{
	return new AlignedBuffer<CR_FloatFragment>(link->quadFormat.floatBlocks, link->cacheLineSize);
}

AlignedBuffer<CR_DoubleFragment>* ShaderLinkInstance::GetDoubleVariableBuffer()
{
	return new AlignedBuffer<CR_DoubleFragment>(link->quadFormat.doubleBlocks, link->cacheLineSize);
}

AlignedBuffer<CR_QuadHeader>* ShaderLinkInstance::GetQuadCache(const Ceng::UINT32 maxQuadCount)
{
	return new AlignedBuffer<CR_QuadHeader>(maxQuadCount * sizeof(CR_QuadHeader), link->cacheLineSize);
}
