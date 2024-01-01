#include "SingleDeclaration.h"

using namespace Ceng;

SingleDeclaration::SingleDeclaration(const FullySpecifiedType& fullType, const Ceng::StringUtf8& name)
	: INonTerminal(NonTerminalType::single_declaration), fullType(fullType), name(name), initializer()
{

}

void SingleDeclaration::Release()
{
	delete this;
}