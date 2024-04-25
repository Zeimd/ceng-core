#include "TypeSpecifier.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

void TypeSpecifier::Release()
{
	delete this;
}

TypeSpecifier::TypeSpecifier(const TypeSpecifierNoPrec& arrayType)
	: INonTerminal(NonTerminalType::type_specifier), arrayType(arrayType),precision()
{

}

TypeSpecifier::TypeSpecifier(const PrecisionQualifier& precision, const TypeSpecifierNoPrec& typeSpec)
	: INonTerminal(NonTerminalType::type_specifier), arrayType(arrayType),precision(precision)
{

}

Ceng::StringUtf8 TypeSpecifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	if (precision.precision != GLSL::PrecisionQualifierType::unassigned)
	{
		out += precision.ToString(indentLevel);
		out += ' ';
	}
	out += arrayType.ToString(indentLevel);

	return out;
}

void TypeSpecifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_TypeSpecifier(*this);
}

std::shared_ptr<TypeSpecifier> TypeSpecifier::GetBasicType(GLSL::BasicType::value basicType)
{
	auto noArr = std::make_shared<TypeSpecifierNoArray>(basicType);

	TypeSpecifierNoPrec noPrec{ noArr };

	return std::make_shared<TypeSpecifier>(noPrec);
}