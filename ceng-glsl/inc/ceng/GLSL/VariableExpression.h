#ifndef CENG_GLSL_VARIABLE_EXPRESSION_H
#define CENG_GLSL_VARIABLE_EXPRESSION_H

#include <vector>
#include <ceng/datatypes/ce-string.h>

#include "FieldExpression.h"

namespace Ceng
{
	namespace GLSL
	{
		class VariableExpression
		{
		public:

			std::vector<FieldExpression> chain;

		public:

			VariableExpression();

			VariableExpression(FieldExpression root);

			VariableExpression(FieldExpression& root);

			VariableExpression(std::vector<FieldExpression>&& chain);

			~VariableExpression();

			void Append(FieldExpression& access);

			Ceng::StringUtf8 ToString() const;			
		};
	}
}

#endif