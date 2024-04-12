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
			ArrayIndex index;

			bool anonymous;
			Ceng::StringUtf8 name;

		public:

			FunctionParameter(bool isConst, ParameterQualifierType::value qualifier, AST_Datatype& datatype,
				ArrayIndex& index);

			FunctionParameter(bool isConst, ParameterQualifierType::value qualifier, AST_Datatype& datatype,
				ArrayIndex& index, Ceng::StringUtf8& name);

			Ceng::StringUtf8 ToString() const;
		};
	}
}

#endif