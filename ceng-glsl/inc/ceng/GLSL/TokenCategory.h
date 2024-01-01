#ifndef CENG_GLSL_TOKEN_CATEGORY_H
#define CENG_GLSL_TOKEN_CATEGORY_H

namespace Ceng
{
	namespace TokenCategory
	{
		enum value
		{
			op,
			data_type,
			literal_val,
			identifier,
			meta,
			qualifier,
			undefined,
		};
	}
}

#endif