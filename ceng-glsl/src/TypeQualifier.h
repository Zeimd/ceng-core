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

		std::shared_ptr<LayoutQualifier> layout;
	public:

		void Release() override;

		TypeQualifier();

		TypeQualifier(const StorageQualifier& sq);
		
		TypeQualifier(std::shared_ptr<LayoutQualifier>& layout);
		TypeQualifier(std::shared_ptr<LayoutQualifier>& layout, const StorageQualifier& sq);

		TypeQualifier(const InterpolationQualifier& interpolation);
		TypeQualifier(bool invariant);

		TypeQualifier(bool invariant, const StorageQualifier& sq);
		TypeQualifier(const InterpolationQualifier& interpolation, const StorageQualifier& sq);
		TypeQualifier(bool invariant, const InterpolationQualifier& interpolation, const StorageQualifier& sq);

		Ceng::StringUtf8 ToString(unsigned int indentLevel) const override;
		
	};
}

#endif