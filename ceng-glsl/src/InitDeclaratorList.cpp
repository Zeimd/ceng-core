#include "InitDeclaratorList.h"

using namespace Ceng;

InitDeclaratorList::InitDeclaratorList(const SingleDeclaration& decl)
	: INonTerminal(NonTerminalType::init_declarator_list)
{
	list.push_back(decl);
}

void InitDeclaratorList::Release()
{
	delete this;
}