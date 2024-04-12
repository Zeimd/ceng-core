#ifndef CENG_GLSL_FUNCTION_PARAMETER_H
#define CENG_GLSL_FUNCTION_PARAMETER_H

#include <ceng/datatypes/ce-string.h>

#include "AST_Datatype.h"
#include "ArrayIndex.h"
#include "ParameterQualifierType.h"

namespace Ceng
{
	namespace GLSL
	{
		class FunctionParameter
		{
		public:
			bool isConst;

			ParameterQualifierType::value qualifier;

			AST_Datatype datatype;

			bool anonymous;
			Ceng::StringUtf8 name;

			ArrayIndex index;

		public:

			FunctionParameter(bool isConst, ParameterQualifierType::value qualifier, AST_Datatype& datatype);

			FunctionParameter(bool isConst, ParameterQualifierType::value qualifier, AST_Datatype& datatype,
				Ceng::StringUtf8& name, ArrayIndex& index);

			Ceng::StringUtf8 ToString() const;
		};
	}
}

#endif