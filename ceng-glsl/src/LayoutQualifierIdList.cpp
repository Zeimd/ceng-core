#include "LayoutQualifierIdList.h"

using namespace Ceng;

LayoutQualifierIdList::LayoutQualifierIdList()
	:INonTerminal(NonTerminalType::layout_qualifier_id_list)
{

}

void LayoutQualifierIdList::Release()
{
	delete this;
}