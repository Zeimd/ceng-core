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

Ceng::StringUtf8 FullySpecifiedType::ToString() const
{
	Ceng::StringUtf8 out;

	out += qualifier.ToString();
	out += typeSpec.ToString();

	return out;
}