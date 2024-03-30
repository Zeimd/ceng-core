#include "StructSpecifier.h"

using namespace Ceng;

StructSpecifier::StructSpecifier(const Ceng::StringUtf8& _name, std::shared_ptr<StructDeclarationList>& _list)
	: INonTerminal(NonTerminalType::struct_specifier),name(_name),list(_list)
{

}

void StructSpecifier::Release()
{
	delete this;
}

Ceng::StringUtf8 StructSpecifier::ToString() const
{
	Ceng::StringUtf8 temp;

	temp = "struct ";
	temp += name;
	temp += "\n";
	temp += "{\n";

	temp += list->ToString();

	temp += "}";

	return temp;
}