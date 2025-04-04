/*****************************************************************************
*
* task-pshader.h
*
* Created By Jari Korkala 9/10/2014
*
*****************************************************************************/

#ifndef CRENDER_TASK_PSHADER_H
#define CRENDER_TASK_PSHADER_H

#include <memory>

#include <ceng/datatypes/leaf-vector.h>

#include "locking-task.h"

#include "quad-format.h"

namespace Ceng
{
	class RasterizerBatch;

	class Task_PixelShader : public LockingTask
	{
	public:

		std::shared_ptr<RasterizerBatch> rasterizerBatch;

		LeafVector<CR_QuadHeader> quadList;

		Ceng::UINT32 quadCount;

		Task_PixelShader();

	public:

		Task_PixelShader(std::shared_ptr<RasterizerBatch> &rasterizerBatch);

		virtual ~Task_PixelShader();

		virtual const CRESULT Prepare(const Ceng::UINT32 threadId,Pipeline *pipeline) override;
		virtual const CRESULT Execute(const Ceng::UINT32 threadId,Pipeline *pipeline) override;
	};
}

namespace Ceng::Experimental
{
	class Pipeline;

	class Task_PixelShader : public Experimental::RenderTask
	{
	public:

		std::shared_ptr<RasterizerBatch> rasterizerBatch;

		LeafVector<CR_QuadHeader> quadList;

		Ceng::UINT32 quadCount;
		
	public:

		Task_PixelShader();

		//Task_PixelShader(std::shared_ptr<RasterizerBatch>& rasterizerBatch);

		~Task_PixelShader() override;

		const CRESULT Prepare(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
		const CRESULT Execute(const Ceng::UINT32 threadId, Experimental::Pipeline* pipeline) override;
	};
}

#endif