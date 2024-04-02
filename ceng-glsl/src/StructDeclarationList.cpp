#include "StructDeclarationList.h"
#include "StructDeclaration.h"

using namespace Ceng;

StructDeclarationList::StructDeclarationList(std::shared_ptr<StructDeclaration>& decl)
	: INonTerminal(NonTerminalType::struct_declaration_list)
{
	list.push_back(decl);
}

void StructDeclarationList::Append(std::shared_ptr<StructDeclaration>& decl)
{
	list.push_back(decl);
}

StructDeclarationList::~StructDeclarationList()
{

}

void StructDeclarationList::Release()
{
	delete this;
}

Ceng::StringUtf8 StructDeclarationList::ToString() const
{
	Ceng::StringUtf8 out;

	for (auto& item : list)
	{
		out += "    ";
		out += item->ToString();
		out += '\n';
	}

	return out;
}