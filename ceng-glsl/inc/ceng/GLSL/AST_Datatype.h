#ifndef CENG_GLSL_AST_DATATYPE_H
#define CENG_GLSL_AST_DATATYPE_H

#include <ceng/datatypes/ce-string.h>
#include "BasicType.h"
#include "TypenameCategory.h"

#include "ArrayIndex.h"

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

			ArrayIndex index;

		public:

			AST_Datatype();

			AST_Datatype(BasicType::value basicType);

			AST_Datatype(BasicType::value basicType, ArrayIndex& index);

			AST_Datatype(const Ceng::StringUtf8& customTypeName);

			AST_Datatype(const Ceng::StringUtf8& customTypeName, ArrayIndex& index);

			Ceng::StringUtf8 ToString() const;

			AST_Datatype DiscardArray() const;

			bool operator == (const AST_Datatype& other) const;

			bool operator != (const AST_Datatype& other) const;
		};
	}
}

#endif