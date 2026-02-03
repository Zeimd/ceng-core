#pragma once

#ifndef CENG_SWRENDER_WRITER_NULL
#define CENG_SWRENDER_WRITER_NULL

#include <ceng/swshader/PshaderTargetWriter.h>

namespace Ceng
{
	class Writer_null : public Pshader::PshaderTargetWriter
	{
	protected:

		~Writer_null() override;

	public:

		void Release() override;

		void WriteFloat(const Pshader::Float& source, void* targetAddress, Ceng::UINT32 coverage) override;

		void WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverage) override;

		void WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverage) override;

		void WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverage) override;
	};
}

#endif