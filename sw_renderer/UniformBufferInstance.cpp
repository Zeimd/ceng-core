#include "UniformBufferInstance.h"

#include "UniformManager.h"

using namespace Ceng;

UniformBufferInstance::UniformBufferInstance()
	: manager(nullptr)
{

}

Ceng::CRESULT UniformBufferInstance::Configure(UniformManager* manager, Ceng::UINT32 cacheLine)
{
	this->manager = manager;
	
	for (int k = 0; k < manager->uniformBlocks.size(); ++k)
	{
		uniformBuffer.emplace_back(manager->uniformBlocks[k].size, cacheLine);
	}

	uniformPtr = AlignedBuffer<UINT8*>(Ceng::UINT32(manager->uniformAllocation.size()), cacheLine);

	for (int k = 0; k < manager->uniformAllocation.size(); ++k)
	{
		uniformPtr[k] = &uniformBuffer[manager->uniformAllocation[k].bufferId][manager->uniformAllocation[k].offset];
	}

	return CE_OK;
}

UniformBufferInstance::UniformBufferInstance(const UniformBufferInstance& source)
	: uniformBuffer(source.uniformBuffer)
{
	manager = source.manager;

	uniformPtr = AlignedBuffer<UINT8*>(
		Ceng::UINT32(source.uniformPtr.GetSize()), source.uniformPtr.GetAlignment());

	for (Ceng::UINT32 k = 0; k < source.manager->uniformAllocation.size(); k++)
	{
		uniformPtr[k] = &uniformBuffer[manager->uniformAllocation[k].bufferId][manager->uniformAllocation[k].offset];
	}
}

UniformBufferInstance& UniformBufferInstance::operator = (const UniformBufferInstance& source)
{
	uniformBuffer = source.uniformBuffer;

	manager = source.manager;

	uniformPtr = AlignedBuffer<UINT8*>(
		Ceng::UINT32(source.uniformPtr.GetSize()), source.uniformPtr.GetAlignment());

	for (Ceng::UINT32 k = 0; k < source.manager->uniformAllocation.size(); k++)
	{
		uniformPtr[k] = &uniformBuffer[manager->uniformAllocation[k].bufferId][manager->uniformAllocation[k].offset];
	}

	return *this;
}
