#ifndef CENG_GLSL_AST_DATATYPE_H
#define CENG_GLSL_AST_DATATYPE_H

#include <ceng/datatypes/ce-string.h>
#include "BasicType.h"
#include "TypenameCategory.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_Datatype
		{
		public:
			TypenameCategory category;

			BasicType::value basicType;
			Ceng::StringUtf8 customTypeName;

		public:

			AST_Datatype();

			AST_Datatype(BasicType::value basicType);

			AST_Datatype(const Ceng::StringUtf8& customTypeName);

			Ceng::StringUtf8 ToString() const;

		};
	}
}

#endif