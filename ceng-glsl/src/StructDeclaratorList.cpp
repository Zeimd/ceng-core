#include "StructDeclaratorList.h"
#include "StructDeclarator.h"

using namespace Ceng;

StructDeclaratorList::StructDeclaratorList(std::shared_ptr<StructDeclarator>& decl)
	: INonTerminal(NonTerminalType::struct_declarator_list)
{
	list.push_back(decl);
}

void StructDeclaratorList::Append(std::shared_ptr<StructDeclarator>& decl)
{
	list.push_back(decl);
}

void StructDeclaratorList::Release()
{
	delete this;
}

Ceng::StringUtf8 StructDeclaratorList::ToString() const
{
	return "";
}
