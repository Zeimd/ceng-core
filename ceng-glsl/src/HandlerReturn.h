#ifndef CENG_GLSL_HANDLER_RETURN_H
#define CENG_GLSL_HANDLER_RETURN_H

#include "ParserReturnValue.h"

namespace Ceng
{
	struct HandlerReturn
	{
		ParserReturnValue retVal;
		bool valid;
	};
}

#endif