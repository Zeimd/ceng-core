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

Ceng::StringUtf8 Initializer::ToString() const
{
	return assignEx->ToString();
}