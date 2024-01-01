#include "LayoutQualifierId.h"

using namespace Ceng;

LayoutQualifierId::LayoutQualifierId()
	: INonTerminal(NonTerminalType::layout_qualifier_id)
{

}

void LayoutQualifierId::Release()
{
	delete this;
}