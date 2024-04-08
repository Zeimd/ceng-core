#include "TypeSpecifier.h"

#include "AST_Visitor.h"

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

Ceng::StringUtf8 TypeSpecifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (precision.precision != PrecisionQualifierType::unassigned)
	{
		out += precision.ToString(indentLevel);
		out += ' ';
	}
	out += typeSpec.ToString(indentLevel);

	return out;
}

void TypeSpecifier::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_TypeSpecifier(*this);
}