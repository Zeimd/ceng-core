#ifndef CENG_GLSL_STORAGE_QUALIFIER_TYPE_H
#define CENG_GLSL_STORAGE_QUALIFIER_TYPE_H

namespace Ceng
{
	namespace GLSL
	{
		namespace StorageQualifierType
		{
			enum value
			{
				sq_const,
				sq_attribute,
				sq_varying,
				sq_centroid_varying,
				sq_in,
				sq_out,
				sq_centroid_in,
				sq_centroid_out,
				sq_uniform,

				unused,
			};

			const char* ToString(StorageQualifierType::value type);
		}
	}	
}

#endif