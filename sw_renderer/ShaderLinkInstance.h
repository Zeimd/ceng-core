#pragma once

#ifndef CENG_SWR_SHADER_LINK_INSTANCE_H
#define CENG_SWR_SHADER_LINK_INSTANCE_H

#include <ceng/datatypes/aligned-buffer.h>

#include "quad-format.h"

namespace Ceng
{
	class CR_ShaderLink;

	class ShaderLinkInstance
	{
	public:

		CR_ShaderLink* link;

		Ceng::UINT32 quadSize;

		Ceng::UINT32 targetAmount;

		Ceng::UINT32 quadCacheSize;

		UINT32 maxViewWidth;
		UINT32 maxViewHeight;

	public:

		ShaderLinkInstance();

		~ShaderLinkInstance();

		CRESULT SetViewSize(const UINT32 maxViewWidth, const UINT32 maxViewHeight);

		CRESULT SetRenderTargets(const Ceng::UINT32 targets);

		AlignedBuffer<Ceng::UINT8>* GetFragmentCache(const Ceng::UINT32 batchSize);

		AlignedBuffer<CR_FloatFragment>* GetFloatVariableBuffer();

		AlignedBuffer<CR_DoubleFragment>* GetDoubleVariableBuffer();

		AlignedBuffer<Ceng::UINT8>* GetShaderStepBuffer();

		AlignedBuffer<CR_QuadHeader>* GetQuadCache(const Ceng::UINT32 maxQuads);

		AlignedBuffer<Ceng::UINT8>* GetClipperCache(const Ceng::UINT32 batchSize);

	protected:
		CRESULT SyncQuadCache();
	};
}

#endif