#include "StructDeclaration.h"
#include "StructDeclaratorList.h"

using namespace Ceng;

StructDeclaration::StructDeclaration(TypeSpecifier& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
	: INonTerminal(NonTerminalType::struct_declaration), typeSpec(typeSpec), typeQ(), list(list)
{

}

StructDeclaration::StructDeclaration(TypeQualifier& typeQ, TypeSpecifier& typeSpec, std::shared_ptr<StructDeclaratorList>& list)
	: INonTerminal(NonTerminalType::struct_declaration), typeSpec(typeSpec), typeQ(typeQ), list(list)
{

}

void StructDeclaration::Release()
{
	delete this;
}

Ceng::StringUtf8 StructDeclaration::ToString() const
{
	Ceng::StringUtf8 out;

	out += typeQ.ToString();
	out += ' ';
	out += typeSpec.ToString();
	out += ' ';
	out += list->ToString();
	out += ';';

	return out;
}

