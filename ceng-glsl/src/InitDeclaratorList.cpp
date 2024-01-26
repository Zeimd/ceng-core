#include "InitDeclaratorList.h"

using namespace Ceng;

InitDeclaratorList::InitDeclaratorList(std::shared_ptr<SingleDeclaration>& decl)
	: INonTerminal(NonTerminalType::init_declarator_list), invariant(decl->invariant), fullType(decl->fullType)
{
	list.push_back(decl->data);
}

void InitDeclaratorList::Append(std::shared_ptr<SingleDeclaration>& decl)
{
	list.push_back(decl->data);
}

void InitDeclaratorList::Release()
{
	delete this;
}

Ceng::StringUtf8 InitDeclaratorList::ToString() const
{
	Ceng::StringUtf8 out;

	if (invariant)
	{
		out += "invariant ";
	}
	else
	{
		out += fullType->ToString();
		out += ' ';
	}

	for (auto& x : list)
	{
		out += x.ToString();
	}

	return out;
}