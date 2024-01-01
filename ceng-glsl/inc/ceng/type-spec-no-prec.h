#ifndef CENG_GLSL_TYPE_SPEC_NO_PREC_H
#define CENG_GLSL_TYPE_SPEC_NO_PREC_H

#include "type-spec-no-arr.h"
#include "constant_expression.h"

namespace Ceng
{
	class TypeSpecifierNoPrec
	{
	public:
		TypeSpecifierNoArray typeSpec;

		bool isArray;
		ConstantExpression elementExpression;

	public:

		TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec);

		TypeSpecifierNoPrec(const TypeSpecifierNoArray& typeSpec, const ConstantExpression& elementExpression);
	};
}

#endif