/*****************************************************************************
*
* locking-task.cpp
*
* Created By Jari Korkala 10/10/2014
*
*****************************************************************************/

#include "locking-task.h"

#include <ceng/datatypes/critical-section.h>

using namespace Ceng;

LockingTask::LockingTask() : lock(nullptr)
{
}

LockingTask::~LockingTask()
{
	if (lock != nullptr)
	{
		lock->Unlock();
	}
}

const CRESULT LockingTask::Prepare(const Ceng::UINT32 threadId, Pipeline* pipeline)
{
	return CE_ERR_FAIL;
}

const CRESULT LockingTask::Execute(const Ceng::UINT32 threadId, Pipeline* pipeline)
{
	return CE_ERR_FAIL;
}