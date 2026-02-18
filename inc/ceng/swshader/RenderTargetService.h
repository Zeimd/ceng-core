#pragma once

#ifndef CENG_SWRENDER_RENDER_TARGET_SERVICE_H
#define CENG_SWRENDER_RENDER_TARGET_SERVICE_H

#include "../interfaces/base-interface.h"

namespace Ceng::Pshader
{
	class RenderTargetService : public BASE_INTERFACE
	{
	protected:

		~RenderTargetService() override
		{

		}

	public:

		virtual void GenerateAddresses(Ceng::UINT32 screenX, Ceng::UINT32 screenY, POINTER* quadTargetOffset) = 0;

	};
}

#endif