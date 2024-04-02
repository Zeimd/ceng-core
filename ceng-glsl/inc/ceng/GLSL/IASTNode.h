#ifndef CENG_GLSL_IAST_NODE_H
#define CENG_GLSL_IAST_NODE_H

#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	class IASTNode
	{
	public:


		virtual Ceng::StringUtf8 ToString() const = 0;

	};
}



#endif