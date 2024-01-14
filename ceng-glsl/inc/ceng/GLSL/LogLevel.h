#ifndef CENG_GLSL_LOGLEVEL_H
#define CENG_GLSL_LOGLEVEL_H

namespace Ceng
{
	namespace LogLevel
	{
		enum value
		{
			debug_low = 0,
			debug = 1,
			verbose = 2,
			nominal = 3,
			warning = 4,
			error = 5,
		};
	}
}

#endif