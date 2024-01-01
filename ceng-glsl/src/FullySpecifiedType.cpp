#include "FullySpecifiedType.h"

using namespace Ceng;

FullySpecifiedType::FullySpecifiedType(const TypeSpecifier& typeSpec)
	: typeSpec(typeSpec), qualifier(TypeQualifier())
{

}

FullySpecifiedType::FullySpecifiedType(const TypeQualifier& qualifier, const TypeSpecifier& typeSpec)
	: typeSpec(typeSpec), qualifier(qualifier)
{

}