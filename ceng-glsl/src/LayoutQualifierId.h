#ifndef CENG_GLSL_LAYOUT_QUALIFIER_ID_H
#define CENG_GLSL_LAYOUT_QUALIFIER_ID_H

#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	class LayoutQualifierId
	{
	public:
		Ceng::StringUtf8 identifier;
		Ceng::INT32 value;
	};
}

#endif