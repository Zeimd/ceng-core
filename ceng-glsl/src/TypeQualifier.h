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
		
		StorageQualifier::value storage;
		InterpolationQualifier::value interpolation;
		bool invariant;

		LayoutQualifier layout;
	public:

		TypeQualifier();

		TypeQualifier(StorageQualifier::value sq);
		TypeQualifier(const LayoutQualifier& layout);
		TypeQualifier(InterpolationQualifier::value interpolation);
		TypeQualifier(bool invariant);

		TypeQualifier(bool invariant, StorageQualifier::value sq);
		TypeQualifier(InterpolationQualifier::value interpolation, StorageQualifier::value sq);
		TypeQualifier(bool invariant, InterpolationQualifier::value interpolation, StorageQualifier::value sq);
		
	};
}

#endif