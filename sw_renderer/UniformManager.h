#pragma once

#ifndef CENG_UNIFORM_MANAGER_H
#define CENG_UNIFORM_MANAGER_H

#include <ceng/datatypes/shader-uniform-desc.h>

#include <ceng/datatypes/return-val.h>

#include "UniformBlock.h"

namespace Ceng
{
	class UniformManager
	{
	public:

		std::vector<UniformBlock> uniformBlocks;

		std::vector<UniformAllocation> uniformAllocation;

	public:

		Ceng::CRESULT Build(const std::vector<ShaderUniformDesc>& uniformList);
		
		Ceng::INT32 FindUniformBlock(const char* name);

	protected:

		void GatherUniformBlocks(const std::vector<ShaderUniformDesc>& uniformList);

		static Ceng::UINT32 AlignOffset(Ceng::UINT32 offset, Ceng::UINT32 alignment);
	};

	
}

#endif