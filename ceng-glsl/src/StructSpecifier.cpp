#include "StructSpecifier.h"

using namespace Ceng;

StructSpecifier::StructSpecifier()
	: INonTerminal(NonTerminalType::struct_specifier)
{

}

void StructSpecifier::Release()
{
	delete this;
}

Ceng::StringUtf8 StructSpecifier::ToString() const
{
	return "";
}