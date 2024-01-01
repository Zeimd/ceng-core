#include "Initializer.h"

using namespace Ceng;

Initializer::Initializer() 
	: INonTerminal(NonTerminalType::initializer)
{

}

void Initializer::Release()
{
	delete this;
}

