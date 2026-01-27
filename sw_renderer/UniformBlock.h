#pragma once

#ifndef CENG_UNIFORM_BLOCK_H
#define CENG_UNIFORM_BLOCK_H

#include <vector>

#include <ceng/datatypes/basic-types.h>

namespace Ceng
{
	struct UniformAllocation
	{
		Ceng::INT32 bufferId;
		Ceng::UINT32 size;
		Ceng::UINT32 offset;
	};

	class UniformBlock
	{
	public:
		const char* name;
		Ceng::UINT32 size;

		UniformBlock(const char* name)
			: name(name), size(0)
		{

		}

	public:

		
	};

	
}

#endif