#pragma once

#ifndef CENG_SWR_SHADER_LINK_INSTANCE_H
#define CENG_SWR_SHADER_LINK_INSTANCE_H

#include <ceng/datatypes/aligned-buffer.h>

#include <ceng/datatypes/return-val.h>

namespace Ceng
{
	namespace SWRender
	{
		struct PixelShaderQuadBatch;
		class CR_FloatFragment;
		class CR_DoubleFragment;
	}

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

		AlignedBuffer<SWRender::CR_FloatFragment>* GetFloatVariableBuffer();

		AlignedBuffer<SWRender::CR_DoubleFragment>* GetDoubleVariableBuffer();

		AlignedBuffer<Ceng::UINT8>* GetShaderStepBuffer();

		AlignedBuffer<SWRender::PixelShaderQuadBatch>* GetQuadCache(const Ceng::UINT32 maxQuads);

		AlignedBuffer<Ceng::UINT8>* GetClipperCache(const Ceng::UINT32 batchSize);

	protected:
		CRESULT SyncQuadCache();
	};
}

#endif