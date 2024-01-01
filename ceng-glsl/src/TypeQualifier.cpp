#include "TypeQualifier.h"

using namespace Ceng;

TypeQualifier::TypeQualifier()
	: storage(StorageQualifier()),interpolation(),
	invariant(false)
{

}

TypeQualifier::TypeQualifier(const LayoutQualifier& layout)
{

}

TypeQualifier::TypeQualifier(const InterpolationQualifier& interpolation)
{

}

TypeQualifier::TypeQualifier(const StorageQualifier& sq)
	: storage(sq)
{

}

TypeQualifier::TypeQualifier(bool invariant)
	: storage(StorageQualifier()), interpolation(),
	invariant(invariant)
{

}

TypeQualifier::TypeQualifier(bool invariant, const StorageQualifier& sq)
{

}

TypeQualifier::TypeQualifier(const InterpolationQualifier& interpolation, const StorageQualifier& sq)
{

}

TypeQualifier::TypeQualifier(bool invariant, const InterpolationQualifier& interpolation, const StorageQualifier& sq)
{

}