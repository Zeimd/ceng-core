#include "TypeSpecifier.h"

using namespace Ceng;

void TypeSpecifier::Release()
{
	delete this;
}

TypeSpecifier::TypeSpecifier(const TypeSpecifierNoPrec& typeSpec)
	: INonTerminal(NonTerminalType::type_specifier), typeSpec(typeSpec),precision()
{

}

TypeSpecifier::TypeSpecifier(const PrecisionQualifier& precision, const TypeSpecifierNoPrec& typeSpec)
	: INonTerminal(NonTerminalType::type_specifier), typeSpec(typeSpec),precision(precision)
{

}

Ceng::StringUtf8 TypeSpecifier::ToString() const
{
	Ceng::StringUtf8 out;

	out += precision.ToString();
	out += typeSpec.ToString();

	return out;
}