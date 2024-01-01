#ifndef CENG_GLSL_FULLY_SPECIFIED_TYPE_H
#define CENG_GLSL_FULLY_SPECIFIED_TYPE_H

#include "TypeQualifier.h"
#include "TypeSpecifier.h"

namespace Ceng
{
	class FullySpecifiedType
	{
	public:

		TypeQualifier qualifier;
		TypeSpecifier typeSpec;

	public:

		FullySpecifiedType(const TypeSpecifier& typeSpec);
		FullySpecifiedType(const TypeQualifier& qualifier, const TypeSpecifier& typeSpec);
	};
}

#endif