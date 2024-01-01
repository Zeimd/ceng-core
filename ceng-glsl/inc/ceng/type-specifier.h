#ifndef CENG_GLSL_TYPE_SPECIFIER_H
#define CENG_GLSL_TYPE_SPECIFIER_H

#include "type-spec-no-prec.h"
#include "precision-qualifier.h"

namespace Ceng
{
	class TypeSpecifier
	{
	public:

		PrecisionQualifier::value precision;

		TypeSpecifierNoPrec typeSpec;

	public:

		TypeSpecifier(const TypeSpecifierNoPrec& typeSpec);
		TypeSpecifier(PrecisionQualifier::value precision, const TypeSpecifierNoPrec& typeSpec);

	};
}

#endif