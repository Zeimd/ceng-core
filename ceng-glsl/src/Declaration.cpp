#include "Declaration.h"

using namespace Ceng;

Declaration::Declaration(std::shared_ptr<InitDeclaratorList>& declList)
	: INonTerminal(NonTerminalType::declaration), declList(declList)
{

}

void Declaration::Release()
{
	delete this;
}

Ceng::StringUtf8 Declaration::ToString() const
{
	return "";
}