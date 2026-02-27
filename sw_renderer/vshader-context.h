/*****************************************************************************
*
* vshader-instance.h
*
* By Jari Korkala 8/2014
*
*****************************************************************************/

#ifndef CRENDER_VSHADER_INSTANCE_H
#define CRENDER_VSHADER_INSTANCE_H

#include <memory>
#include <vector>

#include <ceng/datatypes/return-val.h>

#include <ceng/datatypes/vshader-input-desc.h>

#include "future.h"

namespace Ceng
{
	namespace Experimental
	{
		class Task_Clipper;
	};

	class DrawBatch;

	class LockingStage;

	class VertexShaderInstanceCommon;

	class VertexShaderContext
	{
	public:

		std::shared_ptr<VertexShaderInstanceCommon> common;

	protected:

		VertexShaderContext()
			//: instanceIndex(0)
		{

		}	

	public:

		virtual ~VertexShaderContext()
		{

		}

		virtual CRESULT Configure() = 0;

		virtual CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch,
												LockingStage *outputQueue) = 0;

		virtual CRESULT ProcessVertexBatch(std::shared_ptr<DrawBatch> batch, Ceng::UINT32 threadId,
			Experimental::Future<std::shared_ptr<Experimental::Task_Clipper>>* future) = 0;
	};
}

#endif