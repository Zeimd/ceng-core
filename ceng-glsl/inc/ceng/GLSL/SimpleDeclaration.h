#ifndef CENG_GLSL_SIMPLE_DECLARATION_H
#define CENG_GLSL_SIMPLE_DECLARATION_H

#include "AST_Datatype.h"

#include "PrecisionQualifierType.h"

namespace Ceng
{
	namespace GLSL
	{
		class SimpleDeclaration
		{
		public:

			bool constant;

			PrecisionQualifierType::value precision;

			// NOTE: contains array size if any
			AST_Datatype datatype;			

			Ceng::StringUtf8 name;

		public:

			SimpleDeclaration(bool constant, PrecisionQualifierType::value precision,
				const AST_Datatype& datatype, Ceng::StringUtf8 name);

			Ceng::StringUtf8 ToString() const;
		};
	}
}

#endif

