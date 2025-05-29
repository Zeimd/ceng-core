#pragma once

#ifndef CENG_SWR_EXTERN_PSHADER_INSTANCE_H
#define CENG_SWR_EXTERN_PSHADER_INSTANCE_H

#include <ceng/interfaces/pshader-instance.h>

#include "pshader-context.h"

namespace Ceng
{
	class ExternalPixelShaderContext : public PixelShaderContext
	{
	public:

		PixelShaderInstance* externInstance;
	};
}

#endif