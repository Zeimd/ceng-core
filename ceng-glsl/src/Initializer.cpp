#include "Initializer.h"

using namespace Ceng;

Initializer::Initializer(std::shared_ptr<AssignmentExpression>& assignEx)
	: INonTerminal(NonTerminalType::initializer), assignEx(assignEx)
{

}

void Initializer::Release()
{
	delete this;
}

