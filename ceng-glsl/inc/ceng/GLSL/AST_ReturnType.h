#ifndef CENG_GLSL_AST_RETURN_TYPE_H
#define CENG_GLSL_AST_RETURN_TYPE_H

#include "AST_Datatype.h"
#include "ArrayIndex.h"

namespace Ceng
{
	namespace GLSL
	{
		class AST_ReturnType
		{
		public:
			AST_Datatype datatype;

			ArrayIndex index;

		public:

			AST_ReturnType();

			AST_ReturnType(AST_Datatype& datatype);

			AST_ReturnType(AST_Datatype& datatype, ArrayIndex& index);

			Ceng::StringUtf8 ToString() const;

		};
	}
}

#endif