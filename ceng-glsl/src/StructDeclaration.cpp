#include "StructDeclaration.h"
#include "StructDeclaratorList.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

StructDeclaration::StructDeclaration(TypeSpecifier& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
	: INonTerminal(NonTerminalType::struct_declaration), typeSpec(typeSpec), typeQ(), list(list)
{

}

StructDeclaration::StructDeclaration(TypeQualifier& typeQ, TypeSpecifier& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
	: INonTerminal(NonTerminalType::struct_declaration), typeSpec(typeSpec), typeQ(typeQ), list(list)
{

}

StructDeclaration::~StructDeclaration()
{

}

void StructDeclaration::Release()
{
	delete this;
}

Ceng::StringUtf8 StructDeclaration::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 out;

	out += typeQ.ToString(indentLevel);
	out += ' ';
	out += typeSpec.ToString(indentLevel);
	out += ' ';
	out += list->ToString(indentLevel);
	out += ';';

	return out;
}

void StructDeclaration::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_StructDeclaration(*this);
}