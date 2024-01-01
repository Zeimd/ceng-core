#include "TypeQualifier.h"

using namespace Ceng;

TypeQualifier::TypeQualifier()
	: storage(StorageQualifier::unused),interpolation(InterpolationQualifier::unused),
	invariant(false)
{

}

TypeQualifier::TypeQualifier(StorageQualifier::value sq)
	: storage(sq)
{

}