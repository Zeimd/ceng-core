#ifndef CENG_GLSL_STRUCT_MEMBER_H
#define CENG_GLSL_STRUCT_MEMBER_H

#include <ceng/datatypes/ce-string.h>

#include "AST_Datatype.h"
#include "PrecisionQualifierType.h"

namespace Ceng
{
	namespace GLSL
	{
		class StructMember
		{
		public:

			PrecisionQualifierType::value precision;

			AST_Datatype datatype;

			Ceng::StringUtf8 name;

			StructMember(const AST_Datatype& datatype, const Ceng::StringUtf8& name);

			StructMember(PrecisionQualifierType::value precision, const AST_Datatype& datatype, const Ceng::StringUtf8& name);

			Ceng::StringUtf8 ToString(Ceng::UINT32 indentLevel) const;

		};
	}
}

#endif