#include "UniformManager.h"

#include "ShaderDatatypeMeta.h"

using namespace Ceng;

Ceng::CRESULT UniformManager::Build(const std::vector<ShaderUniformDesc>& uniformList)
{
	GatherUniformBlocks(uniformList);

	for (Ceng::UINT32 k = 0; k < uniformList.size(); k++)
	{
		Ceng::INT32 index = FindUniformBlock(uniformList[k].blockName);

		UniformBlock& block = uniformBlocks[index];

		UniformAllocation alloc;

		alloc.bufferId = index;
		alloc.offset = AlignOffset(block.size, CR_SHADER_DATA_TYPE_ALIGNMENT[uniformList[k].dataType]);
		alloc.size = CR_SHADER_DATA_TYPE_SIZE[uniformList[k].dataType];

		uniformAllocation.push_back(alloc);

		block.size = alloc.offset + CR_SHADER_DATA_TYPE_SIZE[uniformList[k].dataType];
	}

	return CE_OK;
}

Ceng::INT32 UniformManager::FindUniformBlock(const char* name)
{
	if (name == nullptr)
	{
		for (UINT32 j = 0; j < uniformBlocks.size(); ++j)
		{
			if (uniformBlocks[j].name == nullptr)
			{
				return j;
			}
		}

		return -1;
	}

	for (UINT32 j = 0; j < uniformBlocks.size(); ++j)
	{
		if (uniformBlocks[j].name == nullptr)
		{
			continue;
		}

		if (strcmp(name, uniformBlocks[j].name) == 0)
		{
			return j;
		}
	}

	return -1;
}

void UniformManager::GatherUniformBlocks(const std::vector<ShaderUniformDesc>& uniformList)
{
	for (UINT32 k = 0; k < uniformList.size(); ++k)
	{
		Ceng::INT32 index = FindUniformBlock(uniformList[k].blockName);

		if (index == -1)
		{
			uniformBlocks.emplace_back(uniformList[k].blockName);
		}
	}
}

Ceng::UINT32 UniformManager::AlignOffset(Ceng::UINT32 offset, Ceng::UINT32 alignment)
{
	Ceng::UINT32 remainder = offset % alignment;

	if (remainder > 0)
	{
		return offset + (alignment - remainder);
	}

	return offset;
}
