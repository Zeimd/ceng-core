#include "FullySpecifiedType.h"

#include "AST_Visitor.h"

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

Ceng::StringUtf8 FullySpecifiedType::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += qualifier.ToString(indentLevel);
	out += typeSpec.ToString(indentLevel);

	return out;
}

void FullySpecifiedType::AcceptVisitor(AST_Visitor& visitor)
{
	visitor.V_FullySpecifiedType(*this);
}