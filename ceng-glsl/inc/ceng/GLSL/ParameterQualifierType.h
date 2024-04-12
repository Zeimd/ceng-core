#ifndef CENG_GLSL_PARAMETER_QUALIFIER_TYPE_H
#define CENG_GLSL_PARAMETER_QUALIFIER_TYPE_H

namespace Ceng
{
	namespace GLSL
	{
		namespace ParameterQualifierType
		{
			enum value
			{
				empty,
				in,
				out,
				inout,
				invalid_value,
			};

			const char* ToString(ParameterQualifierType::value type);
		}
	}
}

#endif