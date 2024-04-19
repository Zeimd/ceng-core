#ifndef CENG_GLSL_FIELD_EXPRESSION_H
#define CENG_GLSL_FIELD_EXPRESSION_H

#include <ceng/datatypes/ce-string.h>

#include "ArrayIndex.h"

namespace Ceng
{
	namespace GLSL
	{
		class FieldExpression
		{
		public:
			Ceng::StringUtf8 name;
			ArrayIndex index;
			bool empty;

		public:

			FieldExpression();

			FieldExpression(const Ceng::StringUtf8& name);

			FieldExpression(const Ceng::StringUtf8& name, ArrayIndex& index);

			Ceng::StringUtf8 ToString() const;

			bool operator == (const FieldExpression& other) const;
		};
	}
}

#endif