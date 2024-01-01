#include <ceng/GLSL/ceng_GLSL.h>

#include "GLSL_Parser.h"

namespace Ceng
{
	namespace GLSL
	{
		CRESULT GetParser(IParser** out_parser)
		{
			*out_parser = new GLSL_Parser();

			return CE_OK;
		}
	}
}