#ifndef CENG_GLSL_LAYOUT_DATA_H
#define CENG_GLSL_LAYOUT_DATA_H

#include <ceng/datatypes/ce-string.h>

namespace Ceng
{
	namespace GLSL
	{
		struct LayoutData
		{
			Ceng::StringUtf8 name;
			bool hasValue;
			Ceng::INT32 value;

			LayoutData(const Ceng::StringUtf8& name, bool hasValue, Ceng::INT32 value)
				: name(name), hasValue(hasValue), value(value)
			{

			}
		};
	}
}

#endif