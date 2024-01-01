#ifndef CENG_GLSL_TYPE_QUALIFIER_H
#define CENG_GLSL_TYPE_QUALIFIER_H

#include "StorageQualifier.h"
#include "InterpolationQualifier.h"
#include "LayoutQualifier.h"

namespace Ceng
{
	class TypeQualifier
	{
	public:
		
		StorageQualifier storage;
		InterpolationQualifier::value interpolation;
		bool invariant;

		LayoutQualifier layout;
	public:

		TypeQualifier();

		TypeQualifier(const StorageQualifier& sq);
		TypeQualifier(const LayoutQualifier& layout);
		TypeQualifier(InterpolationQualifier::value interpolation);
		TypeQualifier(bool invariant);

		TypeQualifier(bool invariant, const StorageQualifier& sq);
		TypeQualifier(InterpolationQualifier::value interpolation, const StorageQualifier& sq);
		TypeQualifier(bool invariant, InterpolationQualifier::value interpolation, const StorageQualifier& sq);
		
	};
}

#endif