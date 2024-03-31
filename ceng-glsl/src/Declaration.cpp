#include "Declaration.h"
#include "FunctionPrototype.h"
#include "InitDeclaratorList.h"

using namespace Ceng;

Declaration::Declaration(std::shared_ptr<InitDeclaratorList>& declList)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::init_list),declList(declList),prototype(nullptr)
{

}

Declaration::Declaration(std::shared_ptr<FunctionPrototype>& prototype)
	: INonTerminal(NonTerminalType::declaration), type(DeclarationType::function_prototype), declList(nullptr), prototype(prototype)
{

}

void Declaration::Release()
{
	delete this;
}

Ceng::StringUtf8 Declaration::ToString() const
{
	Ceng::StringUtf8 temp;

	switch (type)
	{
	case DeclarationType::function_prototype:
		temp = prototype->ToString();
		break;
	case DeclarationType::init_list:
		temp = declList->ToString();
		break;
	default:
		return "<UNHANDLED DECLARATION TYPE>";
	}

	
	temp += ';';

	return temp;
}