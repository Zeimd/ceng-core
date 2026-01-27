#pragma once

#ifndef CENG_SWRENDER_UNIFORM_BUFFER_INSTANCE_H
#define CENG_SWRENDER_UNIFORM_BUFFER_INSTANCE_H

#include <vector>

#include <ceng/datatypes/return-val.h>

#include <ceng/datatypes/aligned-buffer.h>

namespace Ceng
{
	using UniformBufferContainer = AlignedBuffer<Ceng::UINT8>;

	class UniformManager;

	class UniformBufferInstance
	{
	public:

		UniformManager* manager;

		AlignedBuffer<Ceng::UINT8*> uniformPtr;

		std::vector<UniformBufferContainer> uniformBuffer;

	public:

		UniformBufferInstance();

		Ceng::CRESULT Configure(UniformManager* manager, Ceng::UINT32 cacheLine);

		UniformBufferInstance(const UniformBufferInstance& source);

		UniformBufferInstance& operator = (const UniformBufferInstance& source);
	};
}

#endif