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
	Ceng::StringUtf8 out;

	for (size_t k = 0; k < list.size(); k++)
	{
		out += list[k]->ToString();

		if (k != list.size() - 1)
		{
			out += ", ";
		}		
	}

	return out;
}
