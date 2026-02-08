#pragma once

#ifndef CENG_PSHADER_TARGET_WRITER_H
#define CENG_PSHADER_TARGET_WRITER_H

#include "../interfaces/base-interface.h"

namespace Ceng::Pshader
{
	class Float;
	class Float2;
	class Float3;
	class Float4;
	class DelayedSampler2D;

	class PshaderTargetWriter : public BASE_INTERFACE
	{
	protected:

		~PshaderTargetWriter() override
		{

		}

	public:

		virtual void WriteFloat(const Pshader::Float& source, void *targetAddress, Ceng::UINT32 coverageIndex) = 0;

		virtual void WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverageIndex) = 0;

		virtual void WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverageIndex) = 0;

		virtual void WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverageIndex) = 0;

		virtual void WriteSampler2d(const DelayedSampler2D& sampler, void* writeAddress, Ceng::INT32 coverageIndex) = 0;
	};
}

#endif