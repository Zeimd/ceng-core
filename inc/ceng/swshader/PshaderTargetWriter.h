#pragma once

#ifndef CENG_PSHADER_TARGET_WRITER_H
#define CENG_PSHADER_TARGET_WRITER_H

#include "../interfaces/base-interface.h"

#include "pshader-types.h"

namespace Ceng::Pshader
{
	class PshaderTargetWriter : public BASE_INTERFACE
	{
	protected:

		~PshaderTargetWriter() override
		{

		}

	public:

		virtual void WriteFloat(const Pshader::Float& source, void *targetAddress, Ceng::UINT32 coverage) = 0;

		virtual void WriteFloat2(const Pshader::Float2& source, void* targetAddress, Ceng::UINT32 coverage) = 0;

		virtual void WriteFloat3(const Pshader::Float3& source, void* targetAddress, Ceng::UINT32 coverage) = 0;

		virtual void WriteFloat4(const Pshader::Float4& source, void* targetAddress, Ceng::UINT32 coverage) = 0;
	};
}

#endif