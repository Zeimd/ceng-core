#include "InitDeclaratorList.h"

using namespace Ceng;

InitDeclaratorList::InitDeclaratorList(std::shared_ptr<SingleDeclaration>& decl)
	: INonTerminal(NonTerminalType::init_declarator_list)
{
	list.push_back(decl);
}

void InitDeclaratorList::Append(std::shared_ptr<SingleDeclaration>& decl)
{
	list.push_back(decl);
}

void InitDeclaratorList::Release()
{
	delete this;
}

Ceng::StringUtf8 InitDeclaratorList::ToString() const
{
	Ceng::StringUtf8 out;

	for (auto& x : list)
	{
		out += x->ToString();
	}

	return out;
}