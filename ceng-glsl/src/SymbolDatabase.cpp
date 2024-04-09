#include "SymbolDatabase.h"

using namespace Ceng;

SymbolDatabase::SymbolDatabase()
	: root(), top(nullptr)
{

}

Symbol& SymbolDatabase::StartScope()
{
	if (top == nullptr)
	{
		top = &root;
		return *top;
	}

	return *top;
}

Symbol& SymbolDatabase::EndScope()
{
	return *top;
}