#ifndef CENG_GLSL_INTERPOLATION_QUALIFIER_TYPE_H
#define CENG_GLSL_INTERPOLATION_QUALIFIER_TYPE_H

namespace Ceng
{
	namespace GLSL
	{
		namespace InterpolationQualifierType
		{
			enum value
			{
				smooth,
				flat,
				noperspective,
				unused,
				invalid_value,
			};

			const char* ToString(InterpolationQualifierType::value type);
		}
	}	
}

#endif