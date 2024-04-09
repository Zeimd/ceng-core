#include "StructSpecifier.h"
#include "StructDeclarationList.h"

#include "NonTerminalVisitor.h"

using namespace Ceng;

StructSpecifier::StructSpecifier(const Ceng::StringUtf8& _name, std::shared_ptr<StructDeclarationList>& _list)
	: INonTerminal(NonTerminalType::struct_specifier),name(_name),list(_list), anonymous(false)
{

}

StructSpecifier::StructSpecifier(std::shared_ptr<StructDeclarationList>& _list)
	: INonTerminal(NonTerminalType::struct_specifier), list(_list), anonymous(true)
{

}

StructSpecifier::~StructSpecifier()
{

}

void StructSpecifier::Release()
{
	delete this;
}

Ceng::StringUtf8 StructSpecifier::ToString(unsigned int indentLevel) const
{
	Ceng::StringUtf8 temp;

	temp = "struct ";

	if (!anonymous)
	{
		temp += name;
	}	

	temp += "\n";
	temp += "{\n";

	temp += list->ToString(indentLevel+1);

	temp += "}";

	return temp;
}

void StructSpecifier::AcceptVisitor(NonTerminalVisitor& visitor)
{
	visitor.V_StructSpecifier(*this);
}