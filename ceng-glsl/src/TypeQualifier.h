#ifndef CENG_GLSL_TYPE_QUALIFIER_H
#define CENG_GLSL_TYPE_QUALIFIER_H

#include "INonTerminal.h"
#include "StorageQualifier.h"
#include "InterpolationQualifier.h"
#include "LayoutQualifier.h"

namespace Ceng
{
	class TypeQualifier : public INonTerminal
	{
	public:
		
		StorageQualifier storage;
		InterpolationQualifier interpolation;
		bool invariant;

		LayoutQualifier layout;
	public:

		void Release() override;

		TypeQualifier();

		TypeQualifier(const StorageQualifier& sq);
		TypeQualifier(const LayoutQualifier& layout);
		TypeQualifier(const InterpolationQualifier& interpolation);
		TypeQualifier(bool invariant);

		TypeQualifier(bool invariant, const StorageQualifier& sq);
		TypeQualifier(const InterpolationQualifier& interpolation, const StorageQualifier& sq);
		TypeQualifier(bool invariant, const InterpolationQualifier& interpolation, const StorageQualifier& sq);
		
	};
}

#endif