#include "FullySpecifiedType.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

FullySpecifiedType::FullySpecifiedType(const TypeSpecifier& typeSpec)
	: INonTerminal(NonTerminalType::fully_specified_type), typeSpec(typeSpec), qualifier(TypeQualifier())
{

}

FullySpecifiedType::FullySpecifiedType(const TypeQualifier& qualifier, const TypeSpecifier& typeSpec)
	: INonTerminal(NonTerminalType::fully_specified_type), typeSpec(typeSpec), qualifier(qualifier)
{

}

std::shared_ptr<FullySpecifiedType> FullySpecifiedType::GetBasicType(GLSL::BasicType::value basicType)
{
	auto noArr = std::make_shared<TypeSpecifierNoArray>(basicType);

	TypeSpecifierNoPrec noPrec{ noArr };

	TypeSpecifier typeSpec{ noPrec };

	return std::make_shared<FullySpecifiedType>(typeSpec);
}

void FullySpecifiedType::Release()
{
	delete this;
}

Ceng::StringUtf8 FullySpecifiedType::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += qualifier.ToString(indentLevel);
	out += typeSpec.ToString(indentLevel);

	return out;
}

void FullySpecifiedType::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_FullySpecifiedType(*this);
}