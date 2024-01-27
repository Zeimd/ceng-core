#include "StructDeclarator.h"

using namespace Ceng;



StructDeclarator::StructDeclarator(Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::struct_declarator), name(name), isArray(false), arraySize(nullptr)
{

}

StructDeclarator::StructDeclarator(Ceng::StringUtf8& name, bool implicitArray)
	: INonTerminal(NonTerminalType::struct_declarator), name(name), isArray(true), arraySize(nullptr)
{

}

StructDeclarator::StructDeclarator(Ceng::StringUtf8& name, std::shared_ptr<Expression>& arraySize)
	: INonTerminal(NonTerminalType::struct_declarator), name(name), isArray(true), arraySize(arraySize)
{

}

void StructDeclarator::Release()
{
	delete this;
}

Ceng::StringUtf8 StructDeclarator::ToString() const
{
	return "";
}