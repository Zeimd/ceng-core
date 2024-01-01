#ifndef CENG_GLSL_SINGLE_DECLARATION_H
#define CENG_GLSL_SINGLE_DECLARATION_H

#include "FullySpecifiedType.h"
#include "ConstantExpression.h"
#include "Initializer.h"

namespace Ceng
{
	class SingleDeclaration
	{
	public:
		FullySpecifiedType fullType;

		Ceng::StringUtf8 name;

		bool isArray;
		ConstantExpression arraySizeExpression;

		bool invariant;

		Initializer initializer;

	public:

		SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name);
	};
}

#endif