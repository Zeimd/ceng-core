#include "FullySpecifiedType.h"

using namespace Ceng;

FullySpecifiedType::FullySpecifiedType(const TypeSpecifier& typeSpec)
	: INonTerminal(NonTerminalType::fully_specified_type), typeSpec(typeSpec), qualifier(TypeQualifier())
{

}

FullySpecifiedType::FullySpecifiedType(const TypeQualifier& qualifier, const TypeSpecifier& typeSpec)
	: INonTerminal(NonTerminalType::fully_specified_type), typeSpec(typeSpec), qualifier(qualifier)
{

}

void FullySpecifiedType::Release()
{
	delete this;
}