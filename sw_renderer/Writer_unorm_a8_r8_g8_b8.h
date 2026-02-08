#pragma once

#ifndef CENG_SWRENDER_WRITER_R8G8B8A8
#define CENG_SWRENDER_WRITER_R8G8B8A8

#include <ceng/swshader/PshaderTargetWriter.h>

namespace Ceng
{
	class Writer_unorm_a8_r8_g8_b8 : public Pshader::PshaderTargetWriter
	{
	protected:

		~Writer_unorm_a8_r8_g8_b8() override;

	public:

		void Release() override;

		void WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverage) override;

		void WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverage) override;

		void WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverage) override;

		void WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverage) override;

		void WriteSampler2d(const Pshader::DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex) override;
	};
}

#endif