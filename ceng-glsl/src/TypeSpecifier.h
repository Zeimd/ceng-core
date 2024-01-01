#ifndef CENG_GLSL_TYPE_SPECIFIER_H
#define CENG_GLSL_TYPE_SPECIFIER_H

#include "TypeSpecifierNoPrecision.h"
#include "PrecisionQualifier.h"

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