#include "LayoutQualifier.h"

using namespace Ceng;

LayoutQualifier::LayoutQualifier()
	: INonTerminal(NonTerminalType::layout_qualifier)
{

}

void LayoutQualifier::Release()
{
	delete this;
}