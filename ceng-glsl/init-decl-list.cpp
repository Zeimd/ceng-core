#include <ceng/init-decl-list.h>

using namespace Ceng;

InitDeclaratorList::InitDeclaratorList(const SingleDeclaration& decl)
{
	list.push_back(decl);
}