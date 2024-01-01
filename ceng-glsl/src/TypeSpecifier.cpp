#include "TypeSpecifier.h"

using namespace Ceng;


TypeSpecifier::TypeSpecifier(const TypeSpecifierNoPrec& typeSpec)
	: typeSpec(typeSpec),precision(PrecisionQualifier::unassigned)
{

}

TypeSpecifier::TypeSpecifier(PrecisionQualifier::value precision, const TypeSpecifierNoPrec& typeSpec)
	:typeSpec(typeSpec),precision(precision)
{

}