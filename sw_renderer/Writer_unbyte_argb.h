#pragma once

#ifndef CENG_SWRENDER_WRITER_R8G8B8A8
#define CENG_SWRENDER_WRITER_R8G8B8A8

#include <array>

#include <ceng/swshader/PshaderTargetWriter.h>

#include <ceng/datatypes/blend-state-desc.h>

namespace Ceng
{
	class Writer_unbyte_argb_noblend : public Pshader::PshaderTargetWriter
	{
	protected:

		~Writer_unbyte_argb_noblend() override;

	public:

		void Release() override;

		void WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex) override;
	};

	typedef void (*BlendPrepareColorCallback)(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors);

	typedef void (*BlendPrepareAlphaCallback)(__m128i* out, __m128i* source, __m128i* dest, Ceng::UINT8* apiBlendFactors);

	typedef void (*BlendOpCallback)(__m128i* out, __m128i* source, __m128i* dest);

	class Writer_unbyte_argb : public Pshader::PshaderTargetWriter
	{
	protected:

		~Writer_unbyte_argb() override;

		// Blend factors provided by SetBlendState() API function. Stored in 0.8 fixed point.
		alignas(16) Ceng::UINT8 apiBlendFactors[16];

		Ceng::UINT32 writeMask;

		BlendPrepareColorCallback prepareSource;
		BlendPrepareColorCallback prepareDest;

		BlendPrepareAlphaCallback prepareSourceAlpha;
		BlendPrepareAlphaCallback prepareDestAlpha;

		BlendOpCallback blendOperation;

	public:

		Writer_unbyte_argb(Ceng::RenderTargetBlendDesc& desc, std::array<Ceng::FLOAT32, 4>& blendFactors);

		void Release() override;

		void WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex) override;

		void WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex) override;
	};
}

#endif