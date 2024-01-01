#include "StorageQualifier.h"

using namespace Ceng;

void StorageQualifier::Release()
{
	delete this;
}

StorageQualifier::StorageQualifier() 
	: INonTerminal(NonTerminalType::storage_qualifier), qualifier(StorageQualifierType::unused)
{

}

StorageQualifier::StorageQualifier(StorageQualifierType::value qualifier)
	: qualifier(qualifier)
{

}