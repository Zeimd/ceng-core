#include "UniformBlock.h"

using namespace Ceng;

Ceng::INT32 UniformBlock::FindUniformBlock(const char* name, std::vector<UniformBlock>& blocks)
{
	if (name == nullptr)
	{
		for (UINT32 j = 0; j < blocks.size(); ++j)
		{
			if (blocks[j].name == nullptr)
			{
				return j;
			}
		}

		return -1;
	}

	for (UINT32 j = 0; j < blocks.size(); ++j)
	{
		if (blocks[j].name == nullptr)
		{
			continue;
		}

		if (strcmp(name, blocks[j].name) == 0)
		{
			return j;
		}
	}

	return -1;
}