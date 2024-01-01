#include "TypeQualifier.h"

using namespace Ceng;

TypeQualifier::TypeQualifier()
	: storage(StorageQualifier()),interpolation(InterpolationQualifier::unused),
	invariant(false)
{

}

TypeQualifier::TypeQualifier(const LayoutQualifier& layout)
{

}

TypeQualifier::TypeQualifier(InterpolationQualifier::value interpolation)
{

}

TypeQualifier::TypeQualifier(const StorageQualifier& sq)
	: storage(sq)
{

}

TypeQualifier::TypeQualifier(bool invariant)
	: storage(StorageQualifier()), interpolation(InterpolationQualifier::unused),
	invariant(invariant)
{

}

TypeQualifier::TypeQualifier(bool invariant, const StorageQualifier& sq)
{

}

TypeQualifier::TypeQualifier(InterpolationQualifier::value interpolation, const StorageQualifier& sq)
{

}

TypeQualifier::TypeQualifier(bool invariant, InterpolationQualifier::value interpolation, const StorageQualifier& sq)
{

}