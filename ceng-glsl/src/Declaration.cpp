#include "Declaration.h"

using namespace Ceng;

Declaration::Declaration(const InitDeclaratorList& declList)
	: INonTerminal(NonTerminalType::declaration), declList(declList)
{

}

void Declaration::Release()
{
	delete this;
}